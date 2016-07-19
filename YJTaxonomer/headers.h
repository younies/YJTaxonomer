//
//  headers.h
//  building_vectors
//
//  Created by Younies Mahmoud on 7/15/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef headers_h
#define headers_h

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdint.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sysexits.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <fstream>

//headaers for the program itself




using namespace std;

typedef unsigned long LONG;
typedef long LONGS;


struct Node {
    LONG uid;
    LONG parentUID;
    LONGS parentIndex;
    LONGS myselfIndex;
    vector<LONG> children;
};



struct G_Statistics
{
    LONG kmer;
    LONGS number_of_leaves;
    LONGS number_of_hitted_leaves;
    Node LCA_global;
    LONGS demoneratorGX;
    LONGS GX;
    
};

#endif /* headers_h */
