
#include "dataH/recordmanager.h"
#include "includes.h"
#include "dataH/resultrecord.h"
#include "dataH/allrecords.h"
#include "dataH/record.h"



// open table function   eg : res = open_table(“Stocks”) ->  {table_name: “Stocks”, all_seqs: 1, all_pos: 1}

AllResultRecord open_table(QString table_name){

    AllResultRecord allResultRecords;

    // trying to get all the data that eq to table_name
    QList<Record> data = AllRecords::getAllRecors();    // get all the data
    int taille = data.length();     // get the length of our allRecords


   // pour afficher sur le debbeger
   qDebug() << " Open_Table Function \n ";


    for(auto i=0; i< taille; i++){
        Record r = data.at(i);
        QString table = r.table_name;
        if (table == table_name){
               ResultRecord ar;
               ar.setTableName(r.table_name);
               ar.setAll_seqs(1);
               ar.setAll_pos(true);

               // adding to AllResultRecord
               allResultRecords.allResultRecords.push_back(ar);

               // showing in the debug the folowing result
               qDebug() << "<table_name> : " << table << ", <all_seq> : " << ar.all_seqs << ", <all_seq> " << ar.all_pos;
        }
    }

    return allResultRecords;

}

// *********************** a refaire de maniere generale getColum( opening or closing from json file ) *******************************


AllResultRecord fetch_seq(QString column_name, AllResultRecord allResultRecords){

    AllResultRecord NewallResultRecords;

    qDebug() << " fetch_seq Function \n ";

    QList<Record> data = AllRecords::getAllRecors();    // get all the data from memory
    int taille = data.length();     // get the length of our allRecords


    for(auto i=0; i<taille; i++)
    {
        // get the record data of each one in the memory
        Record r = data.at(i);
        QString table = r.table_name;  // the table name = stocks
        // get the Result Record data of each one int the memory
        auto ar = allResultRecords.allResultRecords.at(i);

            // for opening sections
        if(column_name == "opening"){
            ar.setColumns(r.opening);
            NewallResultRecords.allResultRecords.push_back(ar);

            qDebug() << "<table_name> : " << ar.getTableName() << ", <all_seq> : " << ar.all_seqs << ", <all_pos> : " << ar.all_pos <<
                        " ,<Column> : (" << column_name << ") : " << ar.columns << " ]" ;

        }
            // for closing section
        else if(column_name == "closing"){
            ar.setColumns(r.closing);
            NewallResultRecords.allResultRecords.push_back(ar);

            qDebug() << "<table_name> : " << ar.getTableName() << ", <all_seq> : " << ar.all_seqs << ", <all_pos> : " << ar.all_pos <<
                        " ,<Column> : (" << column_name << ") : " << ar.columns << " ]" ;

        }
    }

    return NewallResultRecords;



}
