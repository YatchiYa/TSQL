
// this class is used to check if the sql statement is in good form, to parse


/*
    this is the first try of a simple toy parser of the sql statement
    in this first class, we will try to handle the sql statement
    the different statement of sql select will be like :
        -> SELECT * FROM TABLE
        -> SELECT *[ different date ] FROM TABLE
        -> SELECT *[ different date ] < ratio FROM TABLE
        -> SELECT * FROM TABLE WHERE .....


    to say simple, we will try to handle all the different SQL request that we can have with the different statement
    like SELECT-STMT,  WHENE-STMT, WHERE-STMT, CONDITION-STMT, DISTINCT-STMT

    |_> After parsing the sql statement, we need to execute this statement,
        + we need to specify the string buffer  that stocks all the differents variable


*/



#ifndef GRAMMAR_CONTROLLER_H_INCLUDED
#define GRAMMAR_CONTROLLER_H_INCLUDED

// include all the librairies you need
#include <boost/spirit.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

// define our modules in order to not repeat each time
using namespace boost::spirit;

using namespace std;

typedef struct grammar_Controller :
    public grammar<grammar_Controller>
{
    template <typename ScannerT>
    struct definition
    {
        definition(grammar_Controller const& self)
        {

            //-----------------------------------------------------------------
            // KEYWORDS
            //-----------------------------------------------------------------
            keywords =
                "select", "distinct", "from" , "where" , "when", "in" ,
                "and" , "or" , "as" ,
                "is" , "not" , "null" ;

            //-----------------------------------------------------------------
            // OPERATORS
            //-----------------------------------------------------------------

            chlit<>     STAR('*');
            chlit<>     COMMA(',');
            chlit<>     LPAREN('(');
            chlit<>     RPAREN(')');
            chlit<>     SEMI(';');
            chlit<>     LT('<');
            chlit<>     GT('>');
            strlit<>    LE("<=");
            strlit<>    GE(">=");
            chlit<>     EQUAL('=');
            strlit<>    NE("!=");
            chlit<>     AQ(']');
            chlit<>     IAQ('[');
            chlit<>     DP(':');


            //---------------------------------------
            // TOKENS
            //---------------------------------------
            typedef inhibit_case<strlit<> > token_t;

            token_t SELECT      = nocase_d["select"];
            token_t DISTINCT    = nocase_d["distinct"];
            token_t FROM        = nocase_d["from"];
            token_t WHERE       = nocase_d["where"];
            token_t WHEN        = nocase_d["when"];
            token_t IN_         = nocase_d["in"];
            token_t AND_        = nocase_d["and"];
            token_t OR_         = nocase_d["or"];
            token_t AS          = nocase_d["as"];
            token_t IS_         = nocase_d["is"];
            token_t NOT_        = nocase_d["not"];
            token_t NULL_       = nocase_d["null"];


          //-----------------------------------------
          //	Start grammar definition
          //-----------------------------------------



            //-----------------------------------------------------------------
            // RULES
            //-----------------------------------------------------------------

            //  Now - the actual BNF grammar for the parser


            select_stmt_2 = +(select_from_query) ;

            // hanle the select from query only
            select_from_query = select_stmt >> from_stmt ;
            select_stmt = SELECT >> project_list ;      // select project list.

            from_stmt = FROM >> from_stmt_2 ;     // from stmt
            from_stmt_2 = table_name ;  // table name

            project_list = longest_d[ col_projection >> COMMA >> col_projection
                            | col_projection ];     // longuest_d  pour declarer un OR


            col_projection = longest_d[col_reference | col_predicate] ;
            col_predicate = col_reference  ;


            col_reference = col_name;
            /*col_reference = longest_d[ col_name | col_name >> AQ >> start >> IAQ
                 | col_name >> AQ >> endx >> IAQ
                 | col_name >> AQ >> start >> DP >> endx >> IAQ ];*/

            predicate = longest_d[GT | LT | LE | GE | EQUAL | NE];
            //start = start_t ;
            //endx = endxx;



            // handle the select from where query
            // select_when_from_query = select_stmt >> from_stmt >> where_stmt ;



            // handle the select when from query
            // ->select_where_from_query = select_stmt >> when_stmt >> from_stmt ;

            // handle the select when from where query
            // -> select_where_from_query = select_stmt >> when_stmt >> from_stmt >> where_stmt;



        }



      rule<ScannerT> const&
        start() const { return select_stmt_2; }


//  Declare the keywords here
        symbols<> keywords;

        rule<ScannerT>
        select_stmt_2, select_from_query, select_when_from_query, select_where_from_query, select_when_where_from_query,
        select_stmt, from_stmt,
        project_list, from_stmt_2, col_projection, col_reference, col_predicate, predicate,

        where_stmt, identifier, string_literal ;

        string table_name, col_name ;
        int start_t;
        int endxx ;
        int value;

    };
};




#endif // GRAMMAR_CONTROLLER_H_INCLUDED
