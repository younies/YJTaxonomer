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
    
    // hello to you
    cout << "hello, the program started!\n";
    
    //creating the total file
   
    YRJ * all = new YRJ(path_to_the_program_directory + name_of_the_databases + kmer_length_str + "/all.yrj");
    vector<LONG> random_kmers =  all->getRandomSamples(path_to_random_numbers, random_number_size);
    
    
    
    
    
    
    return 0;
}
