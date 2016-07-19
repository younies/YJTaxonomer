//
//  configuration.h
//  YJTaxonomer
//
//  Created by Younies Mahmoud on 7/18/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef configuration_h
#define configuration_h
#include "headers.h"
using namespace std;


//variables_string

string kmer_length_str = "31";

LONGS random_number_size = 10000000;
string path_to_random_numbers = "";

//names
string name_of_the_databases = "databases";
string name_of_output_results = "outputResults" +kmer_length_str + ".txt";


//pathes
string path_to_the_program_directory = "";
string path_to_the_genomes_database = "";
string path_to_the_names_dmp_file = "/Users/youniesmahmoud/Desktop/research/taxdump/names.txt";
string path_to_the_nodes_dmp_file = "/Users/youniesmahmoud/Desktop/research/taxdump/nodes.txt";
string path_to_the_specific_nodes = "/Users/youniesmahmoud/Desktop/research/newNmaes.txt";



#endif /* configuration_h */
