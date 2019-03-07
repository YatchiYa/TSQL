#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "includes.h"



//  a refaire de tel sorte que sa affiche les int !!!!!!!!!!!!!!!!!!!!!!!!!


namespace dataSQL{

    // we defin our alias, by doing this using, so we don't include it each time
    using namespace boost::spirit;
    // we define the output statement of our data
    // this struct for : select -> from only


        // col_reference_type 01


    struct ref_type_0{
        std::string col_name;
        std::string getCol(){
            return col_name;
        }
    };
    struct ref_type_1{
        ref_type_0 ref_type_0;
        int start_x;
        int getStart(){
            return start_x;
        }
    };

    struct ref_type_2{
        ref_type_0 ref_type_0;
        int end_x;
        int getEnd(){
            return end_x;
        }

    };
    struct ref_type_3{
        ref_type_0 ref_type_0;
        int start_x;
        int end_x;
        int getEnd(){
            return end_x;
        }
        int getStart(){
            return start_x;
        }
    };

    // colreference

    typedef boost::variant<ref_type_0, ref_type_1 , ref_type_2, ref_type_3> col_ref_variant;
    struct testC : boost::static_visitor<int>
    {

        int operator()(const ref_type_0& ref_type_0) const
        {
            return 0;
        }
        int operator()(const ref_type_1& ref_type_1) const
        {
            return 1;
        }
        int operator()(const ref_type_2& ref_type_2) const
        {
            return 2;
        }
        int operator()(const ref_type_3& ref_type_3) const
        {
            return 3;
        }
    };

    struct col_reference{
        col_ref_variant col_ref_variant;
    };

        // col predicate

    typedef boost::variant<std::string, int> value_variant;
    struct testD : boost::static_visitor<int>
    {

        int operator()(const std::string& stringx) const
        {
            return 0;
        }
        int operator()(const int& in) const
        {
            return 1;
        }
    };
    struct value{
        value_variant value_variant;
    };

    struct col_predicate{
        col_reference col_ref;
        std::string predicate;
        value value;
        std::string getPredicate(){
            return predicate;
        }
    };


    // definir une variante de choix

    typedef boost::variant<col_predicate , col_reference> predicate_ref;

    // ******************** test *************************
    // to define the path of our variant
    struct testP : boost::static_visitor<int>
    {
        int operator()(const col_predicate& col_pred) const
        {
            return 1;
        }
        int operator()(const col_reference& col_ref) const
        {
            return 2;
        }
    };


        // col_projection
    struct col_projection{
        predicate_ref pred_ref;
    };





        // project list
    struct project_list{
        col_projection col_project;
    };

        // select from stmt
    struct selectFromStmt{
        project_list columns;
        std::string table_name;
        std::string getTable(){
            return table_name;
        }
    };


        // the select stmt struct
    struct selectStmt{
        selectFromStmt query;
    };

}



// this to adapt boost spirit to our structur

BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::value,
    (dataSQL::value_variant, value_variant)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::ref_type_0,
    (std::string, col_name)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::ref_type_1,
    (dataSQL::ref_type_0, ref_type_0)
    (int, start_x)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::ref_type_2,
    (dataSQL::ref_type_0, ref_type_0)
    (int, end_x)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::ref_type_3,
    (dataSQL::ref_type_0, ref_type_0)
    (int, start_x)
    (int, end_x)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::col_reference,
    (dataSQL::col_ref_variant, col_ref_variant)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::col_predicate,
    (dataSQL::col_reference, col_ref)
    (std::string, predicate)
    (dataSQL::value, value)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::col_projection,
    (dataSQL::predicate_ref, pred_ref)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::project_list,
    (dataSQL::col_projection, col_project)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::selectFromStmt,
    (dataSQL::project_list, columns)
    (std::string, table_name)
)
BOOST_FUSION_ADAPT_STRUCT(
    dataSQL::selectStmt,
    (dataSQL::selectFromStmt, query)
)

namespace dataSQL{
    // /////////////////////////////////////////////////////////////////////////////
        //  Our dataSQL parser
    // /////////////////////////////////////////////////////////////////////////////

    // define the template structure and rules

    template <typename Iterator>
    struct selectStmt_parser : qi::grammar<Iterator, selectStmt(), ascii::space_type>  // define the name of the parser, the structure and the skipper
        {



        // in this section we declare all our variable, rules
        qi::symbols<> keywords;

        // the opperators
        qi::rule<Iterator, std::string(), ascii::space_type> STAR, COMMA, LPAREN, RPAREN, SEMI,
        LT, GT, EQUAL, LE, GE, NE, AQL, IAQL, IAQ, AQ, DP;

        // the rules to define
        qi::rule<Iterator, dataSQL::selectStmt(), ascii::space_type> query;
        qi::rule<Iterator, dataSQL::selectFromStmt(), ascii::space_type> select_from_query;


        //
        qi::rule<Iterator, std::string(), ascii::space_type> from_stmt;
        qi::rule<Iterator, dataSQL::project_list(), ascii::space_type> project_list;
        qi::rule<Iterator, dataSQL::col_predicate(), ascii::space_type> col_predicate;
        qi::rule<Iterator, dataSQL::col_reference(), ascii::space_type> col_reference;
        qi::rule<Iterator, dataSQL::ref_type_0(), ascii::space_type> ref_type_0;
        qi::rule<Iterator, dataSQL::ref_type_1(), ascii::space_type> ref_type_1;
        qi::rule<Iterator, dataSQL::ref_type_2(), ascii::space_type> ref_type_2;
        qi::rule<Iterator, dataSQL::ref_type_3(), ascii::space_type> ref_type_3;
        qi::rule<Iterator, dataSQL::value(), ascii::space_type> value;
        qi::rule<Iterator, dataSQL::col_projection(), ascii::space_type> col_projection;

        qi::rule<Iterator , std::string(), ascii::space_type> identifier, table_name, predicate, col_name;
        qi::rule<Iterator , int(), ascii::space_type> start_x, end_x;



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
                           // KEYWORDS
         //-----------------------------------------------------------------
           keywords =
               "select", "distinct", "from" , "where" , "when", "in" ,
               "and" , "or" , "as" ,
               "is" , "not" , "null" ;


           //-----------------------------------------------------------------
           // OPERATORS
           //-----------------------------------------------------------------
           STAR    =     char_('*');
           COMMA   =     char_(',');
           LPAREN  =     char_('(');
           RPAREN  =     char_(')');
           SEMI    =     char_(';');
           LT      =     char_('<');
           GT      =     char_('>');
           LE      =     char_("<=");
           GE      =     char_(">=");
           EQUAL   =     char_('=');
           NE      =     char_("!=");
           AQL     =     char_(":]");
           IAQL    =     char_("[:");
           IAQ     =     char_(']');
           AQ      =     char_('[');
           DP      =     char_(':');


           //---------------------------------------
           // TOKENS
           //---------------------------------------

           //-----------------------------------------------------------------
           // start the grammar parser
           //-----------------------------------------------------------------

            // the different type of select stmt
           query %= select_from_query ;

           // select from stmt
           select_from_query %= ("select" >> project_list >> "from" >> from_stmt)
                                |  ("SELECT" >> project_list >> "FROM" >> from_stmt);   // the grammar of the select stmt

           project_list %= ( col_projection >> "," >> col_projection ) | ( col_projection ) ; // the project list ( colonne , colonne OU colonne
           col_projection %= ( col_predicate | col_reference );
           col_predicate %= col_reference >> predicate >> value;
           predicate %= (GT | LT | EQUAL | LE | GE | NE);

           value %= ( identifier | uint_ ) ;

           col_reference %= ( ref_type_1 | ref_type_2 | ref_type_3 | ref_type_0 );
           ref_type_1 %= ( col_name >> "[" >> start_x >> ":]" );
           ref_type_2 %= ( col_name >> "[:" >> end_x >> "]" );
           ref_type_3 %= ( col_name >> "[" >> start_x >> ":" >> end_x >> "]" );
           ref_type_0 %= col_name;

           col_name %= identifier;
           start_x = uint_;
           end_x = uint_;




           identifier %= no_case[lexeme[(alpha >> *(alnum | '_'))]]; // the table and the colonne for now,
           from_stmt %= table_name;
           table_name %= identifier | (identifier >> "," >> table_name);


       }


     };
}





#endif // GRAMMAR_H
