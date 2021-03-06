//
//  main.cpp
//  YJTaxonomy
//
//  Created by Younies Mahmoud on 7/18/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "configuration.h"
#include "headers.h"
#include "node_reader.hpp"
#include "tree_builder.hpp"
#include "YRJ.hpp"
#include "YJR_Hero_Tester.hpp"



//string to_string(LONG number);


void build_vector(LONG kmer , vector<YRJ *> & sorted_YRJ_nodes ,  vector<LONGS> & hitted_Indices );

int main(int argc, const char * argv[]) {
    
    // hello to you
    cout << "hello, the program started!\n";
    
    //creating the total file
    
    YRJ * all = new YRJ(path_to_the_genomes_database +"all.yrj");
    vector<LONG> random_kmers =  all->getRandomSamples(path_to_random_numbers, random_number_size);
    
    
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
    
    
    ofstream final_output(path_to_the_results + name_of_exact_output);
    
    vector<LONGS>  hitted_Indices;
    vector<Node>   hitted_Nodes;
    
    
    final_output << "kmerIndex  kmer    Number_hits LCA level   number_of_leaves    number_of_hitted_leaves GX_dem  GX  Uids_up_to_5\n";;
    for (LONGS i , n = random_kmers.size() ; i < n ; ++i)
    {
        hitted_Indices.clear();
        hitted_Nodes.clear();
        build_vector( random_kmers[i] , sorted_YRJ_nodes ,   hitted_Indices );
        
        LONGS number_Of_Hits = hitted_Indices.size();
        
        final_output << i << "\t";
        final_output << random_kmers[i] << "\t";
        final_output << number_Of_Hits << "\t";
        
        if(number_Of_Hits == 0)
        {
            final_output << "\n";
            continue;
        }
        


            for(std::vector<LONGS>::iterator it = hitted_Indices.begin(); it != hitted_Indices.end(); ++it)
            {
                hitted_Nodes.push_back(tree->getNodeFromIndex(*it));
            }
            
            
            G_Statistics gStat;
            
            gStat.LCA_global = tree->get_Global_LCA(hitted_Nodes);
            gStat.number_of_leaves = tree->get_Number_Of_Node_Leaves(gStat.LCA_global);
            gStat.number_of_hitted_leaves = tree->getNumberOfHits(gStat.LCA_global, hitted_Indices);
            gStat.demoneratorGX = tree->get_demonrator_GX(gStat.LCA_global, hitted_Indices);
            gStat.GX = (double)gStat.number_of_leaves / (double)gStat.demoneratorGX;
        
            
            final_output << gStat.LCA_global.uid  << "\t";
            final_output << tree->get_level(gStat.LCA_global) << "\t" ;
            final_output << gStat.number_of_leaves << "\t" ;
            final_output << gStat.number_of_hitted_leaves << "\t";
            final_output << gStat.demoneratorGX << "\t";
            final_output << gStat.GX << "\t";
            
            if(hitted_Indices.size() <= 5)
            {
                for(LONGS k = 0 , nnk = hitted_Nodes.size() ; k < nnk ; ++k)
                {
                    final_output << hitted_Nodes[k].uid << "\t";
                }
                
            }
            
        
       final_output << endl;
    }
    
    final_output.flush();
    final_output.close();
    
    
    
    
    
    for (LONGS i = 0 , n = random_kmers.size(); i < n ; ++i)
    {
        random_kmers[i] &= hash_pattern;
    }
    
    for (LONGS i = 0 , n = sorted_YRJ_nodes.size(); i < n ; ++i)
    {
        sorted_YRJ_nodes[i]->Hash_the_kmers(hash_pattern);
    }
    
    final_output.open(path_to_the_results + name_of_in_exact_output );
    
    
    
    
    
    /*
     
     
     repetition
     
     */
    
    final_output << "kmerIndex  kmer    Number_hits LCA level   number_of_leaves    number_of_hitted_leaves GX_dem  GX  Uids_up_to_5\n";;
    for (LONGS i , n = random_kmers.size() ; i < n ; ++i)
    {
        hitted_Indices.clear();
        hitted_Nodes.clear();
        build_vector( random_kmers[i] , sorted_YRJ_nodes ,   hitted_Indices );
        
        LONGS number_Of_Hits = hitted_Indices.size();
        
        final_output << i << "\t";
        final_output << random_kmers[i] << "\t";
        final_output << number_Of_Hits << "\t";
        
        if(number_Of_Hits == 0)
        {
            final_output << "\n";
            continue;
        }
        
        
        
        for(std::vector<LONGS>::iterator it = hitted_Indices.begin(); it != hitted_Indices.end(); ++it)
        {
            hitted_Nodes.push_back(tree->getNodeFromIndex(*it));
        }
        
        
        G_Statistics gStat;
        
        gStat.LCA_global = tree->get_Global_LCA(hitted_Nodes);
        gStat.number_of_leaves = tree->get_Number_Of_Node_Leaves(gStat.LCA_global);
        gStat.number_of_hitted_leaves = tree->getNumberOfHits(gStat.LCA_global, hitted_Indices);
        gStat.demoneratorGX = tree->get_demonrator_GX(gStat.LCA_global, hitted_Indices);
        gStat.GX = (double)gStat.number_of_leaves / (double)gStat.demoneratorGX;
        
        
        final_output << gStat.LCA_global.uid  << "\t";
        final_output << tree->get_level(gStat.LCA_global) << "\t" ;
        final_output << gStat.number_of_leaves << "\t" ;
        final_output << gStat.number_of_hitted_leaves << "\t";
        final_output << gStat.demoneratorGX << "\t";
        final_output << gStat.GX << "\t";
        
        if(hitted_Indices.size() <= 5)
        {
            for(LONGS k = 0 , nnk = hitted_Nodes.size() ; k < nnk ; ++k)
            {
                final_output << hitted_Nodes[k].uid << "\t";
            }
        }
        
        final_output << endl;

        
    }
    
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
    
    
    
    
    
    
    
    
    
