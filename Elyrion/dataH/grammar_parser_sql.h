#ifndef GRAMMAR_PARSER_SQL_H_INCLUDED
#define GRAMMAR_PARSER_SQL_H_INCLUDED


#include <boost/spirit.hpp>
#include <iostream>


namespace bs = boost::spirit;



class grammar_parser_sql{

public:
    grammar_parser_sql(); // constructor
    bs::rule<> const& start();  // run the function

    bool verifySqlStmt(std::string stmt);



private:
    std::string stmt;
    // the different keyword !
    bs::symbols<> keywords ;
    bs::rule<>    identifier, select_stmt, project_list, from_stmt, var_stmt, short_query, query, long_query, program, as_stmt, varname, alias, table_stmt ;

};



#endif // GRAMMAR_PARSER_SQL_H_INCLUDED
