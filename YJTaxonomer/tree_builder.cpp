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
    construct_sorted_leafs();
    printf("all done !!!!  for the trie \n");
}

//implementing the: construct_ids_names()
void Tree_trie::construct_ids_names()
{
    //open the names file
    ifstream file_names(path_names);
    if(!file_names.is_open())
    {
        cerr << "we coud not find the file for names for : " + path_names << endl;
        return;
    }
    //read from the file line by line
    string line;
    LONG uid;
    string name;
    
    LONGS index = -1;
    while (getline(file_names, line, '\n'))
    {
        index++;
        //put the line in the string stream
        stringstream liness(line);
        
        // pushing the id
        liness >> uid;
        this->ids.push_back(uid);
        
        vector<string> temp;
        names.push_back(temp);
        getline(liness, name, '\t'); // to remove the first tab
        while (getline(liness, name, '\t'))
        {
            names[index].push_back(name);
        }
        
    }
    printf("building ids : %d , names : %d  \n", (int)ids.size() , (int)names.size());
}
//#########end of the: construct_ids_names()


//constructing the: constructing_trie()

void Tree_trie::constructing_trie()
{
    //open the node file
    ifstream file_nodes(path_nodes);
    if(!file_nodes.is_open())
    {
        cerr << "the file to the nodes does not exist for: " + path_nodes << endl;
        return;
    }
    
    
    //read from the file line by line
    string line;
    LONGS myselfUID;
    LONGS parentUID;
    string level;
    LONGS index = -1;
    LONGS myselfIndex;
    LONGS parentIndex;
    
    //resize the trie
    trie.resize((int)ids.size());
    levels.resize((int)ids.size());
    while (getline(file_nodes, line, '\n'))
    {
        index++;
        // put the line in stringstream
        stringstream liness(line);
        
        liness >> myselfUID;
        liness >> parentUID;
        liness >> level;
        
        myselfIndex = uid_to_index(myselfUID);
        parentIndex = uid_to_index(parentUID);
        levels[index] = level;
        
        //checking
        if(myselfIndex != index)
            cerr << "there is a problem" << endl;
        
        //to initialize an element
        trie[index].uid = myselfUID;
        trie[index].parentUID = parentUID;
        trie[index].myselfIndex = myselfIndex;
        trie[index].parentIndex = parentIndex;

        if( (parentIndex  !=  myselfIndex) )
            trie[parentIndex].children.push_back(myselfIndex);
    }
    
    printf("trie is constructed .......\n");
    
}
//### end of the: constructing_trie()




LONGS Tree_trie::uid_to_index(LONG uid)
{
    LONGS index;
    LONGS n = (int)ids.size();
    
    LONGS first = 0 , last = n - 1;
    while(last >= first)
    {
        index = (first+last)/2;
        if(ids[index] == uid)
            return index;
        
        if(ids[index] > uid)
            last = index - 1;
        else
            first = index + 1;
    }
    index = - 1;
    return index;
    

}


// implementation of the : construct_sorted_leafs(int node)

void Tree_trie::construct_sorted_leafs(LONG index )
{
    
    
    
    LONGS n = (LONGS)trie[index].children.size();
    
    if(n < 1)
    {
        if(this->is_specific_leaves == false ||  this->is_this_Index_node_specified(index)  )
            sorted_leafs_df.push_back(trie[index]);
        return;
    }
    
    //if(levels[node])
    
    for (int i = 0 ; i < n ; ++i)
    {
        
        construct_sorted_leafs(trie[index].children[i]);
    }
}




vector<LONG> Tree_trie::getSortedLeafsUIDs()
{
    LONGS n = (LONGS)sorted_leafs_df.size() ;
    vector<LONG> ret(n);
    
    for(int i= 0 ; i < n ; ++i)
        ret[i] = sorted_leafs_df[i].uid;
    return ret;
}


vector<LONGS> Tree_trie::get_All_Parents(Node node)
{
    vector<LONGS> ret;
    LONGS final_parent = node.myselfIndex;
    ret.push_back(final_parent);

    while(final_parent != 0)
    {
        final_parent = trie[final_parent].parentIndex;
        ret.push_back(final_parent);
    }
    
    return ret;
}






LONGS Tree_trie::get_LCA_between_Two_Nodes(Node node1 , Node node2)
{
    vector<LONGS> parents_node1 = get_All_Parents(node1);
    
    sort(parents_node1.begin() , parents_node1.end());
    
    vector<LONGS> parents_node2 = get_All_Parents(node2);
    
    for (LONGS i = 0  , n = parents_node2.size() ; i < n ; ++i)
    {
        if(binary_search(parents_node1.begin(), parents_node1.end(), parents_node2[i]))
            return parents_node2[i];
    }
    
    cerr << "Error: does not find the mutual LCA :(\n";
    
    return -1;
}



Node Tree_trie::get_Global_LCA(vector<Node> nodes)
{
    Node ret;
    LONGS nodesSize = nodes.size();
    if(nodesSize < 1)
    {
        ret.myselfIndex = -1;
        cerr << "the global LCA function takes Empty set of nodes\n";
        return ret;
    }
    else if (nodesSize == 1)
        return nodes[0];
    
    ret = nodes[0];
    for (LONGS i = 1 ;  i < nodesSize ; ++i)
    {
        ret = trie[  get_LCA_between_Two_Nodes(ret , nodes[i])   ];
    }
    return ret;
}






LONGS Tree_trie::get_Number_Of_Node_Leaves(Node node)
{
    LONGS childrenNumber = node.children.size();
    
    if(childrenNumber == 0)
       {
           if( this->is_specific_leaves == false || this->is_this_Index_node_specified(node.myselfIndex)    )
               return  1;
           else
               return 0;
       }
    LONGS ret = 0;
    
    for (int i = 0 ; i < childrenNumber; ++i)
    {
        ret += get_Number_Of_Node_Leaves(trie[node.children[i]]);
    }
    return ret;
}




LONGS Tree_trie::getNumberOfHits(Node node , vector<LONGS> &indicies)
{
    LONGS ret = 0;
    if(binary_search(indicies.begin(), indicies.end(), node.myselfIndex))
        ret += 1;
    
    for (LONGS i = 0 , childerenNumber = node.children.size(); i < childerenNumber ; ++i)
    {
        ret += getNumberOfHits( trie[ node.children[i]  ] , indicies);
    }
    
    return ret;
}



Node Tree_trie::getNodeFromIndex(LONGS index)
{
    return trie[index];
}





void Tree_trie::get_hitted_nodes(Node node , vector<LONGS> & sorted_indicies , vector<Node> & hitted_Nodes )
{
    if ( binary_search(sorted_indicies.begin(), sorted_indicies.end(), node.myselfIndex) )
    {
        hitted_Nodes.push_back(node);
    }
    
    for (LONGS i = 0 , n = node.children.size(); i < n ; ++i)
    {
        get_hitted_nodes(trie[ node.children[i] ] ,  sorted_indicies ,  hitted_Nodes );
    }
    
    return;
}





void Tree_trie::build_specific_nodes(string path_to_nodes)
{
    ifstream file_to_nodes(path_to_nodes);
    if(!file_to_nodes.is_open())
    {
        cerr <<"there is no file for the specific node\n";
        return;
    }
    
    
    this->is_specific_leaves = true;
    this->path_to_specific_names = path_to_nodes;
    
    string line;
    LONGS UID;
    while (getline(file_to_nodes, line))
    {
        stringstream liness(line);
        liness >> UID;
        this->specific_nodes_indices_sorted.push_back(uid_to_index(UID));
    }
    file_to_nodes.close();
    
    //sort the vector
    sort(this->specific_nodes_indices_sorted.begin(), this->specific_nodes_indices_sorted.end());
    
    //for constructing the sorted leafs again
    this->sorted_leafs_df.clear();
    this->construct_sorted_leafs();
}




void Tree_trie::update_specific_nodes(vector<LONG> UIDs)
{
    this->specific_nodes_indices_sorted.clear();
    for (LONGS i = 0 , n = UIDs.size(); i < n ; ++i)
    {
        this->specific_nodes_indices_sorted.push_back(uid_to_index(UIDs[i]));
    }
    
    //sort the vector
    sort(this->specific_nodes_indices_sorted.begin(), this->specific_nodes_indices_sorted.end());
    
    //for constructing the sorted leafs again
    this->sorted_leafs_df.clear();
    this->construct_sorted_leafs();
}



bool Tree_trie::is_this_Index_node_specified(LONGS index)
{
    return binary_search(this->specific_nodes_indices_sorted.begin(), this->specific_nodes_indices_sorted.end(), index);
}










LONGS Tree_trie::get_demonrator_GX(Node node , vector<LONGS> & indices)
{
    LONGS ret = 0;
    for (LONGS i = 0 , n = node.children.size(); i < n ; ++i)
    {
        vector<Node> hitted_nodes;
        
        get_hitted_nodes( getNodeFromIndex(node.children[i]) , indices , hitted_nodes );
        
        if(hitted_nodes.size() < 1)
            continue;
        
        Node current_LCA = get_Global_LCA(hitted_nodes);
        
        ret += get_Number_Of_Node_Leaves(current_LCA);
    }
    
    return ret;
}






