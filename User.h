//
// Created by Christo on 3/5/2019.
//

#ifndef MONRAZD_USER_H
#define MONRAZD_USER_H
#pragma once
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "FileManager.h"

/*-------------------------HOW IT WORKS------------------------
 *Each user owns a text file that saves the name of the user and the databases owned.
 * The Text file is named this way:  "name_user"   being "name" the name of the user
 * The text file is created when an object User is instantiated and there's no
 * name_user textfile in the directory.
 *
 *
 *
 *
 *
 *
 *
 * */


class User {
    std::string userName;
    std::string userFilePath;
    std::fstream userFile;
    std::string password;
    std::vector<std::string> userInfoVector;



public:
    //------------------Constructors---------------------------

    /* CONSTRUCTOR WITH NAME OF USER AS PARAMETER
     * This constructor will be the most extensively used. It takes a name as a
     * string and then it tries to open the userFile using the name provided and the
     * */
    User(std::string name);

    User();
    User(std::string name, bool isregistered);
    //---------------Public class members----------------------

    //---------------Getters and setters-----------------------

    const std::string &getUserFilePath() const;

    void setUserFilePath(const std::string &userFilePath);

    const std::string &getUserName() const;

    void setUserName(std::string &userName);

    //-----------------Methods------------------------------

    void refreshUserInfo();

    std::vector<std::string> getDatabases();

    std::string getPassword(bool withoutSignature);

    bool validatePassword(std::string answer);

    void deleteDatabase(std::shared_ptr<Database>database);

    void openDatabase();
    void saveDatabase();
};


#endif //MONRAZD_USER_H
