/************************************\
 *   Copyright 2015 Jacob Gonzalez  *
 *             a1687803             *
 * -------------------------------- *
 *          (╯°□°）╯︵ ┻━┻           *
\************************************/

#include "CSVReader.h"

#include <fstream>
#include <sstream>

// the c'tor will attempt to load in the csv file straight away
CSVReader::CSVReader(std::string filename)
{
    // good will return false unless we reach the end with no issues
    _good = false;
    std::ifstream file(filename.c_str());
    if (!file.good())
    {
        return;
    }

    // get first line for headers
    std::string header = "";
    getline(file, header);

    // split headers into catagory first
    std::stringstream ss(header);
    std::string catagory;
    std::vector<std::string> catagories;
    while (getline(ss, catagory, ','))
    {
        //remove the quotations at the start/end of the names
        if (catagory[0] == '\"' && catagory[catagory.size()-1] == '\"')
        {
            catagory.erase(catagory.begin());
            catagory.erase(catagory.end()-1);
        }
        catagories.push_back(catagory);
    }
    _col_size = catagories.size();

    // get the rest of the table line by line, comma by comma
    std::string working_str;
    //read the line
    while (getline(file, working_str))
    {
        std::stringstream ss(working_str);
        // map of the catagories for this row
        std::map<std::string, std::string> col_for_row;

        // go through the items in the row
        unsigned catagory_index = 0;
        while (getline(ss, working_str, ','))
        {
            // there are to many columns. malformed csv
            // this is not super important but why not make sure
            // we have perfect csv form sizes to avoid errorslater
            if (catagory_index > catagories.size())
            {
                return;
            }
            col_for_row[catagories[catagory_index++]] = working_str;
        }
        // there are for enough rows. malformed csv
        if (catagory_index < catagories.size())
        {
            return;
        }

        _table.push_back(col_for_row);
    }

    file.close();
    _good = true;
}

bool CSVReader::good() const
{
    return _good;
}

size_t CSVReader::columns_size() const
{
    return _col_size;
}

size_t CSVReader::rows_size() const
{
    return _table.size();
}

std::map<std::string, std::string> CSVReader::get_row(size_t index)
{
    return _table[index];
}

std::map<std::string, std::string> CSVReader::operator[](size_t index)
{
    return get_row(index);
}
