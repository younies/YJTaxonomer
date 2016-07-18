//
//  YRJ.cpp
//  building_vectors
//
//  Created by Younies Mahmoud on 7/15/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "YRJ.hpp"


YRJ::~YRJ()
{
    free(this->kmersVector);
}

YRJ::YRJ(string path_to_file)
{
    this->path_to_file = path_to_file;
    ifstream fileStream(path_to_file);
    fileStream.read( (char *)&this->kmerLength  , sizeof(LONG));
    fileStream.read( (char *) &this->numOfKmers , sizeof(LONG));
    this->kmersVector = new LONG [this->numOfKmers];
    
    fileStream.read((char *)kmersVector, this->numOfKmers * sizeof(LONG));
    
    fileStream.close();
}




bool YRJ::isKmerExist(LONG kmer)
{
    LONGS start = 0  , mid;
    LONGS end = this->numOfKmers - 1;
    
    while (end >= start)
    {
        mid = (start + end)/2;
        if(this->kmersVector[mid] == kmer)
            return true;
        else if (this->kmersVector[mid] > kmer)
            end = mid - 1;
        else
            start = mid + 1;
    }
    
    return false;
}





vector<LONG> YRJ::getRandomSamples(string file_path , LONGS numOfSamples)
{
    
    vector<LONG> samples(numOfSamples);
    /*
    for (LONGS i = 0 ; i <  numOfSamples; ++i)
    {
        samples[i] = this->kmersVector[i];
    }
    
    cerr << "finish samples\n" ;
    */
    
    ifstream fileStream(file_path);
    string line;
    LONG indx;
    LONG pointer = 0;
    while (getline(fileStream, line) && pointer < numOfSamples)
    {
        stringstream ss(line);
        ss >> indx;
        //cerr << kmerLength << "   " << numOfKmers << "  " << indx << endl;
        samples[pointer] = this->kmersVector[indx];
        ++pointer;
    }
    fileStream.close();
    
    free(this->kmersVector);
    
    return samples;
}








