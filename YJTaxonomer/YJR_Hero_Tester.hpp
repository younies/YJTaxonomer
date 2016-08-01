//
//  YJR_Hero_Tester.hpp
//  YJTaxonomer
//
//  Created by Younies Mahmoud on 7/31/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef YJR_Hero_Tester_hpp
#define YJR_Hero_Tester_hpp

#include "headers.h"
#include "YRJ.hpp"


class YRJ_Hero_Vector: YRJ {
    
    
    LONGS kmers_test_numbers;
    LONGS kmer_length;
    LONG hash;
    vector<LONG> random_Kmers;
    vector<vector<LONGS> > hash_map;
    
public:
    YRJ_Hero_Vector(string file_path, string random_kmer_path , LONGS numOfSamples, LONG hash , LONGS kmer_length) ;
    
    vector<int> int_vector_result(YRJ &yrj);
    
    int get_the_less_number_of_different(vector<LONGS> & indices_vector , LONG kmer);
    
    void update_vector_information( vector<int> & result_vector, vector<LONGS> & indices_vector , LONG kmer );
    
    int get_number_of_differences_between_two_kmers(LONG kmer1 , LONG kmer2);
    
    LONGS get_kmers_test_numbers(){return this->kmers_test_numbers;}
    
    LONG get_kmer_with_index(LONGS index){return this->random_Kmers[index];}
};





#endif /* YJR_Hero_Tester_hpp */
