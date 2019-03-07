#ifndef RECORD_H
#define RECORD_H

#include "includes.h"

// this file will be for our all data of the file !

// to check after if it's not benefic to to truct rather than classes !!!!

class Record
{

public:
    Record();
    void setTableName(QString t_name);
    QString getTableName();
    void setSqid(int sid);
    int getSqid();
    void setheaderQuater(QString hq);
    QString getheaderQuater();
    void setIndustry(QString ind);
    QString getIndustry();
    void setPosition(QStringList p);
    QStringList getPostion();
    void setOpening(QStringList op);
    QStringList getOpening();
    void setClosing(QStringList clo);
    QStringList getClosing();

public:
    QString table_name;
    int sqid;
    QString headquater;
    QString industry;
    QStringList position;
    QStringList opening;
    QStringList closing;

};




#endif // RECORD_H
