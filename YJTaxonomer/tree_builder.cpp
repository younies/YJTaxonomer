//
//  tree_builder.cpp
//  kraken_database
//
//  Created by Younies Mahmoud on 6/30/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "tree_builder.hpp"

//implementing the defaul constructor
Tree_trie::Tree_trie(string path_names , string path_nodes)
{
    this->path_names = path_names;
    this->path_nodes = path_nodes;
    construct_ids_names();
    constructing_trie();
    construct_sorted_leafs(0);
    cerr << count << endl;
    printf("all done !!!!  %d \n", (int)this->sorted_leafs_df.size());
}


//implementing the: construct_ids_names()
void Tree_trie::construct_ids_names()
{
    //open the names file
    ifstream names_file(path_names);
    
    //read from the file line by line
    string line;
    int id;
    string name;
    int index = -1;
    while (getline(names_file, line, '\n'))
    {
        index++;
        //put the line in the string stream
        stringstream liness(line);
        
        // pushing the id
        liness >> id;
        ids.push_back(id);
        vector<string> temp;
        names.push_back(temp);
        getline(liness, name, '\t'); // to remove the first tab
        while (getline(liness, name, '\t'))
        {
            names[index].push_back(name);
        }
        
    }
    printf("building ids : %d , names : %d \n", (int)ids.size() , (int)names.size());
}
//#########end of the: construct_ids_names()


//constructing the: constructing_trie()

void Tree_trie::constructing_trie()
{
    //open the node file
    ifstream nodes_file(path_nodes);
    
    //read from the file line by line
    string line;
    int child;
    int parent;
    string level;
    int index = -1;
    
    //resize the trie
    trie.resize((int)ids.size());
    levels.resize((int)ids.size());
    while (getline(nodes_file, line, '\n'))
    {
        index++;
        // put the line in stringstream
        stringstream liness(line);
        
        liness >> child;
        liness >> parent;
        liness >> level;
        
        child = id_to_index(child);
        parent = id_to_index(parent);
        levels[index] = level;
        
        //checking
        if(child != index)
            cerr << "there is a problem" << endl;
        
        //to initialize an element
        trie[child].first = parent;
        if( !(parent == 0 && child == 0) )
            trie[parent].second.push_back(child);
    }
    
    printf("trie is constructed .......\n");
    
}
//### end of the: constructing_trie()





int Tree_trie::id_to_index(int id)
{
    int index;
    

    
    int n = (int)ids.size();
    
    int first = 0 , last = n - 1;
    while(last >= first)
    {
        index = (first+last)/2;
        if(ids[index] == id)
            return index;
        
        if(ids[index] > id)
            last = index - 1;
        else
            first = index + 1;
    }
    
    index = - 1;
    return index;
    

}


// implementation of the : construct_sorted_leafs(int node)

void Tree_trie::construct_sorted_leafs(int node)
{
    int n = (int)trie[node].second.size();
    if(n < 1)
    {
        sorted_leafs_df.push_back(node);
        return;
    }
    
    //if(levels[node])
    
    for (int i = 0 ; i < n ; ++i)
    {
        
        construct_sorted_leafs(trie[node].second[i]);
    }
}












vector<int> Tree_trie::getSortedLeafsUIDs()
{
    int n = (int)sorted_leafs_df.size() ;
    vector<int> ret(n);
    
    for(int i= 0 ; i < n ; ++i)
        ret[i] = ids[sorted_leafs_df[i]];
    return ret;
}







