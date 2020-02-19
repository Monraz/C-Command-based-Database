//
// Created by Christo on 3/5/2019.
//

#include "FileManager.h"



//------------------------Operator << >> overloading------------------------
/**
 * \brief overloaded operator to print the file path of the database
 * to a specified ostream.
 * @param out the ostream to print.
 * @param database is the database to print the file path from.
 * @return the ostream message.
 */
std::ostream& operator<<(std::ostream &out, Database &database) {
    out <<database.getDatabaseFilePath()<< "\n" <<std::endl;
    return out;
}
/**
 * \brief overloaded operator to read the file path of the database
 * to a specified istream
 * @param in the istream to print.
 * @param database is the database to retreive the file path from.
 * @return the istream message.
 */
std::istream & operator >> (std::istream &in,  Database &database)
{
    in >> database.getDatabaseFilePath();
    return in;
}

//------------FileManager methods definition---------------------

FileManager::FileManager(const std::string &path) : path(path) {

}


FileManager::FileManager() {}
