//
// Created by Christo on 3/4/2019.
//

#include <map>
#include <string>
enum DataType{
    INT = 0,
    STRING = 1,
    CHAR = 2,
    BOOL = 3,
    DOUBLE = 4

};

std::map<DataType ,std::string>enumStringMap = {
        {INT, "int"},
        {STRING, "string"},
        {CHAR, "char"},
        {BOOL, "bool"},
        {DOUBLE, "double"}
};

std::map<std::string, DataType>enumDatatypeMap = {
        {"int", INT },
        {"string", STRING },
        {"char", CHAR},
        {"bool", BOOL },
        {"double", DOUBLE }
};


