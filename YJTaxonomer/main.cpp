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


int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    Tree_trie * tree = new Tree_trie(path_to_the_names_dmp_file , path_to_the_nodes_dmp_file);
    
    Node root = tree->getNodeFromIndex(0);
    cout << tree->get_Number_Of_Node_Leaves(root) << endl;
    
    
    
    
    return 0;
}
