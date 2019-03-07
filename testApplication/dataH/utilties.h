#ifndef UTILTIES_H
#define UTILTIES_H

#include "includes.h"
#include "dataH/grammar.h"
#include "dataH/allrecords.h"
#include "ast.h"
#include "dataH/grammartest.h"

bool doParse(std::string str, dataSQL::selectStmt& emp);      // parsing the query
bool doParse_(std::string str, dataTSQL::selectFromStmt& emp);
std::string getTableName();         // get the table name

QString stToQs(std::string st);     // string to Qstring
std::string QsToSt(QString qs);     // Qstring to String
void makeTheDeal(std::string file_path);             // to open the json file

#endif // UTILTIES_H
