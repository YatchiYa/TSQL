#include <iostream>

// adding our file
#include "dataH/test1.h"
#include "dataH/test2.h"
#include "dataH/grammar_parser_sql.h"
#include "dataH/sql_request_parser.h"

using namespace std;



int main( int argc, char* argv[] )
{

   int choice;

     do
    {;
        menu();
        cout << " -> " ;
        cin >> choice;

        if (choice == 0)
            cout << " see ya !!" << endl << endl << endl << endl;
            break;


        if (choice == 1){
            cout << " *********** First Version of Learning Lessons !!!  ************ " << endl << endl << endl;

            // simple parsing


            test1(); // test with Qi
            test1_1(); // second test with Qi
            test1_2(); //  test with karma
            test1_3();  // trying to show pair data
            test1_4();

            // simple aritimitique functions

            cout << " --> second tests !! " << endl;
            cout << "testing if the file does exist or not !!!" << endl;
            test2();





            cout << endl << endl << endl << "  ****************** End of Learning Lessons !!!  **************** " << endl << endl << endl;
        }


        if ( choice == 2) {
            cout << endl << endl << endl  << " ************* the first version of the project  **************************" << endl << endl << endl ;

            cout << "/////////////////////////////////////////////////////////\n\n";
            cout << "\t\t A grammar SQL parser !! ( first try )...\n\n";
            cout << "/////////////////////////////////////////////////////////\n\n";
            cout << "Type a SQL expression \n" ;
            cout << " (e.g.  select * from mytable ; ) \n" ;
            cout << " Type [ q or Q ] to quit\n\n" ;


            // grammar_parser_sql g;
            toysql_grammar g;
            string str;
            while (getline(cin, str))
            {
                if (str[0] == 'q' || str[0] == 'Q')
                    break;

                if (parse(str.c_str(), g, bs::space_p).full)
                {
                    cout << "parsing succeeded\n";
                }
                else
                {
                    cout << "parsing failed\n";
                }
            }

            cout << "Bye... :-) \n\n";
            break;

        }


    }while (choice != 1 || choice != 2 || choice != 0);


    return 0;
}








