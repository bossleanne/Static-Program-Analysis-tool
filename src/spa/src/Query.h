//
// Created by Leanne on 3/3/21.
//

#pragma once
#include "Database.h"
#include "Parent.h"
#include "Follow.h"
#include <map>
#include <vector>
#include <string>
//#include <bits/stdc++.h>
#include <iostream>
#include "utils.h"
#include "Use.h"
#include "Modifies.h"
#include "Pattern.h"

/*
    for query:
    step 1 : check it's a Singale select or double select
    step 2 : check if there's a such clause behind it
    step 3 : determine which calause it is
    step 4 : parse the lhs and rhs
    - 9 possible lhs and rhs
        clause (_,_) //select all
        clause (_,stmt)
        clause (stmt,_)
        clause (synonymType,synonymType)
        clause (_,synonymType)
        clause (synonymType,_)
        clause (stmt,stmt)
        clause (_,stmt)
        clause (stmt,_)
 */
class Query {
public:
    //step 1 check single
    static bool isClause(vector<string>&tokens);
    static bool isUseInRelation(vector<pair<string,vector<string>>> select);
    //iteration2 - one
    static void process(vector<string>tokens,vector<string> &databaseResults);
    static vector<string> matchTwoVect(vector<string> v1,vector<string> v2);
    static string getSynm(map<string,vector<string>> &synonyms,string &synm);
};
