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



//variables

string pattern = "##-#--###---#-#-#-#-#--#-##--##";
LONG hash_pattern = 4378607365427089167;

//variables_string

string kmer_length_str = "31";
LONGS kmer_length_long = 31;

LONGS random_number_size = 1000000;
string path_to_random_numbers = "/export1/project/hondius/newKrakenResearch/generate_unique_random/MillionRandomIndices.txt";

//names
string name_of_the_databases = "databases";
string name_of_output_results = "outputResults_newUIDs" +kmer_length_str + "_withKmers_withUIDS_with_levels.txt";

string name_of_genome_classified = "the_classified_genome.txt";



//names of the files

string path_to_the_results = "/export1/project/hondius/newKrakenResearch/final_results/";
string name_of_exact_output = "exact_output_file.txt";
string name_of_in_exact_output = "in_exact_output_file.txt";
string name_of_exact_hits = "exact_hits_file.txt";
string name_of_in_exact_hits = "in_exact_hits_file.txt";

//pathes
string path_to_the_program_directory = "/export1/project/hondius/newKrakenResearch/";
string path_to_the_genomes_database = "/export1/project/hondius/newKrakenResearch/databases/kmerDatabase_new_31/";
string path_to_the_names_dmp_file = "/export1/project/hondius/newKrakenResearch/databases/names.txt";
string path_to_the_nodes_dmp_file = "/export1/project/hondius/newKrakenResearch/databases/nodes.txt";
string path_to_the_specific_nodes = "/export1/project/hondius/newKrakenResearch/databases/uids_new.txt";




#endif /* configuration_h */
