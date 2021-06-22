//
// Created by Leanne on 1/4/21.
//

#include "Modifies.h"


//void getAllVar(string stmtType){
//    if(stmtType == "call")
//    if(stmtType == "while")
//    if(stmtType == "if")
//}



bool Modifies::modRelation(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs) {
//    define l;hs and rhs
    //query
    string sqlTemp = "";
    //three type of query from SQL _,synm
    string tmpSynm = "";
    vector<string> constStmtBuffer;
    vector<string> varStmtBuffer;
    vector<string> stmtStmtBuffer;
    vector<string> procedureBuffer;

    //Modifies relaitionship
    vector<string> selectBuffer;
    vector<string> numBuffer; //_,num after compairinga and join back to Follow
    vector<string> varInRelationBuffer;
    vector<string> varInRelationExist;
    vector<string> constInRelationBuffer;
    vector<string> numBufferB;
    vector<string> buffer;
    bool exist = true;
    bool isParentStmt = false;
    bool isVar = false;
    bool result = true;
    string leftTmp = "";
    leftTmp = Query::getSynm(synonyms, lhs);
    bool varCheck = false;
    string selectVar = "";
    vector<string> callBuffer;

    string lhsSynm = Query::getSynm(synonyms,lhs);
    string rhsSynm = Query::getSynm(synonyms,rhs);
    string tmprhs = rhs;
    rhs = "";
    for(char c:tmprhs){
        if(c != '\"'){
            rhs+=c;
        }
    }
    string tmplhs = lhs;
    lhs = "";
    for(char c:tmplhs){
        if(c != '\"'){
            lhs+=c;
        }
    }
    //modified checking for
    for(int i = 0; i < select.size(); i++)
    {
        cout << select[i].first << ", "  << endl;
        selectVar = select[i].first;

        if( lhs == "_" ){
            //_,_
            if(rhs == "_"){
                return false;
            }
            //_,num
            else if(utils::isDigit(rhs)){
                return false;
            }
            //_,synm
            else{
                if(rhsSynm=="-1"){
                    sqlTemp = "SELECT variable FROM modifies WHERE variable = '"+ rhs +"';";
                    Database::getUsesSql(followBuffer,sqlTemp);
                    if(!followBuffer.empty()){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else if(rhsSynm == "variable"){
                    return false;
//                    sqlTemp = "SELECT variable FROM modifies;";
//                    Database::getUsesSql(followBuffer,sqlTemp);
//                    if(followBuffer.empty()){
//                        return false;
//                    }
                }
                else{
                    return false;
                };
            }
            Database::insertRelation("Modifies",lhs,rhs,"T");
        }

            //num,?
        else if(utils::isDigit(lhs)){
            stmtStmtBuffer.clear();
            selectBuffer.clear();
            //chcek if num exist in the data
            sqlTemp = "SELECT child FROM parents WHERE parent = '" + lhs +"';";
            Database::getModSql(selectBuffer,sqlTemp);
            if(!selectBuffer.empty()){
                selectBuffer.push_back(lhs);
                isParentStmt = true;
            }
            else{
                sqlTemp = "SELECT stmtNum FROM modifies WHERE stmtNum = '" + lhs + "';";
                Database::getModSql(selectBuffer, sqlTemp);
            }
            if(selectBuffer.empty()){
                return false;
            }

            //num,_
            if(rhs == "_"){
                sqlTemp = "SELECT variable FROM modifies WHERE stmtNum = '" + rhs + "';";
                Database::getModSql(followBuffer, sqlTemp);
                if(followBuffer.empty()){
                    return false;
                }
            }

            //num,num
            if(utils::isDigit(rhs)){
                return false;
            }

            //num,synm -> need to check if theres parents
            else{
                //selectBuffer stored stmt line from parent or single synm
                for(string p:selectBuffer) {
                    //multi procedure
                    if(rhsSynm=="-1" && rhs!= "_") {
                        sqlTemp = "SELECT variable FROM modifies WHERE variable = '" + rhs + "' AND stmtNum = '" + p + "';";
                        Database::getModSql(followBuffer, sqlTemp);
                    }
                    else if (rhsSynm == "variable") {

                        //check if num is a call
                        sqlTemp ="SELECT variableName FROM variables WHERE procedureName in (SELECT procedureName FROM call WHERE stmtNum = '"+ p+"');";
                        Database::getModSql(callBuffer,sqlTemp);

                        if(!callBuffer.empty()){
                            followBuffer = callBuffer;
                        }
                        else if(isParentStmt){
                            stmtStmtBuffer.clear();
//                            followBuffer.clear();
                            sqlTemp = "SELECT variable FROM modifies WHERE stmtNum  = '" + p + "';";
                            cout << "                           ss23            debug " << p<<endl;
                            Database::getModSql(followBuffer, sqlTemp);

//                            sqlTemp = "SELECT procedureName FROM modifies WHERE stmtNum  = '" + p + "';";
//                            Database::getModSql(stmtStmtBuffer, sqlTemp);
//                            for(string s:stmtStmtBuffer){
//                                sqlTemp = "SELECT calling FROM callstar WHERE procedureName  = '" + s + "';";
//                                Database::getModSql(followBuffer, sqlTemp);
//                            }
                        }
                        else{
                            stmtStmtBuffer.clear();
                            sqlTemp = "SELECT variable FROM modifies WHERE stmtNum  = '" + p + "';";
                            Database::getModSql(followBuffer, sqlTemp);
                        }

                    }
                    else if(rhs == "_"){
                        sqlTemp = "SELECT variable FROM modifies WHERE stmtNum  = '" + lhs + "';";
                        Database::getModSql(followBuffer, sqlTemp);
                        if(followBuffer.empty()){
                            return false;
                        }
                    }
                    else if(rhsSynm == "call" ){
                        stmtStmtBuffer.clear();
//                        extract the procedure name being called
                        sqlTemp = "SELECT procedureName FROM modifies WHERE stmtNum  = '" + p + "';";
                        Database::getModSql(stmtStmtBuffer, sqlTemp);
                        for(string s:stmtStmtBuffer){
                            sqlTemp = "SELECT calling FROM callstar WHERE procedureName  = '" + s + "';";
                            Database::getModSql(followBuffer, sqlTemp);
                        }


//                        select the variable with same procedure name
                        for(string s:callBuffer){
                            sqlTemp = "SELECT variable FROM  WHERE stmtNum  = '" + lhs + "';";
                            Database::getModSql(followBuffer, sqlTemp);
                        }
                    }
                    else if(rhsSynm == "procedure"){
                        sqlTemp = "SELECT procedureName FROM call WHERE stmtNum  = '" + lhs + "';";
                        Database::getModSql(followBuffer, sqlTemp);

                        sqlTemp = "SELECT variable FROM modifies WHERE stmtNum  = '" + lhs + "';";
                        Database::getModSql(followBuffer, sqlTemp);
                    }
                }
                Database::insertRelation("Modifies",lhs,rhs,"T");
            }

        }
        //synm,?

        else if(lhs!= "_" && !utils::isDigit(lhs)){

            stmtStmtBuffer.clear();
            selectBuffer.clear();
            //chcek if num exist in the data
            if(lhsSynm == "while" || lhsSynm == "if"){
                sqlTemp = "SELECT DISTINCT stmtNum FROM statements WHERE stmtType = '"+ lhsSynm +"';";
                Database::getModSql(selectBuffer, sqlTemp);
                for(string s:selectBuffer){
                    sqlTemp = "SELECT child FROM parents WHERE parent = '" + s +"';";
                    Database::getModSql(stmtStmtBuffer,sqlTemp);
                    if(!stmtStmtBuffer.empty()){
                        stmtStmtBuffer.push_back(lhs);
                    }
                    else{
                        return false;
                    }
                }
            }
            else if (lhsSynm == "variable") {

                sqlTemp = "SELECT variable FROM modifies;";
                Database::getModSql(stmtStmtBuffer, sqlTemp);
            }
            //"x" //procedure
            else if(lhsSynm=="-1" && rhs!= "_") {


                if(rhsSynm == "variable"){ //procedure name
                    sqlTemp = "SELECT variable FROM modifies WHERE procedureName = '"+lhs+"';";
                    Database::getModSql(followBuffer, sqlTemp);
                    if(followBuffer.empty()){
                        return false;
                    }else{
                        return true;
                    }
                }
            }
            else if(lhsSynm == "call" ){
//                        extract the procedure name being called
                sqlTemp = "SELECT procedureName FROM modifies;";
                Database::getModSql(selectBuffer, sqlTemp);
                for(string s:selectBuffer){
                    sqlTemp = "SELECT calling FROM callstar WHERE procedureName  = '" + s + "';";
                    Database::getModSql(stmtStmtBuffer, sqlTemp);
                }
            }
            else if(lhsSynm == "procedure"){
                sqlTemp = "SELECT procedureName FROM modifies;";
                Database::getModSql(selectBuffer,sqlTemp);
                if(rhs == "_"){
                    sqlTemp = "SELECT procedureName FROM modifies;";
                    Database::getModSql(followBuffer, sqlTemp);
                    if(followBuffer.empty()){
                        return false;
                    }else{
                        return true;
                    }
                }
                else if (rhsSynm == "-1"){
                    cout << "                               ww        debug " <<rhs<<endl;
                    sqlTemp = "SELECT procedureName FROM modifies WHERE variable  = '" + rhs + "';";
                    Database::getModSql(followBuffer, sqlTemp);
                    if(followBuffer.empty()){
                        return false;
                    }
                    else{
                        return true;
                    };

                }
                else if (rhsSynm == "variable"){
                    sqlTemp = "SELECT variable FROM modifies;";
                    Database::getModSql(followBuffer, sqlTemp);
                    if(followBuffer.empty()){
                        return false;
                    }
                    else{
                        return true;
                    };
                }
            }

            if(rhs == "_"){
                sqlTemp = "SELECT variable FROM modifies WHERE stmtNum  = '" + lhs + "';";
                Database::getModSql(followBuffer, sqlTemp);
                if(followBuffer.empty()){
                    return false;
                }
            }
            else if(rhs == "variable"){
                sqlTemp = "SELECT variable FROM modifies WHERE stmtNum  = '" + lhs + "';";
                Database::getModSql(followBuffer, sqlTemp);
                if(followBuffer.empty()){
                    return false;
                }
            }
            else if(rhsSynm == "-1" && lhsSynm != "procedure"){ //procedure name

                sqlTemp = "SELECT variable FROM modifies WHERE procedureName  = '" + lhs + "';";
                Database::getModSql(followBuffer, sqlTemp);
                if(followBuffer.empty()){
                    return false;
                }
            }



            Database::insertRelation("Modifies",lhs,rhs,"T");

        }
        return true;

    }


}