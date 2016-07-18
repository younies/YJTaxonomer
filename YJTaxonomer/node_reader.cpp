//
//  node_reader.cpp
//  kraken_database
//
//  Created by Younies Mahmoud on 6/27/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
/*
 This file is for reading the nodes file
 */

#include "node_reader.hpp"





void Tree::construct_ids_names()
{
    string line;
    ifstream names_file(path_names);

    int pointer = -1;
    bool newLine = true;
    while(getline(names_file, line ,'\t' ))
    {
        cerr << line << endl;

        
        if(newLine)
        {
            cerr << "newLine " << endl;
            pointer++;
            newLine = false;
            //cerr << pointer << endl;
            //long id = stol(line ,&sz);
            
            this->ids.push_back((int)this->strTolong(line));
            vector<string> newVec;
            this->names.push_back(newVec);
            
        }
        else
        {
            if(line[0] == '$')
            {
                cerr << line << " ggg  $\n";
                newLine = true;
                //continue;
            }
            else
                this->names[pointer].push_back(line);
        }
    }
    
    cout << " idsize and names size\n";
    cout << this->ids.size() << "   " <<this->names.size() << endl;
    
}








void Tree::constructing_trie()
{
    string line;
    ifstream names_file(this->path_nodes);
    int pointer = -1;
    int parent;
    
    this->trie.resize(this->ids.size() , vector<int>());
    this->types.resize(this->ids.size() );
    
    vector<int>::iterator it;
//    vector<int>::iterator beg = this->ids.begin();
//    vector<int>::iterator end = this->ids.end();
    
    while(getline(names_file, line ,'\t'))
    {
        pointer++;
        getline(names_file, line ,'\t');
        parent = (int)this->strTolong(line);
        cerr << ids[pointer] << endl;
        
        parent = this->id_to_index(parent);
        cerr <<  pointer << "   "<< parent  << "   id"<< endl;
        this->trie[parent].push_back(pointer);
        getline(names_file, line ,'\t');
        this->types[pointer] = line;
        
        getline(names_file, line );
        
    }
    
    
}












Tree::Tree(string path_names , string path_nodes)
{
    this->path_names = path_names;
    this->path_nodes = path_nodes;
   
    this->construct_ids_names();
    this->constructing_trie();
    this->construct_sorted_leafs(0);
}


long long Tree::strTolong(string s)
{
    long long ret = 0;
    for(long long i = 0 , n = (int)s.size() ; i < n ; ++ i)
    {
        ret = ret * 10 + s[i] - '0' ;
    }
    
    return ret;
    
}



void Tree::construct_sorted_leafs(int node)
{
    cerr << trie.size() << endl;
    int count =0 ;
    for (int i = 0 ; i < 1000000; ++i)
    {
       // trie[i].push_back(10);
        cerr << trie[i].size() << endl;
    }
    
    if(this->trie[node].size() < 1)
    {
        cerr << node << endl;
        this->sorted_leafs_df.push_back(node);
        return;
    }
    
    for (int i = 0 , n = (int) this->trie[node].size(); i < n ; ++i)
    {
        construct_sorted_leafs(this->trie[node][i]);
    }
    
}




string Tree::getType(int position)
{
    return this->types[position];
}






long long Tree::id_to_index(int id)
{
    long long index;
    
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




