//
//  RosterReader.h
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 05/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#ifndef __SwapShiftEmployeeClass__RosterReader__
#define __SwapShiftEmployeeClass__RosterReader__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
#include <vector>

using namespace std;

class RosterReader
{
    string file_dir;
    string file_delim;
    
    int file_name_col; //column (starting at 0) which contains the employee names
    
    vector<vector<string>> data_vec;
    
public:
    RosterReader(string f_dir, string delimeter = ", ", int name_col = 0) :
        file_dir(f_dir), file_delim(delimeter), file_name_col(name_col) {}
    
    void get_data();
};

#endif /* defined(__SwapShiftEmployeeClass__RosterReader__) */
