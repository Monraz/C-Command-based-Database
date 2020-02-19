//
// Created by Christo on 3/5/2019.
//

#include "Database.h"
/**
 * \brief a Constructor used to create a new Database
 * @param name  is the name of the new Database
 * @param username is the name of the user who created the Database
 */
Database::Database(std::string name, std::string username) {
    databaseName=name;
    databaseFilePath = name+"_database";
    databaseFile.open(databaseFilePath);

    /*If the database File didnt open (because it doesnt exist yet), create
     * a file in the databaseFilePath and write as the first line the path
     * of the database*/
    if(!databaseFile){
        databaseFile.open(databaseFilePath, std::ios::out | std::ios::app);
        databaseFile<<databaseFilePath<<std::endl;
    }
    databaseFile.close();

    //Now, open the file of the user and add a new line with the path of the
    //database file.
    databaseFile.open(username+"_user",std::ios::out | std::ios::app);
    if(databaseFile){
        databaseFile<<databaseFilePath<<std::endl;
    }
    databaseFile.close();
}

/**
 * \brief method used to return the name of the database
 * @param withoutSignature is a boolean that specifies if the
 * returning value must contain the "_database" signature or not.
 * @return the name of the Database
 */
std::string Database::getDatabaseName(bool withoutSignature){
    refreshDatabaseInfo();
    if(withoutSignature){
        for(std::string info : databaseInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_database")){
                return info.substr(0,(info.size()-9));
            }
        }
        std::cout<<"\nThe database has no name";
    }else{
        for(std::string info : databaseInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_database")){
                return info;
            }
        }
        std::cout<<"\nThe database has no name";
    }
}

/**
 * \brief a Constructor used to open an existant Database.
 * @param databaseFilePath is the path to the file where the
 * information of the Database is stored.
 */
Database::Database(std::string databaseFilePath) {
    this->databaseFilePath = databaseFilePath;
    this->databaseName = getDatabaseName(true);
    this->databaseTableVector = getTables();
}

/**
 * \brief method used to return the path to the file of the Database.
 * @return the path to the file of the database.
 */
std::string &Database::getDatabaseFilePath() {
    return databaseFilePath;
}

/**
 * \brief default Constructor
 */
Database::Database() {}

/**
 * \brief method used to refresh the vectors where the information
 * of the Database is stored, it is used when a Database is opened or a
 * change has occured.
 */
void Database::refreshDatabaseInfo() {
    std::string databaseInfo;
    databaseFile.open(databaseFilePath,std::ios::in);
    if(databaseFile){
        databaseInfoVector.clear();
        while(databaseFile>>databaseInfo){
            databaseInfoVector.push_back(databaseInfo);
        }
    }
    databaseFile.close();
    databaseTableVector = getTables();
}
/**
 * \brief method used to delete all the tables of the database.
 */
void Database::deleteAllTables(){
    refreshDatabaseInfo();
    for(std::string tableName:databaseTableVector){
        deleteTable(std::shared_ptr<Table>(new Table(tableName)));
    }
}

/**
 * \brief method used to delete a specific table from the database.
 * @param table is the name of the table to delete.
 */
void Database::deleteTable(std::shared_ptr<Table> table){
    table->deleteAllColumns();
    std::string tableDelete = table->getTableFilePath();
    databaseFile.open(databaseFilePath, std::ios::in);
    std::ofstream  temp;
    temp.open("temp.txt");

    std::string line;
    while(databaseFile>>line){
        if(line!=tableDelete){
            temp<<line<<std::endl;
        }
    }
    databaseFile.close();
    temp.close();
    remove((databaseFilePath).c_str());
    rename("temp.txt",(databaseFilePath).c_str());
    std::remove((tableDelete).c_str());
}

/**
 * \brief method used to retrieve all the tables contained in the database.
 * @return a vector with the file path of the tables of the database.
 */
std::vector<std::string> Database::getTables() {
    std::vector<std::string> toRet;
    for(std::string info : databaseInfoVector){
        //std::cout<<info<<"\n";
        if(endsWith(info,"_table")){
            toRet.push_back(info);
        }
    }
    return  toRet;
}
