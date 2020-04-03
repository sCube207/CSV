#ifndef CSV_READER_HPP
#define CSV_READER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <sstream>
#include <cctype>

using CSV_table = std::vector<std::vector<std::string>>;

CSV_table read_csv(const std::string &fname);
void find_expressions(CSV_table &tab);
void replace_expression(std::string &s,
        const CSV_table &tab);
int read_cell(const CSV_table &tab,
        const std::string &column, int row);
void write_table(const CSV_table &tab);
#endif
