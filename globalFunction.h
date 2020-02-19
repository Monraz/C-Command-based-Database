//
// Created by Christo on 3/7/2019.
//


/**
 *
 *
 *
 * \brief This header file contains a group of functions that are use in several classes of this project
 * to validate the input of the user.
 *
 *
 *
 * \author $Author: bv $Christopher
 *

 *
 * \date $Date: 2019/05/16
 *
 * Contact: cmonraz@bhcc.edu
 *
 * Created on: February 20

 *
 */
#ifndef MONRAZD_GLOBALFUNCTION_H
#define MONRAZD_GLOBALFUNCTION_H

#include <string>

///startPointColumn is an int that specifies at which line the program
/// must start looking for the Data Entries in the stored Column Files
int startPointColumn = 3;

/**
 *
 * @param fullString is the string where the function will check if the ending matches the specified ending.
 * @param ending is a string that tells the function how the lsat part of the string must look like to return true.
 * @return true if fullString ends with endening, false otherwise.
 */
bool endsWith (std::string fullString, std::string ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
/**\brief used to check that an user entry is 0 or 1
 *
 * @param answer is an string provided for the user when a [1]YES or [0]NO question was asked to the user.
 * @return true if the answer is 1, false if the answer is 0
 */
bool isYes(std::string answer){
    while(!((!answer.compare("0"))|| (!answer.compare("1")))){
        std::cout<<"\nYou must input '0' or '1'.\nTry again\n";
        std::cin>>answer;
    }
    if(answer=="1"){
        return true;
    }
    return false;
}

/**
 * \brief used to check that an user entry contains numeric values like 1.43 or 434
 *
 * @param str is a string given by the user when he/she is asked to enter a number.
 * @return true if all the characters of the string are digits or '.'.
 */
bool isDigit(std::string str){
    for (char stringChar: str){
        if (isdigit(stringChar) == 0){
            if(stringChar!='.'){
                return false;
            }
        }
    }
    return true;
}

/**
 * \brief a function used to check that the user entry from a menu is inside the numeric range of answers
 * if the entry is not numeric or is out of range the user must input a valid answer. The returning value
 * wil be a valid integer entry.
 *
 * @param range is the maximum numeric value that the answer may have.
 * @param answer is the user entry.
 * @return a validated int that matches the numeric value of a menu option.
 */
int validateAnswerRange(int range, std::string answer){

    while(true){

        if(isDigit(answer)){

            for(int i = 0;i<=range;i++){

                if(i==stoi(answer)){
                    return i;
                }

            }
            std::cout<<"\nInvalid answer.The range is from 0 to "<<range;
            std::getline(std::cin,answer);
        }
        std::cout<<"\nInvalid answer. Enter just numbers.\n Try again.";
        std::getline(std::cin,answer);

    }
}

/**
 * \brief receives a user input and checks that the input is an integer, if it is it will return the integer value
 * @param value is a string given by the user
 * @return the validated integer value of the value.
 */
int validateInt(std::string value){
    while(true){
        if(isDigit(value)){
            return std::stoi(value);
        }else{
            std::cout<<"Enter just digits.\nTry again.";
            getline(std::cin,value);
        }
    }
}
/**
 * \brief receives a user input and checks that the input is a double, if it is it will return the double value
 * @param value is a string given by the user
 * @return the validated double value of the value.
 */
double validateDouble(std::string value){
    while(true){
        if(isDigit(value)){
            return std::stod(value);
        }else{
            std::cout<<"Enter just digits.\nTry again.";
            getline(std::cin,value);
        }
    }
}

/**
 * \brief checks if a user input is "true" or false" if not, the user must enter one of these options
 * @param data the user input
 * @return the validated string with the value "true" or "false"
 */
std::string validateBool(std::string data){
    while(true){
        if(data == "true"){
            return data;
        }else if(data== "false"){
            return data;
        }else{
            std::cout<<"Enter 'true' or 'false'.\nTry again.";
            getline(std::cin,data);
        }
    }
}





#endif //MONRAZD_GLOBALFUNCTION_H
