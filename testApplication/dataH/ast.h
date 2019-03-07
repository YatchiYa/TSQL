#ifndef AST_H
#define AST_H

#include "includes.h"

class ast
{
public:
    ast();
    std::string getColName();
    void setColName(std::string c);

private:
    std::string colName;
};

#endif // AST_H
