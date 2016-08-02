//
//  count_all_genomes_length.cpp
//  YJTaxonomer
//
//  Created by Younies Mahmoud on 8/2/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "configuration.h"
#include "headers.h"
#include "node_reader.hpp"
#include "tree_builder.hpp"
#include "YRJ.hpp"
#include "YJR_Hero_Tester.hpp"


long long getTheNumber(string path)
{
    //the return type
    long long ret = 0;
    
    // initialize the input stream
    ifstream inputStream(path);
    
    //counting the letters
    string line;
    while (getline(inputStream, line))
    {
        if(line.size() > 0 && line[0] != '>')
            ret+= line.size();
    }
    inputStream.close();
    
    return ret;
}

int main()
{
    Tree_trie * tree = new Tree_trie(path_to_the_names_dmp_file , path_to_the_nodes_dmp_file);
    
    tree->build_specific_nodes(path_to_the_specific_nodes);
    
    
    vector<YRJ *> sorted_YRJ_nodes;
    vector<LONG> sorted_UIDs = tree->getSortedLeafsUIDs();
    
    vector<LONG> availableUIDs;
    
    long long count_letters_in_genome = 0;
    
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
        
        name = path_to_the_raw_genomes + to_string( sorted_UIDs[i]) + ".fa";
        
        count_letters_in_genome += getTheNumber(name);
        
    }
    
    
    cout << count_letters_in_genome << endl;
    

}