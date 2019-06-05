//
//  RosterReader.cpp
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 05/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#include "RosterReader.h"

void RosterReader::get_data()
{
    ifstream fin;
    
    fin.open(file_dir);
    
    vector<string> row_vec;
    string line;
    
    while(getline(fin, line))
    {
        row_vec.clear();
        
        //while the delimeter still exists in the string
        while(line.find(file_delim) != string::npos)
        {
            string entry = line.substr(0, line.find(file_delim));
            
            row_vec.push_back(entry);
            
            line.erase(0, line.find(file_delim) + file_delim.length());
        }
        
        data_vec.push_back(row_vec);
        
    }
    
    
    
}
