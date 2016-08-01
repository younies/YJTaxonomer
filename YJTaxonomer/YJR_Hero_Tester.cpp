//
//  YJR_Hero_Tester.cpp
//  YJTaxonomer
//
//  Created by Younies Mahmoud on 7/31/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "YJR_Hero_Tester.hpp"


YRJ_Hero_Vector::YRJ_Hero_Vector(string file_path, string random_kmer_path , LONGS numOfSamples , LONG hash , LONGS kmer_length) : YRJ(file_path)
{
    this->kmer_length = kmer_length;
    this->random_Kmers =   this->getRandomSamples( random_kmer_path ,numOfSamples );
    this->hash_map.resize(numOfSamples);
    
    
    //initialize the hash mapper
    LONGS index;
    for(LONGS i = 0 ; i < numOfSamples ; ++ i)
    {
        index = (this->random_Kmers[i] & hash )% numOfSamples;
        this->hash_map[index].push_back(i);
    }
}
