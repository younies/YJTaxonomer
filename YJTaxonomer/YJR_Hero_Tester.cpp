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
    this->kmers_test_numbers = numOfSamples;
    this->hash = hash;
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




vector<int> YRJ_Hero_Vector::int_vector_result(YRJ &yrj)
{
    vector<int> vec_ret(this->kmers_test_numbers , (int)this->kmer_length);
    
    LONG kmer;
    
    for (LONGS i , n = yrj.get_kmers_numbers(); i < n ; ++i)
    {
        kmer = yrj.get_kmer_index(i);
        vector<LONGS> vector_indices = this->hash_map[(kmer & this->hash) % this->kmers_test_numbers];
        update_vector_information(vec_ret, vector_indices, kmer);
    }
    
    
    
    return vec_ret;
}




void YRJ_Hero_Vector::update_vector_information( vector<int> & result_vector, vector<LONGS> & indices_vector , LONG kmer )
{
    LONG temp_kmer;
    LONGS index;
    for(LONGS i = 0 , n =  indices_vector.size(); i < n ;++i )
    {
        index = indices_vector[i];
        temp_kmer = this->random_Kmers[index];
        result_vector[index] = min(result_vector[index] , get_number_of_differences_between_two_kmers(kmer, temp_kmer));
    }
    
}



int YRJ_Hero_Vector::get_number_of_differences_between_two_kmers(LONG kmer1 , LONG kmer2)
{
    int ret = 0;
    LONGS letters = this->kmer_length;
    
    
    while (letters--)
    {
        if(  kmer1%4 != kmer2%4  ) ret++;
        kmer1 >>= 2;
        kmer2 >>= 2;
    }
    
    return ret;
}





int YRJ_Hero_Vector::get_the_less_number_of_different(vector<LONGS> & indices_vector , LONG kmer)
{
    LONGS index;
    
    int less_differences = (int)this->kmer_length;
    
    for (LONGS i = 0  , n = indices_vector.size();  i< n ; ++i)
    {
        index = indices_vector[i];
        
        less_differences = min(less_differences,   get_number_of_differences_between_two_kmers(kmer , this->random_Kmers[index]) );
    }
    
    return less_differences;
}


