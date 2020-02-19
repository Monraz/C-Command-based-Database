//
// Created by Christo on 3/5/2019.
//

#include "UserList.h"

//---------------------add Functions------------------------
/**
 * \brief method used to register a new user by saving its username
 * in the file called UserListFile.
 * @param user is a string containing the username of the new user.
 */
void UserList::addUser(std::shared_ptr<User> user) {
    userlistFile.open(userListFilePath, std::ios::in | std::ios::app);
    if(userlistFile){
        userlistFile<<user->getUserName()+"_user"<<std::endl;
    }
    userlistFile.close();
}

// ----------------Refresh UserlistVector-------------------
/**
 * \brief method used to refresh the vector string that contains
 * all the usernames registered in the program.
 */
void UserList::refreshUserList() {
    std::string userListInfo;
    userlistFile.open(userListFilePath,std::ios::in);
    if(userlistFile){
        //std::cout<<"\nREFRESHING\n";
        userListVector.clear();
        while(userlistFile>>userListInfo){
            //std::cout<<"\n"<<userListInfo;
            userListVector.push_back(userListInfo);
        }
    }
    userlistFile.close();
}
/**
 * \brief method used to check if the specified username is
 * registered in the program
 * @param user is a string that contains the username to check.
 * @return a boolean that is true if the usernama is registered
 * in the program.
 */
bool UserList::isUserRegistered(std::string user) {
    refreshUserList();
    for(std::string userName : userListVector){
        if(0== userName.compare(user+"_user")){
            return true;
        }
    }
    return false;
}
/**
 * \brief Constructor used to initialize the UserList object
 * that will load the list of users registered in the system.
 * @param path
 */
UserList::UserList(std::string path){
    userListFilePath = path;
    refreshUserList();

}

