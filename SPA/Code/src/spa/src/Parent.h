//
// Created by Leanne on 2/3/21.
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
class Parent {

public:
    static void parentsParse(string procedureName,vector<string> tokens);
    static bool parents(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
    static bool parentStar(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
};

