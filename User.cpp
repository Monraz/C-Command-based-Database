//
// Created by Christo on 3/5/2019.
//
#pragma once
#include "User.h"
#include "globalFunction.h"



//--------------------Constructors-----------------------
/**
 * \brief a Constructor used to create or retreive a user from the program files, If the username
 * is not located in the files, it will store it.
 * @param name is the username of the user.
 * @param isregistered is a boolean used to specify if the user has registered before in the program.
 */
User::User(std::string name, bool isregistered) {
    if(isregistered){
        userName = name;
        userFilePath =name+"_user";
        password = getPassword(true);
    }else{
        std::cout<<"\nEnter your password:";
        std::getline(std::cin,password);
        userName=name;
        //The userFilePath is set as the name of the user  + _user
        userFilePath = name+"_user";
        userFile.open(userFilePath);
        if(!userFile){
            userFile.open(userFilePath, std::ios::out | std::ios::app);
            userFile<<name+"_user"<<std::endl;
            userFile<<password+"_password"<<std::endl;
            userFile.close();
        }
        userFile.close();
    }
    refreshUserInfo();
}

/**
 * \brief default User Constructor.
 */
User::User() {}

//-----------------Getters and Setters-----------------------
std::vector<std::string > User::getDatabases() {
    std::vector<std::string> toRet;
    refreshUserInfo();
    for(std::string info : userInfoVector){
        //std::cout<<info<<"\n";
        if(endsWith(info,"_database")){
            toRet.push_back(info);
        }
    }
    return  toRet;
}

/**
 * \brief a method use to get the username of the user.
 * @return a string with the username of the user.
 */
const std::string &User::getUserName() const {
    return userName;
}

/**
 * \brief method used to change the username.
 * @param userName is a string that contains the new username.
 */
void User::setUserName(std::string &userName) {
    User::userName = userName;
    User::userFilePath = userName+"_user";
}


/**
 * \brief method used to get the filepath to the file that stores the information
 * of the user.
 * @return
 */
const std::string &User::getUserFilePath() const {
    return userFilePath;
}
/**
 * \brief method used to change the path to the file that stores the information of the user.
 * @param userFilePath is a string containing the new filepath.
 */
void User::setUserFilePath(const std::string &userFilePath) {
    User::userFilePath = userFilePath;
}

/**
 * \brief a method used to refresh the vector strings that
 * contains the information stored in the user file.
 *
 */
void User::refreshUserInfo() {
    std::string userInfo;
    userFile.open(userFilePath,std::ios::in);
    if(userFile){
        userInfoVector.clear();
        while(userFile>>userInfo){
            userInfoVector.push_back(userInfo);
        }
    }
    userFile.close();
}
/**
 * \brief method used to get the password stored in the file of the user.
 * @param withoutSignature is a boolean that specifies if the password should have the signature
 * "_password" or not.
 * @return a string with the password of the user.
 */
std::string User::getPassword(bool withoutSignature) {
    refreshUserInfo();
    if(withoutSignature){
        for(std::string info : userInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_password")){
                return info.substr(0,(info.size()-9));
            }
        }
        std::cout<<"\nThe user has no password";
    }else{
        for(std::string info : userInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_password")){
                return info;
            }
        }
        std::cout<<"\nThe user has no password";
    }
}
/**
 * \brief method used to check if the password given by the
 * user matches the records of the user file.
 * @param answer is a string with the password given by the user.
 * @return a boolean that is true if the password matches with the records of the user.
 */
bool User::validatePassword(std::string answer) {
    if((answer+"_password")==getPassword(false)){
        return true;
    }
    return false;
}
/**
 * \brief method used to delete a Database owned by the user.
 * @param database is s string that contains the name of the file to delete.
 */
void User::deleteDatabase(std::shared_ptr<Database> database){
    database->deleteAllTables();
    std::string databaseDelete = database->getDatabaseFilePath();
    userFile.open(userFilePath, std::ios::in);
    std::ofstream  temp;
    temp.open("temp.txt");

    std::string line;
    while(userFile>>line){
        if(line!=databaseDelete){
            temp<<line<<std::endl;
        }
    }
    userFile.close();
    temp.close();
    remove((userFilePath).c_str());
    rename("temp.txt",(userFilePath).c_str());
    std::remove((databaseDelete).c_str());
}



