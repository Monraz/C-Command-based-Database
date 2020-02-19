//
// Created by Christo on 3/5/2019.
//

#ifndef MONRAZD_USERLIST_H
#define MONRAZD_USERLIST_H

#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "globalFunction.h"
#include <memory>


class UserList {
    std::string userListFilePath;
    std::fstream userlistFile;
    std::vector<std::string > userListVector;
public:
    UserList(std::string path);

    void addUser(std::shared_ptr<User>user);
    bool isUserRegistered(std::string user);
    void addMessage(std::string message);
    void refreshUserList();


};


#endif //MONRAZD_USERLIST_H
