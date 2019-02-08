
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
// include all the librairies you need
#include <fstream>
#include <vector>
#include <string>
#include <boost/spirit.hpp>
#include <iostream>

// include the header file
#include "../dataH/grammar_parser_sql.h"

namespace bs = boost::spirit;

grammar_parser_sql::grammar_parser_sql(){



    // define the different operators :

    bs::chlit<>     STAR('*');
    bs::chlit<>     COMMA(',');
    bs::chlit<>     LPAREN('(');
    bs::chlit<>     RPAREN(')');
    bs::chlit<>     SEMI(';');
    bs::chlit<>     LT('<');
    bs::chlit<>     GT('>');
    bs::strlit<>    LE("<=");
    bs::strlit<>    GE(">=");
    bs::chlit<>     EQUAL('=');
    bs::strlit<>    NE("!=");

    // the different keyword possible

    keywords =  "select", "distinct", "from" , "where" , "when" , "in" ,
                "and" , "or" , "as" ,
                "is" , "not" , "null" ;



     // the different tokens possible

    typedef bs::inhibit_case<bs::strlit<> > token_t;
            token_t SELECT      = bs::nocase_d["select"];
            token_t DISTINCT    = bs::nocase_d["distinct"];
            token_t FROM        = bs::nocase_d["from"];
            token_t WHERE       = bs::nocase_d["where"];
            token_t WHEN        = bs::nocase_d["when"];
            token_t IN_         = bs::nocase_d["in"];
            token_t AND_        = bs::nocase_d["and"];
            token_t OR_         = bs::nocase_d["or"];
            token_t AS          = bs::nocase_d["as"];
            token_t IS_         = bs::nocase_d["is"];
            token_t NOT_        = bs::nocase_d["not"];
            token_t NULL_       = bs::nocase_d["null"];




      // *********** start grammar definition ******************


       //identifier = bs::nocase_d[bs::lexeme_d [ bs::alpha_p >> *(bs::alnum_p | '_')) ]];
      // string_literal = bs::lexeme_d[bs::ch_p('\'') >>  +( bs::anychar_p - bs::ch_p('\'') ) >> bs::ch_p('\'') ];


      // npw we start our grammar defenition !

      // itried only the short query here !
      // e.g : select * from X ;


    program = +(query);

    query = bs::longest_d[ short_query | long_query ] ;

    short_query = select_stmt >> from_stmt ;

    select_stmt = SELECT >> !(DISTINCT) >> ( STAR | var_stmt ) ;
    var_stmt = bs::longest_d[ varname |  bs::list_p( varname, COMMA ) ] ;
    varname = identifier >> !(as_stmt) ;
    as_stmt = AS >> alias ;
    alias = identifier ;
    from_stmt = FROM >> table_stmt ;
    table_stmt = bs::longest_d[ identifier |  bs::list_p(identifier, COMMA ) ] ;





}


bool grammar_parser_sql::verifySqlStmt(std::string stmt){
    bool isOk = true;


    // define the different rules of our statement :

    return isOk;
}

bs::rule<> const& grammar_parser_sql::start(){
    return program;
}
