#include "csv_reader.hpp"

int main(int argc, char *argv[]) {
    using std::cout;
    using std::cin;
    using std::vector;
    using std::string;
    using std::fstream;

    std::string fname; 
    vector<vector<string>> table;  //Use to save our table

    //open and read csv file
    for (int i = 1; i < argc; i++) {
        std::cout << "\n"<<argv[i] << "\n\n";
        table = read_csv(argv[i]);
        find_expressions(table);
        write_table(table);
    }
    return 0;
}
