//
//  CSVReader.cpp
//  SwapShiftProject
//
//  Created by Daniel Gallagher on 22/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#include "CSVReader.h"

CSVReader::CSVReader(string dir, vectorStr str_to_ignore, string delim) :
file_dir(dir), file_delim(delim), str_to_ignore(str_to_ignore)
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

vectorStr2D CSVReader::read_csv()
{
    vector<string> row;
    string line;
    bool ignore_line;
        
    while(getline(input_stream, line))
    {
        ignore_line = false;
        row.clear();

        //Check if line is empty
        if(empty_line(line))
            continue;

        //Check if this line should be ignored
        for(string &s : str_to_ignore)
        {
            if(contains_str(line, s))
            {
                ignore_line = true;
                break;
            }
        }

        if(!ignore_line)
        {
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
    }
    
    return csv_vector;
    
}

bool CSVReader::empty_line(string line)
{
    if(line.empty())
        return true;
}

bool CSVReader::contains_str(string orig, string substr)
{
    //Check if substr is contained within orig
    if(orig.find(substr) != string::npos)
        return true;

    return false;
}





