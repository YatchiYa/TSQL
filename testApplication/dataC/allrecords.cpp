#include "dataH/allrecords.h"
#include "dataH/record.h"
#include "includes.h"

// we define our static variable
QList<Record> AllRecords::allRecords;

// constructor
AllRecords::AllRecords()
{

}

// to add data
void AllRecords::AddRecord(Record r){
    AllRecords::allRecords.push_back(r);
}

// to get data
QList<Record> AllRecords::getAllRecors(){
    return AllRecords::allRecords;
}



// to show data in the debugger
void AllRecords::testShowData(){

    for(int i=0; i< allRecords.length(); i++){
        qDebug() << "\n *****séquence : ******";
        qDebug() << AllRecords::allRecords.at(i).table_name;
        qDebug() << AllRecords::allRecords.at(i).sqid;
        qDebug() << AllRecords::allRecords.at(i).headquater;
        qDebug() << AllRecords::allRecords.at(i).industry;
        qDebug() << AllRecords::allRecords.at(i).position;
        qDebug() << AllRecords::allRecords.at(i).opening;
        qDebug() << AllRecords::allRecords.at(i).closing;
        qDebug() << " ****** fin !! ******** ";
    }
}
