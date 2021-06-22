//
// Created by Leanne on 3/4/21.
//

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Database.h"
#include <stack>
#include "utils.h"
#include <stack>
#include <math.h>
#include "utils.h"
#include "Tokenizer.h"
#include <map>
#include "Query.h"
#include "Tokenizer.h"
#include "InfixToPostfix.h"

class Pattern {
public:
    static bool pattern(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
    static string infixConversion(string postfix);
};



