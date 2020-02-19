//
// Created by Christo on 3/14/2019.
//

#include "ColumnDouble.h"

/**
 * \brief Constructor used to create a ColumnDouble from an existant table.
 * @param columnName name of the Column.
 * @param tableName name of the Table that owns the column.
 */
ColumnDouble::ColumnDouble(std::string columnName, std::string tableName) : Column(columnName, tableName) {
    dataType = DOUBLE;
    columnFile.open(columnFilePath, std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<enumStringMap.at(dataType)+"_type"<<std::endl;
    }
    columnFile.close();
}

/**
 * \brief Constructor used to create a new ColumnDouble.
 * @param columnName is the name of the Column.
 * @param tableName is the name of the table that owns the column.
 * @param description the description of the new Column.
 */
ColumnDouble::ColumnDouble(std::string columnName, std::string tableName, std::string description) : Column(columnName, tableName, description) {
    dataType = DOUBLE;
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
ColumnDouble::ColumnDouble(std::string columnFilePath) : Column(columnFilePath) {
    this->columnFilePath=columnFilePath;
}

/**
 * \brief method used to insert a new entry into the file
 * @param data is the element to be inserted into the file.
 */
void ColumnDouble::addData(std::string data) {

    columnFile.open(columnFilePath, std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<std::stod(data)<<std::endl;
    }
    columnFile.close();

}
/**
 * \brief used to calculate the sum of all the doubles stored in the file
 * @return the sum of all the doubles in the column
 */
std::string ColumnDouble::calSum() {
    columnFile.open(columnFilePath, std::ios::in);
    int counter = 0;
    double toRet=0;
    std::string data;
    if(columnFile){
        while(columnFile>>data){
            counter++;
            if(counter>=3){
                toRet+=std::stod(data);
            }
        }
    }
    columnFile.close();
    return std::to_string(toRet);
}
