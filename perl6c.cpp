#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace perl6 {
    template<typename Iterator>
    struct perl6_grammar: qi::grammar<Iterator, ascii::space_type>
    {
        perl6_grammar(): perl6_grammar::base_type(TOP)
        {
            TOP = ascii::char_;
        }

        qi::rule<Iterator, ascii::space_type> TOP;
    };
}

int main(int argc, char** argv) {
    using namespace std;

    char const* filename;
    if (argc > 1) 
        filename = argv[1];
    else  {
        cerr << "No input file.\n";
        return 1;
    }

    ifstream in(filename, std::ios_base::in);
    
    if (!in) {
        cerr << "No such file: " << filename << "\n";
        return 1;
    }

    string source;
    in.unsetf(std::ios::skipws);
    copy(istream_iterator<char>(in), istream_iterator<char>(), back_inserter(source));

    perl6::perl6_grammar<string::const_iterator> perl6_parser;
    string::const_iterator iter = source.begin();
    string::const_iterator end = source.end();
    bool parse_result = phrase_parse(iter, end, perl6_parser, ascii::space);
    
    cout << parse_result << endl;
    
    return 0;
}
