//
// Created by Leanne on 31/3/21.
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

using namespace std;
class Use {
public:
    static bool useRelation(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
    static bool useRelationship(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
};
