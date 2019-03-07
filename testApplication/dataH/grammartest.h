#ifndef GRAMMARTEST_H
#define GRAMMARTEST_H

#include "includes.h"

namespace dataTSQL{

    // we defin our alias, by doing this using, so we don't include it each time
    using namespace boost::spirit;
    // we define the output statement of our data
    // this struct for : select -> from only

    struct selectFromStmt{
        std::string col_name;
        std::string table_name;
        std::string evalc();
        std::string evalt();
    };

}

// this to adapt boost spirit to our structur
BOOST_FUSION_ADAPT_STRUCT(
    dataTSQL::selectFromStmt,
    (std::string, col_name;)
    (std::string, table_name)
)

namespace dataTSQL{
    // /////////////////////////////////////////////////////////////////////////////
        //  Our dataSQL parser
    // /////////////////////////////////////////////////////////////////////////////

    // define the template structure and rules

    template <typename Iterator>
    struct selectStmt_parser : qi::grammar<Iterator, selectFromStmt(), ascii::space_type>  // define the name of the parser, the structure and the skipper
        {



        // in this section we declare all our variable, rules
        qi::symbols<> keywords;

        // the opperators
        qi::rule<Iterator, std::string(), ascii::space_type> STAR, COMMA, LPAREN, RPAREN, SEMI,
        LT, GT, EQUAL, LE, GE, NE, AQL, IAQL, IAQ, AQ, DP;


        // the rules
        qi::rule<Iterator, selectFromStmt(), ascii::space_type> select_from_query, select_when_from_query, select_from_where_stmt, select_when_from_where_query;
        qi::rule<Iterator, selectFromStmt(), ascii::space_type> query;


        // to define
        qi::rule<Iterator, std::string(), ascii::space_type> from_stmt, when_stmt, where_stmt, pos_log_expr, pos_and_log_expr, pos_or_log_expr, seq_log_expr;
        qi::rule<Iterator, std::string(), ascii::space_type> project_list;

        qi::rule<Iterator , std::string(), ascii::space_type> identifier, table_name, col_name;
        qi::rule<Iterator , std::string(), ascii::space_type> col_projection, col_predicate, col_reference, predicate, value, start_x, end_x, seq_and_log_expr, seq_or_log_expr, seq_all_log_expr, seq_any_log_expr;


        // define the base type of our grammar

            selectStmt_parser() : selectStmt_parser::base_type(query)
            {
                    // define our tools
                using qi::int_;
                using qi::lit;
                using qi::double_;
                using qi::lexeme;
                using ascii::char_;
                using ascii::string;
                using qi::symbols;
                using ascii::no_case;
                using ascii::alpha;
                using ascii::alnum;
                using boost::variant;


                //-----------------------------------------------------------------
                // OPERATORS
                //-----------------------------------------------------------------
                STAR    =     string("*");
                COMMA   =     string(",");
                LPAREN  =     string("(");
                RPAREN  =     string(")");
                SEMI    =     string(";");
                LT      =     string("<");
                GT      =     string(">");
                LE      =     string("<=");
                GE      =     string(">=");
                EQUAL   =     string("=");
                NE      =     string("!=");
                AQL     =     string(":]");
                IAQL    =     string("[:");
                IAQ     =     string("[");
                AQ      =     string("]");
                DP      =     string(":");



            // ///////////////////////////////////////////////////////////////////////////////////////////
                // /////////// RULES ////////////////

            // ///////////////////////////////////////////////////////////////////////////////////////////

            // the different type of select stmt
           query %= (select_from_query) | (select_when_from_query) | (select_from_where_stmt) | (select_when_from_where_query) ;

           select_from_query %= "select" >> project_list >> "from" >> from_stmt ;
           select_when_from_query %= "select" >> project_list >> "when" >> when_stmt >> "from" >> from_stmt ;
           select_from_where_stmt %= "select" >> project_list >> "where" >> where_stmt >> "from" >> from_stmt  ;
           select_when_from_where_query %= "select" >> project_list >> "when" >> when_stmt >> "where" >> where_stmt >> "from" >> from_stmt ;





           // ////////////////////    select from stmt  //////////////////////////////////

              // the grammar of the select stmt

            project_list %= ( col_projection >> "," >> col_projection ) | ( col_projection ); // the project list ( colone , colone OU colone
            col_projection %= ( col_predicate ) | ( col_reference );                           // to choice for our colones
            col_predicate %= col_reference >> predicate >> value;                                  // define col predicate
            predicate %= (GT | LT | EQUAL | LE | GE | NE);                                      // define the paramaters predicate sup, inf equal...
            value %= identifier | uint_ ;                                                       // define the value of the reference

            col_reference %= ( col_name >> "[" >> start_x >> ":" >> end_x >> "]" )          // opening[15:36]
                            | ( col_name >> "[" >> start_x >> ":]" )                        // opening [14:]
                            | (col_name >> "[:" >> end_x >> "]" )                           //  opening[:14]
                            | (col_name) ;                                                  // cole name simple

            col_name %= identifier;
            start_x = uint_;
            end_x = uint_;

           identifier %= no_case[lexeme[(alpha >> *(alnum | '_'))]]; // the table and the colonne for now,
           from_stmt %= table_name;
           table_name %= identifier;




           // ////////////////////    select WHEN from stmt  //////////////////////////////////

              // the grammar of the select stmt
            when_stmt %= pos_log_expr;                                                                          // define the when stmt
            pos_log_expr %= ( col_predicate )                                                                   // pos_log is predicate
                            | ( pos_and_log_expr )
                            | (pos_or_log_expr);

            pos_and_log_expr %= ( (col_predicate >> "and" >> col_predicate)                                             // A and B
                                  | ( "(" >> col_predicate >> "and" >> col_predicate >> ")")
                                  );
            pos_or_log_expr %= ( (col_predicate >> "or" >> col_predicate)                                               // A or B
                                 | ("(" >> col_predicate >> "or" >> col_predicate >> ")" )
                                 );


            // ////////////////////    select from where stmt  //////////////////////////////////

            where_stmt %= seq_log_expr;
            seq_log_expr %= ( seq_and_log_expr )                      // where x and y
                            | ( seq_or_log_expr )                       // where x or y
                            | ( seq_all_log_expr )                      // where all x
                            | ( seq_any_log_expr)
                            | (col_predicate);                      // where all y

            seq_and_log_expr %= ( col_predicate >> "and" >> col_predicate );
            seq_or_log_expr %= ( col_predicate >> "or" >> col_predicate );
            seq_all_log_expr %= "all" >> col_predicate;
            seq_any_log_expr %= "any" >> col_predicate;

            // ///////////////////////////// select when from where stmt //////////////////////////





       }


     };
}



#endif // GRAMMARTEST_H
