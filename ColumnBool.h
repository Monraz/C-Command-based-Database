//
// Created by Christo on 3/14/2019.
//

#ifndef MONRAZD_COLUMNBOOL_H
#define MONRAZD_COLUMNBOOL_H

#include "Column.h"


class ColumnBool : public Column{

public:
    ColumnBool(std::string columnName, std::string tableName);

    ColumnBool(std::string columnName, std::string tableName, std::string description);
    ColumnBool(std::string columnFilePath);

    void addData(std::string data);


    std::string calSum() override;
};


#endif //MONRAZD_COLUMNBOOL_H
