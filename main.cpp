/**Christopher Monraz
 *
 * last modification 5/15/2019
 * */
#include <iostream>
#include <memory>
#include <stdlib.h>
#include "Classes/User.h"
#include "Classes/User.cpp"
#include "Classes/UserList.h"
#include "Classes/UserList.cpp"
#include "Classes/FileManager.cpp"
#include "Classes/FileManager.h"
#include "Classes/Database.cpp"
#include "Classes/Database.h"
#include "Classes/Table.h"
#include "Classes/Table.cpp"
#include <cstdio>

using namespace std;

/*---------------------HOW THIS DATABASE WORKS---------------------------
 *
 * This database is being created with scalability and flexibility as the foundations.
 * Therefore, EVERYTHING IS A CLASS: the users, the databases, the tables and the
 * columns of the tables. The modularity of this structure allows the programer to have more
 * possibilities and ways to execute the desired functions.
 *
 * The method used to save the information (users, databases, tables and the actual data)
 * is with text files (for now... it will be as binary files later). Eeach class will have
 * a signature used to differentiate the textfiles from different kinds of classes
 * For example, a text file from a User will be named "userName_user" being "_user" the signature
 **/






/*------THINGS TO AVOID IF YOU DON'T WANT THIS CODE TO STOP WORKING-------
 *
 *-Don't change the name of the main.cpp source code! The lenght of the name of this file is
 * required to be 8 char lenght because it's needed to get the correct path of the project
 *
 * -Don't enter "0" as password, that value is reserved to Exit from the menus
 *
*/

//endsWith is used to check if a substring matches the ending of a string. If it does, returns a true boolean.
//This function is used to check if a textfile contains a line with a signature "_user", "_database", etc



/**
 * \brief function used to display the welcome messsage an to ask for the username.
 */
void welcomeMessage(){
    cout<<"Welcome to DATABASE MONRAZ!\n Enter your username: ";
}
/**
 * \brief function used to create a new Database.
 * @param user is a string containing the username of the user that will own the database.
 * @return a smart pointer to the new Database created.
 */
shared_ptr<Database> createNewDatabase(shared_ptr<User>user){
    string answer;
    cout<<"\nEnter a name for the new Database: ";
    cin>>answer;
    shared_ptr<Database>toRet(new Database(answer,user->getUserName()));
    cin.ignore();
    return toRet;
}
/**
 * \brief function used to select an existant Database from the list of database a user owns.
 * @param user is a string containing the username of the user.
 * @return a smart pointer that points to the selected Database.
 */
shared_ptr<Database> userDatabaseSelect(shared_ptr<User> user){
    vector<string>userVect = user->getDatabases();
    cout<<"\nWelcome "<<user->getUserName()<<"\n\n";
    int i = 1;
    string answer;
    cout<<"Select a Database or Enter 0 to create a new one: "
          "\n[0]Create new Database";
    for(string data : userVect){
        cout<<"\n["<<i++<<"]"<<data;
    }
    cin>>answer;
    //cout<<"\nAnswer: "<<answer;
    //cout<<"\nVect: "<<userVect.size();
    i=validateAnswerRange(userVect.size(),answer);
    cin.ignore();
    if(i==0){
        return createNewDatabase(user);
    }
    shared_ptr<Database>toRet(new Database(userVect.at(i-1)));
    return toRet;
}

/**
 * \brief function used to login using a username and a password.
 * @return a smart pointer that points to the logged User.
 */
shared_ptr< User> userLogin(){
    // dataPath stores the working directory of the project. The method used to get the path
    //is based on the MACRO __FILE__ that returns the whole path, including "main.cpp"
    //To delete the "main.cpp" from the path the .substr method of string is used to cut off
    //The last 8 characters of the path.
    string dataPath = ((string)__FILE__).substr(0,(((string)__FILE__).size()-8));

    shared_ptr<User> userR;
    string userName;
    string userPassword;
    string answer;


    bool isregistered = false;
    /*This boolean is to:
     * 1. Control the while loop that loops until a user logs in or a new user is created
     *
     * 2.As parameter for the constructors of the User. The constructor User(string,bool) has to differnt ways
     * to initialize a User. If the user is registered it will take the information saved in the File of the existing user
     * and set it in the corresponding variables of the user.
     *
     * If the user isn't registered it will create a new one. A password will be required to be entered, then the userName,
     * userFilePath and the password are set. Next, a new file will be created for the user and the "name_user"
     * and "password_password" values will be stored in the file.
     * */



    UserList userlist = UserList(dataPath + "\\UserListFile");
    /*UserList is a class used to save the name of the users in a File. A new UserList is created with the path to an existant
     * file*/

    //While the user isn't registered, keep asking for a valid username or create a new one.
    while(!isregistered){
        welcomeMessage();
        getline(cin,userName);

        //If the user is registered, create a new instance of User. The cosntructor will link the information in the user file to
        //the member variables of the new user.
        if(userlist.isUserRegistered(userName)){
            isregistered = true;
            shared_ptr<User> user(new User(userName, isregistered));
            userR= user;
            //The password of the user is asked
            cout<<"\nEnter password:";
            cin>>answer;

            //If the password doesnt match the password stored in the user File, keep asking for it or enter "0" to Exit.

            while(!(user->validatePassword(answer))){
                if(answer=="0"){
                    break;
                }
                cout<<"\nWrong password.\n"
                      "Try again or enter 0 to Exit.";
                getline(cin,answer);
            }
            cin.ignore();
        }else{

            //If the username is not registered the user can create a new profile using that name. If the user doesnt
            //want ot create it, the program will ask again for a valid username.
            isregistered = false;
            cout<<"\nYour username is not registered.\n"
                  "Do you want to create a new user with this name?\n"
                  "[1]YES\n"
                  "[0]NO";
            getline(cin,answer);


            //If the user wants to register a new profile the constructor will create the file of the user.
            if(isYes(answer)){
                shared_ptr<User> user(new User(userName, isregistered));
                userR = user;
                userlist.addUser(user);
                isregistered = true;
            }else{
                cout<<"\nDo you want to terminate the program?\n"
                      "[1]YES\n"
                      "[0]NO";
                getline(cin,answer);

                //If yes, the program will terminate
                if(isYes(answer)){
                    exit(0);
                }
            }

        }
    }
    return userR;
}


/**
 * \brief a function used to create a new Database, if the user has no databases she/he will
 * be asked to create a new one.
 * @param user is a string containing the username of the user that will own the Database.
 * @return a smart pointer that points to the created database.
 */
shared_ptr<Database> databaselogin(shared_ptr<User> user){
    //If the user has no Databases, ask the user if he wants to create one.
    if((user->getDatabases()).empty()){
        string answer;
        cout<<"\nYou have no Databases.\nDo you want to create a new one?"
              "\n[1]YES"
              "\n[0]NO";
        cin>>answer;
        if(isYes(answer)){
            return createNewDatabase(user);

        }else{
            exit(0);
        }
        cin.ignore();
    }else{
        return userDatabaseSelect(user);
    }
}
/**
 * \brief function used to select a Table from the existant tables in a Database.
 * @param database is a string that contains the name of the database.
 * @param user is a string that contains the usernama of the user.
 * @return a smart pointer that points to the selected Table.
 */
shared_ptr<Table> databaseTableSelect(shared_ptr<Database>database, shared_ptr<User>user){
    vector<string>tableVect = database->getTables();
    cout<<"\nDatabase "<<database->getDatabaseName(true)<<"\n\n";
    int i = 1;
    string answer;
    cout<<"\nSelect a table or enter 0 to edit the Database: "
          "\n[0]Edit  or create new Table";

    for(string table : tableVect){
        cout<<"\n["<<i++<<"]"<<table;
    }
    cin>>answer;

    i=validateAnswerRange(tableVect.size(),answer);
    cin.ignore();
    if(i==0){
        cout<<"\nDo you want to create a table?.\n"
              "[1]Yes\n"
              "[0]No";
        cin>>answer;
        cin.ignore();
        if(isYes(answer)){
            cout<<"\nHow do you want to create the table?.\n"
                  "[1]User Input\n"
                  "[0]Text File Input";
            cin>>answer;
            if(isYes(answer)){
                cout<<"\nEnter a name for the new Table: ";
                cin>>answer;
                cin.ignore();
                return shared_ptr<Table>(new Table(answer,database->getDatabaseName(true)));
            }else{
                cout<<"Enter the path to the Text File:";
                cin.ignore();
                getline(cin,answer);

                bool throwIfWrong = true;
                try{
                    shared_ptr<Table>toRet(new Table(answer, database->getDatabaseName(true),throwIfWrong));
                    return toRet;
                }catch(exception& e){
                    cout<<"\n"<<e.what();
                    return databaseTableSelect(database,user);
                }
            }
        }else{
            cout<<"\nWhat do you want to delete?.\n"
                  "[1]Table\n"
                  "[0]Database";
            cin>>answer;
            cin.ignore();
            if(isYes(answer)){

                if((database->getTables()).size()<1){
                    cout<<"\nYou already have no tables.";
                    databaseTableSelect(databaselogin(user),user);

                }else{
                    cout<<"\nSelect the table you want to delete: ";
                    i=0;
                    for(string table : tableVect){
                        cout<<"\n["<<i++<<"]"<<table;
                    }
                    cin>>answer;
                    cin.ignore();
                    i=validateAnswerRange(tableVect.size(),answer);
                    database->deleteTable(shared_ptr<Table>(new Table(tableVect.at(i))));
                }
            }else{
                user->deleteDatabase(database);
                databaseTableSelect(databaselogin(user),user);
            }
        }
    }
    shared_ptr<Table>toRet(new Table(tableVect.at(i-1)));

    return toRet;
}
/**
 * \brief function used to display the menu of the Database, the main purpose of the menu is
 * to select an existant table or create a new one.
 * @param database is the name of the database.
 * @param user is the username of the database.
 * @return a smart pointer that points to the selected table.
 */
shared_ptr<Table> databaseMenu(shared_ptr<Database>database, shared_ptr<User>user){
    if(database->getTables().empty()){
        string answer;
        cout<<"\nThere are no tables in this Database.\n"
              "What do you want to do?\n"
              "[1]Create a table\n"
              "[2]Continue without table\n"
              "[0]Exit";
        cin>>answer;
        cin.ignore();
        int option = validateAnswerRange(2,answer);
         switch(option){
             case 0:
                 cout<<"Do you want to go back to your Database List or to Exit?"
                       "\n[1]Database List Menu"
                       "\n[0]Exit";
                 cin>>answer;
                 if(isYes(answer)){

                     return databaseMenu(databaselogin(user),user);

                 }else{
                     exit(0);
                 }
                 break;
             case 1:
                 cout<<"\nHow do you want to create the table?.\n"
                       "[1]User Input\n"
                       "[0]Text File Input";
                 cin>>answer;
                 cin.ignore();
                 if(isYes(answer)){
                     cout<<"\nEnter a name for the new Table: ";
                     cin>>answer;
                     cin.ignore();
                     return shared_ptr<Table>(new Table(answer,database->getDatabaseName(true)));
                 }else{
                     cout<<"Enter the path to the Text File:";
                     getline(cin,answer);

                     bool throwIfWrong = true;
                     try{
                         shared_ptr<Table>toRet(new Table(answer, database->getDatabaseName(true),throwIfWrong));
                         return toRet;
                     }catch(exception& e){
                         cout<<"\n"<<e.what();
                         return databaseMenu(database,user);
                     }
                 }
             case 2:
                 return databaseTableSelect(database, user);

         }
    }else{
        return databaseTableSelect(database, user);
    }
}

/**
 * \brief function used to add a new column in a Table.
 * @param table is a string that contains the name of the Table where the column will be added.
 */
 void addColumn(shared_ptr<Table>table){
    string answer;
    string columnName;
    while(true){
        cout<<"\nEnter a name for the column: ";
        cin>>columnName;
        cin.ignore();
        shared_ptr<Column>toRet;

        int selection;
        std::cout<<"\nEnter the datatype of this column:"
                   "\n[0]Integer"
                   "\n[1]String"
                   "\n[2]Character"
                   "\n[3]Boolean"
                   "\n[4]Double";
        std::cin>>answer;
        std::cin.ignore();
        //std::cout<<"\nSTOP!";
        selection=validateAnswerRange(4,answer);
        //std::cout<<"\nSTAP!";
        switch (selection){
            case INT:{
                shared_ptr<Column>toRet(new ColumnInt(columnName,table->getTableName(true)));
                break;
            }
            case STRING:{
                shared_ptr<Column>toRet(new ColumnString(columnName,table->getTableName(true)));
                break;
            }
            case CHAR: {
                shared_ptr<Column> toRet(new ColumnChar(columnName, table->getTableName(true)));
                break;
            }
            case BOOL: {
                shared_ptr<Column> toRet(new ColumnBool(columnName, table->getTableName(true)));
                break;
            }
            case DOUBLE:{
                shared_ptr<Column>toRet(new ColumnDouble(columnName,table->getTableName(true)));
                break;
            }
        }

        cout<<"\nDo you want to create more columns?"
              "\n[1]YES\n"
              "[0]NO";
        cin>>answer;
        cin.ignore();
        if(!isYes(answer)){
            break;
        }
        table->refreshTableInfo();

    }
}


/**
 * \brief function used to check if a table has no columns, if it is empty it will ask
 * the user if she/he wants to add columns to the table.
 * @param table is a string that contains the name of the table.
 * @param database is a string that contains the name of the database where the table is located.
 * @param user is a string containing the username of the user applying the changes.
 */
void ifTableEmpty(shared_ptr<Table>table, shared_ptr<Database>database, shared_ptr<User>user){
    table->refreshTableInfo();
    if(table->getColumns().empty()){
        string answer;
        cout<<"\nThere are no columns in this table.\n"
              "Do you want to add columns?"
              "\n[1]YES"
              "\n[0]NO";
        cin>>answer;
        cin.ignore();
        if(isYes(answer)){
           addColumn(table);

        }else{
            cout<<"Do you want to go back to your Table List or to  the program?"
                  "\n[1]Table List Menu"
                  "\n[0]Exit";
            cin>>answer;
            cin.ignore();
            if(isYes(answer)){

                ifTableEmpty(databaseMenu(database,user),database, user);

            }else{
                exit(0);
            }
        }
    }
}

/**
 * \brief function used to delete a column from a table.
 * @param table a string containing the name of the Table where a column will be deleted.
 */
void deleteColumnMenu(shared_ptr<Table>table){
    cout<<"\nWhich column do you want to delete?";
    string answer;
    int intAnswer;
    table->printColumn(true);
    cin>>answer;
    cin.ignore();
    intAnswer=validateAnswerRange((table->tableColumnVector).size(),answer);
    table->deleteColumn(shared_ptr<Column>(new Column((table->tableColumnVector).at(intAnswer))));
}

/**
 * \brief this function is the core of the program, it displays the options to manipulate a table,
 * this function calls the different functions and methods needed to manipulate a table.
 * @param table is a string containing the table to manipulate.
 * @param database is a string that contains the name of the database.
 * @param user is a string containing the username of the user doing the changes.
 */
void tableMod(shared_ptr<Table>table, shared_ptr<Database>database, shared_ptr<User>user){
    ifTableEmpty(table,database,user);
    table->refreshTableInfo();
    vector<string>columnVect = table->getColumns();
    cout<<"\nColumns: \n";
    table->printColumn(false);
    cout<<" \n";
    int i = 1;
    string answer;
    cout<<"\nWhat changes do you want to do in this table?: "
          "\n[1]Add columns"
          "\n[2]Delete columns"
          "\n[3]Delete table"
          "\n[4]Insert data"
          "\n[5]Export data"
          "\n[6]Query"
          "\n[7]Show Table"
          "\n[0]Exit";

    cin>>answer;
    cin.ignore();

    i=validateAnswerRange(7,answer);
    switch (i){
        case 0:
            cout<<"Do you want to go back to your Table List or to Exit the program?"
                  "\n[1]Table List Menu"
                  "\n[0]Exit";
            cin>>answer;
            if(isYes(answer)){
                tableMod(databaseMenu(database,user),database,user);

            }else{
                exit(0);
            }

            break;
        case 1:
            addColumn(table);
            tableMod(table,database,user);
            break;
        case 2:
            deleteColumnMenu(table);
            tableMod(table,database,user);
            break;
        case 3:
            database->deleteTable(table);
            system("CLS");
            tableMod(databaseMenu(database,user),database,user);
            break;
        case 4:
            table->addRow(table->getRowFromUser());
            tableMod(table,database,user);
            break;
        case 5:
            cout<<"\nEnter the name of the Export File: ";
            getline(cin,answer);
            table->exportFile(answer,"all");
            tableMod(table,database,user);
            break;
        case 6:
            table->query();
            tableMod(table,database,user);
            break;
        case 7:
            table->showTable();
            tableMod(table,database,user);
            break;
    }

}






/**
 * \brief the main function calls the primary functions that lead the user through the
 * steps needed to reach the bottom line of the program that is to be able to create and
 * manipulate a table.
 * @return a code with the exit value.
 */
int main() {

    ///A user logs into the system
    shared_ptr<User> user = userLogin();

    /**UP TO THIS POINT OF THE CODE A REGISTERED USER HAS LOGGED IN OR A NEW USER HAS BEEN CREATED
    * */

    system("CLS");

    ///The user selects a Database or creates a new one
    shared_ptr<Database>database = databaselogin(user);

    /**UP TO THIS POINT OF THE CODE A REGISTERED USER HAS LOGGED IN AND A DATABASE HAS BEEN SELECTED
     *OR CREATED
     * */

    system("CLS");

    ///The user selects a table from the database or creates a new one.
    shared_ptr<Table>table = databaseMenu(database,user);


    /**UP TO THIS POINT OF THE CODE A REGISTERED USER HAS LOGGED IN, HAS ACCESS A DATABASE
     * AND A TABLE HAS BEEN SELECTED OR CREATED.
     */
    system("CLS");

    ///The user manipulates a selected table.
    tableMod(table,database,user);
    //Database database = Database("Cars", chris.getUserName());
    //Table table = Table("Wheel", database.getDatabaseName());


    return 0;
}