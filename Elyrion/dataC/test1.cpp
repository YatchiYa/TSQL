
#include <iostream>
#include <string>
#include <vector>


#include "../dataH/test1.h"


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/config/warning_disable.hpp>


namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace ascii = boost::spirit::ascii;

using namespace std;

void menu(){

    std::cout << " ************* choose an option  : " << std::endl;
    std::cout << " enter : 1  -> for the test version of the library C++/Boost " << std::endl;
    std::cout << " enter : 2  -> for the test version of the project !! " << std::endl ;
    std::cout << " enter : 0  -> to quit " << std::endl;


}





void test1()
{
    std::string input = "12345678";
    int out_int;

    qi::parse(
        // input string (iterators)
        input.begin(), input.end(),
        // parser grammar
        qi::int_,
        // output fields
        out_int);

    std::cout << "test1() parse result with Qi :  "
              << out_int << std::endl;
}

void test1_1()
{
    int value = 0;
    std::string str("123");
    std::string::iterator strbegin = str.begin();
    qi::parse(strbegin, str.end(), qi::int_, value);

    std::cout << "test1_1() parse result with Qi :  "
              << value << std::endl;
}


// using Karma
void test1_2()
{
    int value = 1234;
    std::string str;
    std::back_insert_iterator<std::string> out(str);
    karma::generate(out, karma::int_, value);

    std::cout << "test1_2() parse result with Karma :  "
              << value << std::endl;
}




void test1_3()
{
    std::string input("1.0 2.0");
    std::string::iterator strbegin = input.begin();
    std::pair<double, double> p;
    double d1 = 0.0, d2 = 0.0;

    qi::phrase_parse(strbegin, input.end(),
        qi::double_ >> qi::double_,       // parser grammar
        qi::space,                        // delimiter grammar
        d1, d2);                                 // attribute to fill while parsing

            // try to show p ! std::pair not two doubles
    std::cout << "test1_3() parse result with Qi :  <"
              << d1 <<"," << d2 <<">" << std::endl;
}







template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last)
{
        using qi::double_;
        using qi::phrase_parse;
        using ascii::space;

        bool r = phrase_parse(
            first,                          /*< start iterator >*/
            last,                           /*< end iterator >*/
            double_ >> *(',' >> double_),   /*< the parser >*/
            space                           /*< the skip-parser >*/
        );
        if (first != last) // fail if we did not get a full match
            return false;
        return r;
}

void test1_4()
{
     std::cout << "Give me a comma separated list of numbers.\n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;

    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        if (parse_numbers(str.begin(), str.end()))
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " Parses OK: " << std::endl;
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";

}


