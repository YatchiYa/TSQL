#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include "includes.h"
#include "resultrecord.h"

// here we define the differents function of the project



AllResultRecord open_table(QString table_name);
AllResultRecord fetch_seq(QString column_name, AllResultRecord allResultRecords);











#endif // RECORDMANAGER_H
