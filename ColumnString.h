//
// Created by Christo on 3/14/2019.
//

#ifndef MONRAZD_COLUMNSTRING_H
#define MONRAZD_COLUMNSTRING_H
#include "Column.h"

class ColumnString : public Column{

public:
    ColumnString(std::string columnName, std::string tableName);

    ColumnString(std::string columnName, std::string tableName, std::string description);

    ColumnString(std::string columnFilePath);

    void addData(std::string data);

    std::string calSum() override;

};


#endif //MONRAZD_COLUMNSTRING_H
