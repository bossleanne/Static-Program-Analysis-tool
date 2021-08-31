//
// Created by Leanne on 1/4/21.
//

#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <math.h>
#include "utils.h"
#include "Tokenizer.h"
#include "Database.h"
#include <map>
#include "Query.h"
#include <regex>

class Modifies {
public:
    static bool modRelation(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
};



