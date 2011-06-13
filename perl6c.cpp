#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

int main(int argc, char** argv) {
    using namespace std;

    char const* filename;
    if (argc > 1) 
        filename = argv[1];
    else  {
        cerr << "No input file.\n";
        return 1;
    }

    std::ifstream in(filename, std::ios_base::in);
    
    if (!in) {
        cerr << "No such file: " << filename << "\n";
        return 1;
    }

    string source;
    in.unsetf(ios::skipws);
    copy(istream_iterator<char>(in), istream_iterator<char>(), back_inserter(source));
    
    cout << source;
    
    return 0;
}
