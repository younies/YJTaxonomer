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
//####

#include "headers.h"


//the class that contains all the required data structures for the tree



class Tree_trie {
    
    //pathes to the node and names files
    string path_nodes;
    string path_names;
    
    vector< LONG> ids;//holds the uid for each node index
    vector<vector<string > > names;//it associate all the names for a node in the tree
    vector<string  > levels; // this specify the level for each node (if it is species, genus .... and so on)
    vector< Node > trie;// holds all the trie nodes starting with the root
    
    
    vector<Node> sorted_leafs_df; // this vector holds the indices  of sorted leafs in the depth first order
    LONGS strTolong(string s); // this function convert the string to integer type (long long)
    
    // for constructing the tree
    void construct_ids_names(); // this method construct the ids and names vector
    void constructing_trie(); // this method construct the trie
    void construct_sorted_leafs(LONG index  = 0 ); //this method construct the sorted leafs vector
    
public:
    Tree_trie(string path_names , string path_nodes);// the default constructor
    
    string getLevel(LONGS position); // method for getting the type of an index node
    
    LONGS uid_to_index(LONG uid);// methid that convert from node id to its index
    
    
    vector<LONGS> get_All_Parents(Node node);
    LONGS get_LCA_between_Two_Nodes(Node node1 , Node node2);
    Node get_Global_LCA(vector<Node> nodes);
    
    
    LONGS get_Number_Of_Node_Leaves(Node node);
    
    
    Node getNodeFromIndex(LONGS index);
    
    vector<LONG> getSortedLeafsUIDs();
};





#endif /* tree_builder_hpp */
