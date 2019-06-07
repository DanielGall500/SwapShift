//
//  RosterReader.cpp
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 05/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#include "RosterReader.h"

RosterReader::RosterReader(string f_dir, string delimeter, int name_col_indx, bool header) :
    file_dir(f_dir), file_delim(delimeter), file_name_col(name_col_indx), is_header(header)
{
	read_data();
	parse_data();
}

bool RosterReader::valid_file(string dir)
{
	return true;
}

void RosterReader::read_data()
{
    ifstream fin;
    
    fin.open(file_dir);

	if (fin.fail())
	{
		//NEED TO HANDLE THIS ERROR
		cout << "ERROR: Unable To Open File" << endl;
		getchar();
		exit(1);
	}
	else
	{
		vector<string> row_vec;
		string line;

		while (getline(fin, line))
		{
			row_vec.clear();

			//while the delimeter still exists in the string
			while (line.find(file_delim) != string::npos)
			{
				string entry = line.substr(0, line.find(file_delim));

				row_vec.push_back(entry);

				line.erase(0, line.find(file_delim) + file_delim.length());
			}

			data_vec.push_back(row_vec);
		}
	}
    
}

void RosterReader::parse_data()
{
    read_all_empl_names();
}

void RosterReader::read_all_empl_names()
{
    //First entry in name column
    string new_empl = data_vec[0][file_name_col];
    
    //If there's no column titles, names start from beginning
    if(!is_header)
        empl_names.push_back(new_empl);
      
    for(unsigned int i = 1; i < data_vec.size(); i++)
    {
        new_empl = data_vec[i][file_name_col];
        
        empl_names.push_back(new_empl);
    }
}

vector<string> RosterReader::get_employee_names()
{
    return empl_names;
}






