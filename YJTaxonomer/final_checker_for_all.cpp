//
//  final_checker_for_all.cpp
//  YJTaxonomer
//
//  Created by Younies Mahmoud on 7/23/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "configuration.h"
#include "headers.h"
#include "node_reader.hpp"
#include "tree_builder.hpp"
#include "YRJ.hpp"
#include "YJR_Hero_Tester.hpp"



int main()
{
    //creat the random sample class
    YRJ_Hero_Vector * hero_vector = new YRJ_Hero_Vector(path_to_the_genomes_database +"all.yrj" ,path_to_random_numbers, random_number_size , hash_pattern ,  kmer_length_long);
}