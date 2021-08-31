//
// Created by Leanne on 20/2/21.
//

#include "utils.h"
#include "InfixToPostfix.h"
//#include <vector>
//#include <string>
//#include <iostream>
//using namespace std;

//check if the variable is a c or int
bool utils::isDigit(string str) {
    for (char& ch : str) {
        if (isdigit(ch)==false) {
            return false;
        }
    }
    return true;
}