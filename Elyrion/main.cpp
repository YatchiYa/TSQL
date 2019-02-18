/*
    this is a first test of the simple query of the sql statement
    using the boot spirit laibrairies
    this exemple, handles only an exemple like :
    e.g : SELECT * FROM TABLE ;

*/


#include <boost/spirit.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

#include "dataH/grammar_controller.h"
#include "dataH/views.h"


int main(int argc, char* argv[])
{
    menu();

    grammar_Controller ref_;




    string str;
    while (getline(cin, str))
    {

        if (str[0] == 'q' || str[0] == 'Q')
            break;

        if (parse(str.c_str(), ref_, space_p).full)
        {
            cout << "parsing succeeded\n";

        }
        else
        {
            cout << "parsing failed\n";
        }
    }

    cout << "Bye... :-) \n\n";
    return 0;
}


