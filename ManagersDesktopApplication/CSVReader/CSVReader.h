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
#include "globals.h"

using namespace std;

class CSVReader
{
    //File Directory & Delimeter
    string file_dir,
           file_delim;
    
    //Vector Which Holds CSV File
    vectorStr2D csv_vector;
    
    //Stream From File
    ifstream input_stream;

    //Ignore any lines which contain the following strings
    vectorStr str_to_ignore;

    //Check if a string is a substring of another
    bool contains_str(string orig, string substr);

    //Check if string is empty
    bool empty_line(string line);
    
    
public:
    CSVReader(string dir, vectorStr str_to_ignore, string file_delim = ",");
    
    //Check If File Opens
    bool open_file();
    
    //Read CSV File
    vectorStr2D read_csv();
    
};

#endif /* defined(__SwapShiftProject__CSVReader__) */
