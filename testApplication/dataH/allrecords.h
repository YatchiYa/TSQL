#ifndef ALLRECORDS_H
#define ALLRECORDS_H

#include "includes.h"
#include "dataH/record.h"

class AllRecords
{

public:
    AllRecords();
    static void setAllRecord(QList<Record> ar);
    static QList<Record> getAllRecors();
    static void AddRecord(Record r);
    static void testShowData();    // for testing if the data is embaded

public:
    static QList<Record> allRecords;

};

#endif // ALLRECORDS_H
