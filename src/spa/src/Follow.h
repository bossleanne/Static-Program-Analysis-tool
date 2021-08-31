//
// Created by Leanne on 2/3/21.
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
using namespace std;

class Follow {
public:
    static bool followstar(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
    static bool follows(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs);
};



