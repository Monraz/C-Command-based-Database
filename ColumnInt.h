//
// Created by Christo on 3/14/2019.
//

#ifndef MONRAZD_COLUMNINT_H
#define MONRAZD_COLUMNINT_H
#include "Column.h"

class ColumnInt : public  Column{
public:
    ColumnInt( std::string columnName, std::string tableName);
    ColumnInt( std::string columnName, std::string tableName, std::string description);
    ColumnInt(std::string columnFilePath);
    void addData(std::string data);

    std::string calSum() override;

};


#endif //MONRAZD_COLUMNINT_H
