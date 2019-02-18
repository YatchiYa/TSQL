

#include "../dataH/views.h"
#include "../dataH/grammar_controller.h"

#include <boost/spirit.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace boost::spirit;
using namespace std;


void menu(){

    cout << "**********************************************************\n\n";
    cout << "\t\t SQL parser.  Test n : 1  \n\n";
    cout << "**********************************************************\n\n";
    cout << "Type a SQL expression \n" ;
    cout << " (e.g.  select * from stocks ; ) \n" ;
    cout << " Type [q or Q] to quit\n\n" ;
}



bool isOK(string requette){

    return false ;
}
