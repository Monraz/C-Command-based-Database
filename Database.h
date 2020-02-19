//
// Created by Christo on 3/5/2019.
//

#ifndef MONRAZD_DATABASE_H
#define MONRAZD_DATABASE_H
#pragma once
#include "User.h"
#include "Table.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>

class Database {
    std::string databaseName;
    std::string databaseFilePath;
    std::fstream databaseFile;
    std::vector<std::string>databaseInfoVector;
    std::vector<std::string>databaseTableVector;

public:

    //--------------------public member variables--------------

    //------------------Constructor---------------------------
    Database();

    Database(std::string name, std::string username);
    Database(std::string databaseFilePath);

    //------------------Getters and Setters--------------------

    std::string getDatabaseName(bool withoutSignature);

    std::string &getDatabaseFilePath();

    std::vector<std::string> getTables();

    void refreshDatabaseInfo();
    void deleteTable(std::shared_ptr<Table>table);
    void deleteAllTables();



};


#endif //MONRAZD_DATABASE_H
