#include "csv_reader.hpp"

/*
* read_csv: open file and create table, using information from it. 
* If func can't open file it returns void table.
*/
CSV_table read_csv(const std::string &fname) {
    using std::vector;
    using std::string;
    using std::stringstream;
    std::ifstream in(fname);

    //check file
    if (!in.is_open()) {
        std::cout << "Error: can't open " << fname << "\n";
        return vector<vector<string>> {0}; //void table
    }

    vector<vector<string>> tab {};
    vector<string> v {};

    string line {};

    while (getline(in, line)) {
        stringstream ss(line); //use to find all word from line
        string word; //use to copy word from line

        //reading all columns of the row
        while (getline(ss, word, ','))
            v.push_back(word);

        tab.push_back(v); //adding row to our table
        v.clear();
    }
    in.close();
    return tab;
}

/*
* find_expressions: find cells with expressions and replace it with result
*/

void find_expressions(CSV_table &tab) {
    for (int i = 1; i < tab.size(); i++) { //missing row with columns names
        for (int j = 0; j < tab[i].size(); j++) {
            if (tab[i][j][0] == '=')
                replace_expression(tab[i][j], tab);
        }
    }
}

void replace_expression(std::string &s,
        const CSV_table &tab) {
    using std::string;
    int pos; //end of readed string
    int row;
    int i; //to save begin of non-readed string
    int a, b; //vars from table
    char op; //to save operation
    string column_name;

    pos = i = 1; //missing =
    //find end of first column name and save it
    while (!isdigit(s[pos]))
        pos++;
    column_name = s.substr(i, pos - i);
    i = pos; //change begin of non-readed string

    //find end of the first row number
    while (isdigit(s[pos]))
            pos++;
    row = std::stoi(s.substr(i, pos - i));

    a = read_cell(tab, column_name, row);

    //save operation
    op = s[pos++];
    i = pos; //change begin of non-readed string

    column_name.clear();
    //find end of the second column name and save it
    while (!isdigit(s[pos]))
        pos++;
    column_name = s.substr(i, pos - i);
    i = pos; //change begin of non-readed string

    //find end of the second row number
    while (isdigit(s[pos]))
            pos++;
    row = std::stoi(s.substr(i, pos - i));

    b = read_cell(tab, column_name, row);

    switch (op) {
        case '+':
            s = std::to_string(a + b);
            break;
        case '-':
            s = std::to_string(a - b);
            break;
        case '*':
            s = std::to_string(a * b);
            break;
        case '/':
            s = std::to_string(a / b);
            break;
    }
}

/*
* read_cell: convert cell from column c and row r to int and return it. 
*/
int read_cell(const CSV_table &tab, const std::string &c, int r) {
    int col;

    //find column with name c
    for (col = 0; col < tab.size(); col++) {
        if (c == tab[0][col])
            break;
    }

    //if not found column
    if (col == tab[0].size()) {
        std::cout << c;
        std::cout << "Error: misstake in the table. Return 0.\n";
        return 0;
    }

    while (r >= tab.size())
        r /= 10;

    //read cell and convert to integer
    return std::stoi(tab[r][col]);
}

void write_table(const CSV_table &tab) {
    for (int i = 0; i < tab.size(); i++) {
        for (int j = 0; j < tab[i].size(); j++) {
            std::cout << tab[i][j];
            if (j != tab[i].size() - 1)
                std::cout << ',';
        }
        std::cout << std::endl;
    }
}
