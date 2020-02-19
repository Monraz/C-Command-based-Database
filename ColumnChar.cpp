//
// Created by Christo on 3/14/2019.
//

#include "ColumnChar.h"
/**
 * \brief Constructor used to create a ColumnChar from an existant table.
 * @param columnName name of the Column.
 * @param tableName name of the Table that owns the column.
 */
ColumnChar::ColumnChar(std::string columnName, std::string tableName) : Column(columnName, tableName) {
    dataType = CHAR;
    columnFile.open(columnFilePath, std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<enumStringMap.at(dataType)+"_type"<<std::endl;
    }
    columnFile.close();
}

/**
 * \brief Constructor used to create a new ColumnChar.
 * @param columnName is the name of the Column.
 * @param tableName is the name of the table that owns the column.
 * @param description the description of the new Column.
 */
ColumnChar::ColumnChar(std::string columnName, std::string tableName, std::string description) : Column(columnName, tableName, description) {
    dataType = CHAR;
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
ColumnChar::ColumnChar(std::string columnFilePath) : Column(columnFilePath) {
    this->columnFilePath=columnFilePath;
}

/**
 * \brief method used to insert a new entry into the file
 * @param data is the element to be inserted into the file.
 */
void ColumnChar::addData(std::string data) {
    if(data.length()>1){
        throw std::invalid_argument("Char can only be one char long, multiple characters received");
    }

    columnFile.open(columnFilePath, std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<data.at(0)<<std::endl;
    }
    columnFile.close();

}

std::string ColumnChar::calSum() {
    return std::string();
}
