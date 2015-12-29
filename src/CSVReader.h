/************************************\
 *   Copyright 2015 Jacob Gonzalez  *
 *             a1687803             *
 * -------------------------------- *
 *          (╯°□°）╯︵ ┻━┻           *
\************************************/

#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include <map>

typedef std::vector<std::map<std::string, std::string> > table;

// Class that reads a csv file and stores it in a table format
class CSVReader
{
public:
    CSVReader(std::string filename);
    ~CSVReader()
    {}

    // get the row of the table at index
    std::map<std::string, std::string> get_row(size_t index);

    // operator to get the row at index
    std::map<std::string, std::string> operator[](size_t index);

    // get the num cols in the table
    size_t columns_size() const;
    // get the num of rows in the table
    size_t rows_size() const;

    // has the csv been loaded properly
    bool good() const;

private:
    // the table for the csv file
    table _table;
    bool _good;
    size_t _col_size;
};

#endif // CSV_READER_H
