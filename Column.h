//
// Created by Christo on 3/5/2019.
//

#ifndef MONRAZD_COLUMN_H
#define MONRAZD_COLUMN_H
#pragma once
#include "DataType.h"
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "globalFunction.h"
class Column {
protected:
    std::string description;
    std:: string columnFilePath;
    std::fstream columnFile;
    std::string columnName;
    DataType dataType;
public:

    const std::fstream &getColumnFile() const;

    std::vector<std::string> columnInfoVector;

    Column(std::string columnName,std::string tableName );
    Column(std::string columnName,std::string tableName, std::string description);

    Column(std::string columnFilePath);

    DataType getType();

    virtual void addData(std::string);

    void refreshColumnInfo();

    std::string getDataAt(int i);

    std::string getColumnName(bool withoutSignature);

    virtual std::string calSum();

    std::string getColumnFilePath();

};


#endif //MONRAZD_COLUMN_H
