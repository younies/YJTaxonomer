//
//  final_checker_for_all.cpp
//  YJTaxonomer
//
//  Created by Younies Mahmoud on 7/23/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "configuration.h"
#include "headers.h"
#include "node_reader.hpp"
#include "tree_builder.hpp"
#include "YRJ.hpp"
#include "YJR_Hero_Tester.hpp"



int main()
{
    //creat the random sample class
    YRJ_Hero_Vector * hero_vector = new YRJ_Hero_Vector(path_to_the_genomes_database +"all.yrj" ,path_to_random_numbers, random_number_size , hash_pattern ,  kmer_length_long);
    
    
    
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

    
    ofstream final_output(path_to_the_results + name_of_inexact_with_numbers);
    

    final_output << "kmerIndex  kmer    hits_numbers.......\n";

    
    vector<vector<int> > results(sorted_YRJ_nodes.size());
    
    LONGS sorted_YRJ_number =sorted_YRJ_nodes.size();
    for (LONGS i = 0, n = sorted_YRJ_nodes.size(); i < n ; ++i)
    {
        results[i] = hero_vector->int_vector_result(*sorted_YRJ_nodes[i]);
    }
    
    
    
    for (LONGS i = 0 , n =  hero_vector->get_kmers_test_numbers() ; i < n ; ++i)
    {
        final_output << i << "\t";
        final_output << hero_vector->get_kmer_with_index(i) << "\t";
        for (LONGS j = 0; j < sorted_YRJ_number ; ++j)
        {
            final_output << results[j][i] << "\t";
        }
        
        final_output << endl;
    }
    
    
    
    
    
    
}