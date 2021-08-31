//
// Created by Leanne on 20/2/21.
//

#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <math.h>

#include "Tokenizer.h"
#include "Database.h"

using namespace std;


class InfixToPostfix {
public:
    static bool isOptr(string s);
    static int priority(string c);
    static vector<string> in_to_post(string expression);
    static bool isCal(string s);
    static bool isOrAnd(string s);
    static bool isScope(string s);
    static void partialExp(string procedureName, int stmtNum, vector<string> expression);
};