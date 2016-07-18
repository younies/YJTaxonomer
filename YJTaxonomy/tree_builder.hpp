//
//  tree_builder.hpp
//  kraken_database
//
//  Created by Younies Mahmoud on 6/30/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef tree_builder_hpp
#define tree_builder_hpp


//for including all the required headers
#include "kraken3_headers.h"
//####


#include <stdio.h>



//the class that contains all the required data structures for the tree

class Tree_trie {
    
    vector< int> ids;//which holds for each node index the associate id (in integer value)
    vector<vector<string > > names;//it associate all the names for a node in the tree
    vector<string  > levels; // this specify the level for each node (if it is species, genus .... and so on)
    vector< pair < int , vector<int> > > trie;// it holds for each node the parent index of this node and all the child of this node
    string path_names; // the path for the names file
    string path_nodes; // the path for th nodes file
    
    vector<int> sorted_leafs_df; // this array holds the sorted leafs in the depth first order
    long long strTolong(string s); // this function convert the string to integer type (long long)
    
    // for constructing the tree
    void construct_ids_names(); // this method construct the ids and names vector
    void constructing_trie(); // this method construct the trie
    void construct_sorted_leafs(int node); //this method construct the sorted leafs vector
    
public:
    Tree_trie(string path_names , string path_nodes);// the default constructor
    
    string getType(int position); // method for getting the type of an index node
    
    int id_to_index(int id);// methid that convert from node id to its index
    int count = 0;
    
    vector<int> getSortedLeafsUIDs();
};





#endif /* tree_builder_hpp */
