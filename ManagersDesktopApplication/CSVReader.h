//
//  CSVReader.h
//  SwapShiftProject
//
//  Created by Daniel Gallagher on 22/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#ifndef __SwapShiftProject__CSVReader__
#define __SwapShiftProject__CSVReader__

#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//ADD THIS TO GLOBALS
typedef vector<vector<string>> vector2D;

class CSVReader
{
    string file_dir;
    string file_delim;
    
    vector2D csv_vector;
    
    ifstream input_stream;
    
    
public:
    CSVReader(string dir, string file_delim = ",");
    
    bool open_file();
    
    vector2D read_csv();
    
};

#endif /* defined(__SwapShiftProject__CSVReader__) */
