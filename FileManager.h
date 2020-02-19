//
// Created by Christo on 3/5/2019.
//

#ifndef MONRAZD_FILEMANAGER_H
#define MONRAZD_FILEMANAGER_H

#pragma once

#include <fstream>
#include <string>
#include "Database.h"

//------------------------Operator >>  << overloading-----------------------

std::ostream & operator << (std::ostream &out, const Database & database);
std::istream & operator>>(std::istream &in, Database &database);


class FileManager {
    std::string path;
    std::fstream fileStream;
public:
    FileManager(const std::string &path);

    FileManager();


};






#endif //MONRAZD_FILEMANAGER_H
