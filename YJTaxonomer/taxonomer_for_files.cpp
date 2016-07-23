//
//  taxonomer_for_files.cpp
//  YJTaxonomer
//
//  Created by Younies Mahmoud on 7/22/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//


#include "configuration.h"
#include "headers.h"
#include "node_reader.hpp"
#include "tree_builder.hpp"
#include "YRJ.hpp"




void build_vector(LONG kmer , vector<YRJ *> & sorted_YRJ_nodes ,  vector<LONGS> & hitted_Indices );

int main(int argc, const char * argv[]) {
    
    // hello to you
    cout << "hello, the program started!\n";
    
    //creating the total file
    
    
    cout << "Enter the path to the YRJ file\n";
    
    string target_path ;
    cin >> target_path;
    
    ifstream target_file(target_path);
    
    if(!target_file.good())
    {
        cout <<" the file does not exist: "+ target_path << endl;
        exit(1);
    }
    
    target_file.close();
    
    YRJ targetYRJ(target_path);
    
    /*
    YRJ * all = new YRJ(path_to_the_genomes_database +"all.yrj");
    vector<LONG> random_kmers =  all->getRandomSamples(path_to_random_numbers, random_number_size);
    */
    
    Tree_trie * tree = new Tree_trie(path_to_the_names_dmp_file , path_to_the_nodes_dmp_file);
    
    tree->build_specific_nodes(path_to_the_specific_nodes);
    
    
    vector<YRJ *> sorted_YRJ_nodes;
    vector<LONG> sorted_UIDs = tree->getSortedLeafsUIDs();
    
    vector<LONG> availableUIDs;
    
    for (LONGS i = 0 , n = sorted_UIDs.size(); i < n ; ++i)
    {
        string name = path_to_the_genomes_database + to_string( sorted_UIDs[i]) + ".yrj";
        
        ifstream checkerIF(name);
        if(!checkerIF.is_open())
        {
            cout << "This_UID_doesn't exist: " << sorted_UIDs[i] << endl;
            continue;
        }
        checkerIF.close();
        
        availableUIDs.push_back(sorted_UIDs[i]);
        
        sorted_YRJ_nodes.push_back(new YRJ(name));
        
        Node node = tree->getNodeFromIndex(tree->uid_to_index(sorted_UIDs[i]));
        sorted_YRJ_nodes[i]->set_trie_node(node);
    }
    
    
    cout << sorted_YRJ_nodes.size() << " the sorted YRJ\n";
    
    tree->update_specific_nodes(availableUIDs);
    
    //
    //
    //
    //start the final operation
    //
    //
    
    
    ofstream final_output(target_path + "the_classification_output.txt");
    
    vector<LONGS>  hitted_Indices;
    vector<Node>   hitted_Nodes;
    
    vector<Node> all_global_LCA;
    
    for (LONGS i , n = targetYRJ.get_kmers_numbers() ; i < n ; ++i)
    {
        hitted_Indices.clear();
        hitted_Nodes.clear();
        build_vector( targetYRJ.get_kmer_index(i) , sorted_YRJ_nodes ,   hitted_Indices );
        
        if(hitted_Indices.size() > 1)
        {
              all_global_LCA.push_back( tree->get_Global_LCA(hitted_Nodes) );
        }
        
    }
    
    
    vector<LONGS> global_LCAs_All_Uids =  tree->get_global_kraken_uids(all_global_LCA);
    for (LONGS i = 0 , n = global_LCAs_All_Uids.size(); i <  n ; ++i)
    {
        final_output << global_LCAs_All_Uids[i] << "\t";
    }
    
    final_output << endl;
    
    
    
    
    final_output.flush();
    final_output.close();
    
    
    
    return 0;
}


void build_vector(LONG kmer , vector<YRJ *>  &sorted_YRJ_nodes ,  vector<LONGS> & hitted_Indices )
{
    // clear the vector before starting
    
    for (LONGS i = 0 , n = sorted_YRJ_nodes.size(); i < n ; ++i)
    {
        if( sorted_YRJ_nodes[i]->isKmerExist(kmer) )
            hitted_Indices.push_back(sorted_YRJ_nodes[i]->getTrie_Index());
    }
    
    sort(hitted_Indices.begin(), hitted_Indices.end());
}









