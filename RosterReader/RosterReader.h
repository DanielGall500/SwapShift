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
#include <vector>

using namespace std;

class RosterReader
{
    string file_dir;
    string file_delim;
    
    bool is_header; //column titles e.g Name
    
    int file_name_col; //column (starting at 0) which contains the employee names
    
    //Vector filled with entries from csv file
    vector<vector<string>> data_vec;
    
    //Vector of employee's names
    void read_all_empl_names();
    vector<string> empl_names;
    
    //Called on creation of class object
    void read_data();
    void parse_data();

	bool valid_file(string dir);
    
public:
    RosterReader(string f_dir, string delimeter = ", ", int name_col_indx = 0, bool header = false);
    
    vector<string> get_employee_names();
    
    
};

#endif /* defined(__SwapShiftEmployeeClass__RosterReader__) */
