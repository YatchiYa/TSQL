#ifndef RESULTRECORD_H
#define RESULTRECORD_H

#include "includes.h"

// this file will be for the output data
// structur result_data

// class of result record
class ResultRecord
{

public:
    ResultRecord();
    void setTableName(QString tab_name);
    QString getTableName();
    int getSqid();
    void setAll_seqs(bool as);
    bool getAll_seqs();
    void setAll_pos(bool ap);
    bool getAll_pos();
    void setVSI(QVector<int> vsi);
    QVector<int> getVSI();
    void setVSL(QVector<int> vsl);
    QVector<int> getVSL();
    void setColumns(QStringList col);
    QStringList getColumns();

public:
    QString table_name;
    bool all_seqs;
    bool all_pos;
    QVector<int> valid_seq_ids;
    QVector<int> valid_pos_locations;
    QStringList columns;   // to check after

};


// class of all records
class AllResultRecord
{

public:
    AllResultRecord();
    void setAllResultRecord(QList<ResultRecord> arr);
    QList<ResultRecord> getAllResultRecors();

public:
    QList<ResultRecord> allResultRecords;

};

#endif // RESULTRECORD_H
