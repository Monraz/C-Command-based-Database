//
// Created by Christo on 3/5/2019.
//

#ifndef MONRAZD_TABLE_H
#define MONRAZD_TABLE_H

#pragma once

#include "Column.h"
#include "ColumnInt.h"
#include "ColumnChar.h"
#include "ColumnString.h"
#include "ColumnDouble.h"
#include "ColumnBool.h"
#include "Column.cpp"
#include "ColumnInt.cpp"
#include "ColumnChar.cpp"
#include "ColumnString.cpp"
#include "ColumnDouble.cpp"
#include "ColumnBool.cpp"
#include "WrongPathException.cpp"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Database.h"
#include <memory>
#include <iomanip>
class Table {
    std::string tableName;
    std::string tableFilePath;
    std::fstream tableFile;
    std::vector<std::string> tableInfoVector;
    const char separator =' ';
    const int cellWidht = 16;

public:
    std::vector<std::string>tableColumnVector;
    Table(std::string tableName, std::string databaseName);
    Table(std::string path, std::string databaseName, bool boolean) noexcept(false);
    Table(std::string tableFilePath);

    const std::string &getTableFilePath() const;

    std::string getTableName(bool withoutSignature);
    void refreshTableInfo();
    std::vector<std::string> getColumns();
    void addRow (std::vector<std::string> stringVector);
    void printColumn(bool enumerated);
    std::vector<std::string> getRowFromUser();
    void deleteColumn(std::shared_ptr<Column> column);
    void deleteAllColumns();
    void exportFile(std::string name, std::string query);
    void query();
    void showTable();
};


#endif //MONRAZD_TABLE_H
