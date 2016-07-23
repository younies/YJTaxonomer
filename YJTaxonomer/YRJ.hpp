//
//  YRJ.hpp
//  building_vectors
//
//  Created by Younies Mahmoud on 7/15/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef YRJ_hpp
#define YRJ_hpp
#include "headers.h"
#include <stdio.h>


class YRJ {
    LONG kmerLength;
    LONG numOfKmers;
    string path_to_file;
    LONG * kmersVector;
    
    Node trie_node;
    
public:
    YRJ(string path_to_file);
    ~YRJ() ;
    bool isKmerExist(LONG kmer);
    //LONG getRandomSamples(vector<LONG> &samples , LONG numOfSamples);
    vector<LONG> getRandomSamples(string file_path, LONGS numOfSamples);// this function free all the memory after getting the samples
    
    void set_trie_node(Node node);
    
    LONGS getTrie_Index();
    LONGS get_kmers_numbers(){return this->numOfKmers;}
    LONG get_kmer_index(LONGS index);
};

#endif /* YRJ_hpp */
