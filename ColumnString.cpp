//
// Created by Christo on 3/14/2019.
//

#include "ColumnString.h"

/**
 * \brief Constructor used to create a ColumnString from an existant table.
 * @param columnName name of the Column.
 * @param tableName name of the Table that owns the column.
 */
ColumnString::ColumnString(std::string columnName, std::string tableName) : Column(columnName, tableName) {
    dataType = STRING;
    columnFile.open(columnFilePath, std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<enumStringMap.at(dataType)+"_type"<<std::endl;
    }
    columnFile.close();
}

/**
 * \brief Constructor used to create a new ColumnString.
 * @param columnName is the name of the Column.
 * @param tableName is the name of the table that owns the column.
 * @param description the description of the new Column.
 */
ColumnString::ColumnString(std::string columnName, std::string tableName, std::string description) : Column(columnName, tableName, description) {
    dataType = STRING;
    columnFile.open(columnFilePath, std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<enumStringMap.at(dataType)+"_type"<<std::endl;
    }
    columnFile.close();
}

/**
 * \brief Constructor used to open an existant column stored in the files of the program.
 * @param columnFilePath is the path to the file.
 */
ColumnString::ColumnString(std::string columnFilePath) : Column(columnFilePath) {
    this->columnFilePath=columnFilePath;
}

/**
 * \brief method used to insert a new entry into the file
 * @param data is the element to be inserted into the file.
 */
void ColumnString::addData(std::string data) {
    columnFile.open(columnFilePath, std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<data<<std::endl;
    }
    columnFile.close();

}

std::string ColumnString::calSum() {
    return std::string();
}
