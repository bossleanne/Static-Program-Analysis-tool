#pragma once
#include <sstream>
#include <fstream>
#include <vector>
#include "Database.h"
#include "Tokenizer.h"
#include "utils.h"
#include "InfixToPostfix.h"
#include "Follow.h"
#include "Parent.h"
#include <queue>
//#include "conditionParsing.h"

#include <iostream>

using namespace std;

class SourceProcessor {
public:
	// method for processing the source program
    static void readParser(int &stmtNum, string procedureName, string readVar);
    static void printParser(int &stmtNum, string procedureName, string printVar);
    static void assignParser(int &stmtNum, string procedureName, vector<string>&tokens, int &i);
    static void ifParser(int &stmtNum, string procedureName,vector<string> &tokens, int &i);
    static void whileParser(int &stmtNum, string procedureName, vector<string> &tokens, int &i);
    static vector <string> exprParser(vector<string>&variables, vector<string>&constant,vector<string> &tokens, int &i);
    static void isFollow(int stmt1,int stmt2,string &procedureName);

    //Clause parsing:
    static void patternParser(vector<string>postfix);

    //utile
    static void contentParser(string type,int typecount,vector<string>&tokens,int&i,int &stmtNum,string procedureName,string startstmt);
    static void conditionParser(vector<string>&tokens, int &i, int &stmtNum, string procedureName);
//    static void parents();

    //    void callParser()
    static void stmtList(vector<string>tokens,int &i,int &stmtNum,int parents,string procedureName);
    static void process(string program);

//    static void checkVar(vector <string>&variables,string token);
//    static void checkConst(vector <string>&constant,string token);



};