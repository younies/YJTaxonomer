//
//  node_reader.hpp
//  kraken_database
//
//  Created by Younies Mahmoud on 6/27/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef node_reader_hpp
#define node_reader_hpp


#include "headers.h"

class Tree {
    
    vector< int> ids;
    vector<vector<string > > names;
    vector<string  > types;
    vector< vector<int> > trie;
    string path_names;
    string path_nodes;
    
    vector<int> sorted_leafs_df;
    long long strTolong(string s);
    
    // for constructing the tree
    void construct_ids_names();
    void constructing_trie();
    void construct_sorted_leafs(int node);
    
public:
    Tree(string path_names , string path_nodes);
    
    string getType(int position);
    
    long long id_to_index(int id);
    
    
    
    
};

#endif /* node_reader_hpp */
