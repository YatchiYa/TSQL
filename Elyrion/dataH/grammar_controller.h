
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

            identifier = nocase_d[lexeme_d[(alpha_p >> *(alnum_p | '_'))]];

            string_literal = lexeme_d[ch_p('\'') >>  +( anychar_p - ch_p('\'') )>> ch_p('\'')];


            //-----------------------------------------------------------------
            // RULES
            //-----------------------------------------------------------------

            //  Now - the actual BNF grammar for the parser

            program = +(query) ;
            query = longest_d[ select_from_query | select_when_from_query | select_where_from_query | select_when_where_from_query ] ;

            // hanle the select from query only
            select_from_query = select_stmt >> from_stmt ;
            select_stmt = SELECT >> !(DISTINCT) >> ( STAR | var_stmt );
            var_stmt = longest_d[ varname |  list_p( varname, COMMA ) ] ;
            varname = identifier >> !(as_stmt) ;
            as_stmt = AS >> alias ;
            alias = identifier ;
            from_stmt = FROM >> table_stmt >> ( SEMI | where_stmt );
            table_stmt = longest_d[ identifier |  list_p(identifier, COMMA ) ] ;


            // handle the select from where query
            select_when_from_query = select_stmt >> from_stmt >> where_stmt ;



            // handle the select when from query
            // ->select_where_from_query = select_stmt >> when_stmt >> from_stmt ;

            // handle the select when from where query
            // -> select_where_from_query = select_stmt >> when_stmt >> from_stmt >> where_stmt;



        }


      rule<ScannerT> const&
        start() const { return program; }


//  Declare the keywords here
        symbols<> keywords;

        rule<ScannerT>
        program, query,
        select_from_query, select_when_from_query, select_where_from_query, select_when_where_from_query,
        select_stmt, star, var_stmt, varname,
        as_stmt, alias, from_stmt, table_stmt,

        where_stmt, identifier, string_literal ;

    };
};


#endif // GRAMMAR_CONTROLLER_H_INCLUDED
