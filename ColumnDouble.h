//
// Created by Christo on 3/14/2019.
//

#ifndef MONRAZD_COLUMNDOUBLE_H
#define MONRAZD_COLUMNDOUBLE_H
#include "Column.h"

class ColumnDouble : public Column{
public:
    ColumnDouble(std::string columnName, std::string tableName);

    ColumnDouble(std::string columnName, std::string tableName, std::string description);

    ColumnDouble(std::string columnFilePath);

    void addData(std::string data);

    std::string calSum() override;

};


#endif //MONRAZD_COLUMNDOUBLE_H
