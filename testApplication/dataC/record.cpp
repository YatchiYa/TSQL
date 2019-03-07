#include "dataH/record.h"
#include "includes.h"

Record::Record()
{

}

void Record::setSqid(int sid){
    sqid = sid;
}
void Record::setTableName(QString t_name){
    table_name = t_name;
}
void Record::setIndustry(QString ind){
    industry = ind;
}
void Record::setClosing(QStringList clo){
    closing = clo;
}
void Record::setOpening(QStringList op){
    opening = op;
}
void Record::setheaderQuater(QString hq){
    headquater = hq;
}
void Record::setPosition(QStringList p){
    position = p;
}
