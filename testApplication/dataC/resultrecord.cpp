#include "dataH/resultrecord.h"

// define the static variable


ResultRecord::ResultRecord()
{

}

AllResultRecord::AllResultRecord()
{

}

//get All the records :
QList<ResultRecord> AllResultRecord::getAllResultRecors(){
    return AllResultRecord::allResultRecords;
}





void ResultRecord::setTableName(QString tab_name){
    table_name = tab_name;
}
void ResultRecord::setAll_seqs(bool as){
    all_seqs = as;
}
void ResultRecord::setAll_pos(bool ap){
    all_pos = ap;
}
void ResultRecord::setVSI(QVector<int> vsi){
    valid_seq_ids = vsi;
}void ResultRecord::setVSL(QVector<int> vsl){
    valid_pos_locations = vsl;
}
void ResultRecord::setColumns(QStringList col){
    columns = col;
}

QString ResultRecord::getTableName(){
    return table_name;
}
