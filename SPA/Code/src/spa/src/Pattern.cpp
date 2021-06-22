//
// Created by Leanne on 3/4/21.
//

#include "Pattern.h"
bool matchUnderline(string &exp){
    //true is a value partal exp, false it's not a valid exp
    //return chopped exp
    string underlineL = "";
    string underlineR = "";
    underlineL = exp.front(); // return "_"
    underlineR = exp.back();
    if(underlineL == "_" && underlineR == "_"){
        exp = exp.substr(1,exp.size()-2);
        return true;
    }else if(underlineL != "_" && underlineR != "_"){//false means it's a full partial exp
        return false;
    }else{
        exp = "-1";
    }

}

bool Pattern::pattern(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs){
    //query
    string sqlTemp = "";
    //pattern
    vector<string> selectBuffer;
    vector<string> stmtStmtBuffer;
    vector <string> patternBuffer;
    vector<string> varibaleBuffer;
    string lhsSynm = Query::getSynm(synonyms,lhs);
    string rhsSynm = Query::getSynm(synonyms,rhs);
    string fullExp = "";
    bool partExp = false;
    string underline = "";
    string exp = "";
    // tokenize the program
    Tokenizer tk;
    vector<string> tokens;
    bool sameDigit = false;
    vector<string> inPoFix;

    //?,_
    if (rhs == "_") {
        //_,_
        if (lhs == "_") {
            sqlTemp = "SELECT stmtNum FROM expression;";
            Database::getPattern(followBuffer,sqlTemp);
        }
        //"x",_
        else if (lhsSynm == "-1") { //lhs is "var"
            selectBuffer.clear();
            stmtStmtBuffer.clear();
            tokens.clear();
            varibaleBuffer.clear();

            //check if lhs it's a partial or full exp
            exp = lhs;
            exp = exp.substr(1, exp.size() - 2);
            sqlTemp = "SELECT stmtNum FROM pattern WHERE lhs = '" + exp + "';";
            Database::getPattern(followBuffer, sqlTemp);
        }
        else{ //lhs is all diff stmt
            if(lhsSynm == "variable"){
                sqlTemp = "SELECT stmtNum FROM pattern;";
                Database::getPattern(followBuffer, sqlTemp);
            }

        }
    }

    //?,""
    else if (rhsSynm == "-1"){
        varibaleBuffer.clear();
        selectBuffer.clear();
        stmtStmtBuffer.clear();
        tokens.clear();
//        rhs = rhs.substr(1,rhs.size()-2);
        //check if rhs it's a partial or full exp
        exp = rhs;

        partExp = matchUnderline(exp);
        exp = exp.substr(1,exp.size()-2);

        if(exp!= "-1"){
            inPoFix = InfixToPostfix::in_to_post(exp);
            exp = "";
            for(string s:inPoFix){
                exp= exp + s + " ";
            }
            if(partExp){ //match true means its partial exp
                sqlTemp = "SELECT stmtNUm FROM pattern WHERE partExp LIKE '%"+ exp +"%';"; //select the stmtNum fitst
                Database::getPattern(stmtStmtBuffer,sqlTemp);
                sqlTemp = "SELECT partExp FROM pattern WHERE partExp LIKE '%"+ exp +"%';"; //select the stmtNum fitst
                Database::getPattern(patternBuffer,sqlTemp);
                for(int i=0;i<patternBuffer.size();++i){
                    tk.tokenize(patternBuffer.at(i), tokens);
                    if(utils::isDigit(exp)){ // if its a digit, check for matching before pushing back
                        for(string t:tokens){
                            if(exp.size() == t.size()){
                                sameDigit = true;
                            }else{
                                i++;
                                sameDigit = false;
                            }
                        }
                        if(sameDigit){
                            selectBuffer.push_back(stmtStmtBuffer.at(i));
                            varibaleBuffer.push_back(patternBuffer.at(i));
                        }
                    }
                    else{//else if it;s not a int direct push back the stmt;
                        selectBuffer.push_back(stmtStmtBuffer.at(i));
                        varibaleBuffer.push_back(patternBuffer.at(i));
                    }
                }

            }
            else{ //match false means it's a full exp
                sqlTemp = "SELECT stmtNum FROM pattern WHERE partExp = '"+ exp +"';";
                Database::getPattern(selectBuffer,sqlTemp);
            }
        }
        else{
            return false;
        }
        //_,"x"
        if(lhs == "_")
        {
            followBuffer = selectBuffer;
        }
        //stmt,"x"
        else{
            followBuffer = selectBuffer;
        }

    }

    //?,_""_
}