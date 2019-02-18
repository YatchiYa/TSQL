#ifndef GRAMMAR_CONTROLLER_H_INCLUDED
#define GRAMMAR_CONTROLLER_H_INCLUDED



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
            strlit<>    AQL(":]");
            strlit<>    IAQL("[:");
            chlit<>     IAQ(']');
            chlit<>     AQ('[');
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

            identifier = nocase_d[lexeme_d[(alpha_p >> *(alnum_p | '_'))]];

            string_literal = lexeme_d[ch_p('\'') >>  +( anychar_p - ch_p('\'') )>> ch_p('\'')];

            //-----------------------------------------------------------------
            // RULES
            //-----------------------------------------------------------------

            //  Now - the actual BNF grammar for the parser


            query = longest_d[ (select_from_query | select_when_from_query | select_where_from_query | select_when_where_from_query) ] ;

            // hanle the select from query only
            select_from_query = select_stmt >> from_stmt ;
            select_stmt = SELECT >> project_list;
            project_list = longest_d[ (col_projection >> COMMA >> col_projection)
                            | col_projection ];     // longuest_d  pour declarer un OR

            col_projection = longest_d[col_reference | col_predicate] ;
            col_predicate = col_reference >> predicate >> value ;

            col_reference = longest_d[ col_name | (col_name >> AQ >> start_x >> AQL)
                 | (col_name >> IAQL >> end_x >> IAQ)
                 | (col_name >> AQ >> start_x >> DP >> end_x >> IAQ) ];

            end_x = uint_p;
            start_x = uint_p;

            col_name = longest_d[anychar_p | identifier]  ;
            value = longest_d[ uint_p | identifier ];

            predicate = longest_d[ (GT | LT | LE | GE | EQUAL | NE) ];

            from_stmt = FROM >> table_name ;
            table_name = longest_d[ identifier |  list_p(identifier, COMMA ) ] ;






            // handle the select from where query with when statement !

            select_when_from_query = select_stmt >> when_stmt >> from_stmt ;
            when_stmt = longest_d[ anychar_p | identifier ];
            when_stmt = WHEN >> pos_log_expr;

            pos_log_expr = longest_d[col_predicate | pos_and_log_expr | pos_or_log_expr] ;
            pos_and_log_expr = longest_d[ ( col_predicate >> AND_ >> col_predicate ) | ( LPAREN >> col_predicate >> AND_ >> col_predicate >> RPAREN ) ];
            pos_or_log_expr = longest_d[ (col_predicate >> OR_ >> col_predicate) | (LPAREN >> col_predicate >> OR_ >> col_predicate >> RPAREN ) ];

            seq_and_log_expr = col_predicate >> AND_ >> col_predicate ;
            seq_or_log_expr = col_predicate >> OR_ >> col_predicate ;
            seq_all_log_expr = longest_d[ ("all" >> col_predicate) | ("all" >> seq_log_expr) ];
            seq_any_log_expr = longest_d[ ("any" >> col_predicate) | ("any" >> seq_log_expr) ];

            // handle the select where from query

            select_where_from_query = select_stmt >> from_stmt >> where_stmt ;
            where_stmt = WHERE >> seq_log_expr ;
            seq_log_expr = longest_d[ col_predicate | seq_and_log_expr | seq_or_log_expr | seq_all_log_expr | seq_any_log_expr ] ;

            // handle the select when from where query
            select_when_where_from_query = select_stmt >> when_stmt >> from_stmt >> where_stmt;



        }


      rule<ScannerT> const&
        start() const { return query; }


//  Declare the keywords here
        symbols<> keywords;

        rule<ScannerT>
        program, query, col_projection, col_name, predicate, value, col_pr, end_x, start_x,
        select_from_query, select_when_from_query, select_where_from_query, select_when_where_from_query,
        select_stmt, when_stmt,
        from_stmt, table_name, project_list, col_reference, col_predicate, pos_log_expr, pos_or_log_expr, pos_and_log_expr, seq_and_log_expr, seq_log_expr,
        seq_all_log_expr, seq_any_log_expr, seq_or_log_expr,
        where_stmt, identifier, string_literal ;

    };
};

#endif // GRAMMAR_CONTROLLER_H_INCLUDED
