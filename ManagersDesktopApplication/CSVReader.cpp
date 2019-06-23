//
//  CSVReader.cpp
//  SwapShiftProject
//
//  Created by Daniel Gallagher on 22/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#include "CSVReader.h"

CSVReader::CSVReader(string dir, string delim) :
file_dir(dir), file_delim(delim)
{}

bool CSVReader::open_file()
{
    input_stream.open(file_dir, ios::in);
    
    if(!input_stream)
    {
        return false;
    }
    
    return true;
}

vector2D CSVReader::read_csv()
{
    vector<string> row;
    string line;
        
    while(getline(input_stream, line))
    {
        row.clear();
            
        //Find the next delimeter
        while (line.find(file_delim) != string::npos)
        {
            string entry = line.substr(0, line.find(file_delim));
                
            row.push_back(entry);
                
            line.erase(0, line.find(file_delim) + file_delim.length());
        }
            
        //Push the final part of our line back
        row.push_back(line);
            
            
        //Add new row to our vector
        csv_vector.push_back(row);
    }
    
    return csv_vector;
    
}