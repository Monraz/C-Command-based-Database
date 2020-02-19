
///Created by Christo on 3/5/2019.
/// Last time modified on 5/10/2019.

#include "Column.h"
/**
 * \brief a Constructor used by the derived class to open an existant column stored
 * in files.
 * @param columnFilePath
 */
Column::Column(std::string columnFilePath){
    this->columnFilePath = columnFilePath;
    this->columnName = getColumnName(true);
}

/**
 * \brief a Constructor used to open a stored Column
 *
 * @param columnName is a string that contains the name of the new Column
 * @param tableName is the name of the table that owns this Column
 */
Column::Column(std::string columnName, std::string tableName){
    //std::cout<<"\n1STIP!";
    std::cout<<"\nEnter a description for this column: ";
    std::getline(std::cin, description);
    this->columnName=columnName;
    this->columnFilePath= columnName+"_column";
    //std::cout<<"\n2STIP!";
    columnFile.open(columnFilePath);
    /*If the column File didnt open (because it doesnt exist yet), create
     * a file in the columnFilePath and write as the first line the path
     * of the column*/
    //std::cout<<"\n3STIP!";
    if(!columnFile){
        //std::cout<<"\n31STIP!";
        columnFile.open(columnFilePath, std::ios::out | std::ios::app);
        //std::cout<<"\n32STIP!";
        columnFile<<columnFilePath<<std::endl;
        //std::cout<<"\n33STIP!";
        columnFile<<description+"_description"<<std::endl;
        //std::cout<<"\n34STIP!";

    }
    //std::cout<<"\n4STIP!";
    columnFile.close();
    //std::cout<<"\n5STIP!";
    //Now, open the file of the table and add a new line with the path of the
    //column file.
    //std::cout<<"\n6STIP!";
    columnFile.open(tableName+"_table",std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<columnFilePath<<std::endl;
    }
    //std::cout<<"\n7STIP!";
    columnFile.close();
}

/**
 * \brief a Constructor used to create a new Column object.
 *
 * \note this Constructor is only called from its derived classes.
 * @param columnName is the name of the column.
 * @param tableName is the name of the table that owns the column.
 * @param description is the description this column will have.
 */
Column::Column(std::string columnName, std::string tableName,
        std::string description){
    this->columnName=columnName;
    this->columnFilePath= columnName+"_column";
    //std::cout<<"\n2STIP!";
    columnFile.open(columnFilePath);
    /*If the column File didnt open (because it doesnt exist yet), create
     * a file in the columnFilePath and write as the first line the path
     * of the column*/
    //std::cout<<"\n3STIP!";
    if(!columnFile){
        //std::cout<<"\n31STIP!";
        columnFile.open(columnFilePath, std::ios::out | std::ios::app);
        //std::cout<<"\n32STIP!";
        columnFile<<columnFilePath<<std::endl;
        //std::cout<<"\n33STIP!";
        columnFile<<description;
        columnFile<<"\n";
        //std::cout<<"\n34STIP!";

    }
    //std::cout<<"\n4STIP!";
    columnFile.close();
    //std::cout<<"\n5STIP!";
    //Now, open the file of the table and add a new line with the path of the
    //column file.
    //std::cout<<"\n6STIP!";
    columnFile.open(tableName+"_table",std::ios::out | std::ios::app);
    if(columnFile){
        columnFile<<columnFilePath<<std::endl;
    }
    //std::cout<<"\n7STIP!";
    columnFile.close();
}

/**
 * \brief used to return the Datatype of the column to know how to manage the data stored inside
 * @return the Datatype value stored in the Column file
 */
DataType Column::getType(){
    std::string type;
    for(std::string info : columnInfoVector){
        //std::cout<<info<<"\n";
        if(endsWith(info,"_type")){
            type= info.substr(0,(info.size()-5));
        }
    }

    return enumDatatypeMap.at(type);
}

/**
 * \brief used to refresh the vectors containing the information stored in the Column file
 * it is used when a Column is opened or a change has occured.
 */
void Column::refreshColumnInfo() {
    std::string tableInfo;
    columnFile.open(columnFilePath,std::ios::in);
    if(columnFile){
        columnInfoVector.clear();
        while(std::getline(columnFile,tableInfo)){
            columnInfoVector.push_back(tableInfo);
        }
    }
    columnFile.close();
}

/**
 * \brief used to add data to the column
 * \note the reason why this method was needed is because
 * when the program opens a Column at first it doesn't know
 * what type of Column it is, so a base class column is created, and then the
 * DataType is requested and once the program knows the Datatype the overriden addData
 * method from the derived class is called.
 */
void Column::addData(std::string){}

/**
 * \brief used to get the file path relative to the project
 * @return
 */
std::string Column::getColumnFilePath() {
    return this->columnFilePath;
}

/**
 * \brief used to retreive an element from the file at an specific position.
 * @param i
 * @return
 */
std::string Column::getDataAt(int i){
    refreshColumnInfo();
    return columnInfoVector.at(i+startPointColumn);

}
/**
 *
 * @param withoutSignature is a boolean to specified if the returning string
 * must contain the Signature "_column" or not.
 * @return the name of the Column.
 */
std::string Column::getColumnName(bool withoutSignature) {
    refreshColumnInfo();
    if(withoutSignature){
        for(std::string info : columnInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_column")){
                return info.substr(0,(info.size()-7));
            }
        }
        std::cout<<"\nThe column has no name";
    }else{
        for(std::string info : columnInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_column")){
                return info;
            }
        }
        std::cout<<"\nThe column has no name";
    }
}



const std::fstream &Column::getColumnFile() const {
    return columnFile;
}

/**
 * \brief this class will be overriden by the derived class to return the
 * sum of all the elements stored in the column accordingly to its type.
 * @return
 */
std::string Column::calSum() {
    return "";
}
