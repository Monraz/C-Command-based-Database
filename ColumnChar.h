//
// Created by Christo on 3/14/2019.
//

#ifndef MONRAZD_COLUMNCHAR_H
#define MONRAZD_COLUMNCHAR_H
#include "Column.h"

class ColumnChar : public Column{

public:
    ColumnChar(std::string columnName, std::string tableName);

    ColumnChar(std::string columnName, std::string tableName, std::string description);

    ColumnChar(std::string columnFilePath);

    void addData(std::string data);

    std::string calSum() override;

};


#endif //MONRAZD_COLUMNCHAR_H
