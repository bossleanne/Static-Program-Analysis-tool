//
// Created by Leanne on 31/3/21.
//

#include "Use.h"

//bool Use::useRelation(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs){
//    //query
//    string sqlTemp = "";
//    //three type of query from SQL _,synm
//    string tmpSynm="";
//    vector<string> constStmtBuffer;
//    vector<string> varStmtBuffer;
//    vector<string> stmtStmtBuffer;
//    vector<string> procedureBuffer;
//
//    //use relaitionship
//    vector<string> selectBuffer;
//    vector<string> numBuffer; //_,num after compairinga and join back to Follow
//    vector<string> varInRelationBuffer;
//    vector<string> varInRelationExist;
//    vector<string> constInRelationBuffer;
//    vector<string> numBufferB;
//    vector<string> buffer;
//    bool exist=true;
//    bool isParentStmt = false;
//    bool isVar=false;
//    bool result = true;
//    string leftTmp = "";
//    leftTmp = Query::getSynm(synonyms,lhs);
//    vector<string> tmpLoop;
//
//    string lhsSynm = Query::getSynm(synonyms,lhs);
//    string rhsSynm = Query::getSynm(synonyms,rhs);
////    bool varCheck = false;
//
//    isVar = Query::isUseInRelation(select);
//
//
//    //_?
//    if( lhs == "_" ){
//        // _,_
//        if(rhs == "_"){
//            return false;
//        }
//            //_,num
//        else if(utils::isDigit(rhs)){
//            return false;
//        }
//            //_,synm
//        else if(rhs!= "_" && !utils::isDigit(rhs)) {
//            tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
//
//            //if there are variable names only
//            if(tmpSynm=="-1"){
//                //extract the varible stmt from Use table
//                if(isVar){
//                    sqlTemp = "SELECT variable FROM uses;";
//                    Database::getUsesSql(followBuffer,sqlTemp);
//                }
//                else{
//                    sqlTemp = "SELECT stmtNum FROM uses WHERE variable = '" + rhs+"';";
//                    Database::getUsesSql(followBuffer,sqlTemp);
//                }
//                if(followBuffer.empty()){
//                    return false;
//                }
//            }else{
//                return false;
//            }
//        }
//    }
//
//    //num,?
//    else if(utils::isDigit(lhs)){
//
//        stmtStmtBuffer.clear();
//
//        //chcek if num exist in the data
//        sqlTemp = "SELECT stmtNum FROM uses;";
//        Database::getUsesSql(stmtStmtBuffer,sqlTemp);
//        if (std::find(stmtStmtBuffer.begin(), stmtStmtBuffer.end(), lhs) != stmtStmtBuffer.end()){
//            exist = true;
//            //check if it's a parents stmt;
//            //check if the number is a parents stmt:
//            selectBuffer.clear();
//            sqlTemp = "SELECT child FROM parents WHERE parent = '" + lhs +"';";
//            Database::getUsesSql(selectBuffer,sqlTemp);
//            if(!selectBuffer.empty()){
//                isParentStmt = true;
//            }
//        }
//        else{
//            exist = false;
//            return false;
//        }
//
//        if(exist){
//            //num,_
//            if(rhs == "_"){
//                sqlTemp = "SELECT variable FROM uses WHERE stmtNum  = '" + lhs + "';";
//                Database::getUsesSql(followBuffer, sqlTemp);
//                if(followBuffer.empty()){
//                    return false;
//                }
//                Database::insertRelation("uses",lhs,rhs,"T");
////                return false;
//            }
//                //num,num
//            else if(utils::isDigit(rhs)){
//                return false;
//            }
//                //num,synm
//            else{
//                tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
//                if(isParentStmt){
////                    cout << "                YES                    "<<lhs<<endl;
//                    selectBuffer.empty();
//                    sqlTemp = "SELECT child FROM parents WHERE parent in (SELECT stmtNum FROM statements WHERE stmtType = '"+ tmpSynm +"');"; // return all child stmt
//                    Database::getUsesSql(selectBuffer,sqlTemp);
//                    selectBuffer.push_back(lhs);
//                    //selectBuffer stored stmt line from parent
//                    for(string p:selectBuffer) {
//                        //multi procedure
//                        if (tmpSynm == "variable") {
//                            sqlTemp = "SELECT variable FROM uses WHERE stmtNum  = '" + p + "';";
//                            Database::getUsesSql(followBuffer, sqlTemp);
//                        } else if(tmpSynm == "call"){
//                            return false;
//                        }
//                    }
//                }else{
//                    //single procedure
//                    followBuffer.clear();
//                    if(tmpSynm == "variable"){
//                        sqlTemp = "SELECT variable FROM uses WHERE stmtNum  = '" + lhs+"';";
//                        Database::getUsesSql(followBuffer,sqlTemp);
//                    }else if(tmpSynm == "call"){
//                        return false;
//                    }
//                    else{
//                        return false;
//                    }
//                }
//                Database::insertRelation("uses",lhs,rhs,"T");
//            }
//        }
//    }
//
//        //synm,?
//    else if(lhs!= "_" && !utils::isDigit(lhs)) {
//        //check what's the possible synm
////        tmpSynm = Query::getSynm(synonyms,lhs;
//        //synm,synm
//        if (lhsSynm == "-1" && rhsSynm == "variable") {//procedure name
//            sqlTemp = "SELECT variableName FROM variables WHERE procedureName = '" + lhs + "';";
//            Database::getUsesSql(followBuffer, sqlTemp);//get all variables in procedure
//            if(followBuffer.empty()){
//                return false;
//            }else{
//                Database::insertRelation("uses",lhs,rhs,"T");
//                return true;
//            }
//        }
//        else if (rhsSynm == "-1" && rhs!= "_") {//rhs is the variable
//
//            if (lhsSynm == "procedure" || lhsSynm == "call") {
//                sqlTemp = "SELECT DISTINCT procedureName FROM variables WHERE variableName = '" + rhs + "';";
//                Database::getUsesSql(followBuffer, sqlTemp);
//                if (followBuffer.empty()) {
//                    return false;
//                }
//            } else if (lhsSynm == "print") {
//                Database::getStmtType(stmtStmtBuffer, lhsSynm);
//                sqlTemp = "SELECT stmtNum FROM uses WHERE variable == '" + rhs + "';";
//                Database::getUsesSql(selectBuffer, sqlTemp);
//                for (string stmt:stmtStmtBuffer) {
//                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
//                        followBuffer.push_back(stmt);
//                    } else {
//                        continue;
//                    }
//                }
//                if (followBuffer.empty()) {
//                    return false;
//                }
//            } else if (lhsSynm == "stmt") {
//                stmtStmtBuffer.clear();
//                selectBuffer.clear();
//                Database::getStmt(stmtStmtBuffer);
//                sqlTemp = "SELECT stmtNum FROM uses WHERE variable == '" + rhs + "';";
//                Database::getUsesSql(selectBuffer, sqlTemp);
//                for (string stmt:stmtStmtBuffer) {
//                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
//                        followBuffer.push_back(stmt);
//                    } else {
//                        continue;
//                    }
//                }
//                if (followBuffer.empty()) {
//                    return false;
//                }
//            } else if (tmpSynm == "while" or tmpSynm == "if") {
//                Database::getStmtType(stmtStmtBuffer, tmpSynm);
//                sqlTemp =
//                        "SELECT child FROM parents WHERE parent in (SELECT stmtNum FROM statements WHERE stmtType = '" +
//                        tmpSynm + "');"; // return all child stmt
//                Database::getUsesSql(stmtStmtBuffer, sqlTemp);
//                sqlTemp = "SELECT stmtNum FROM uses;";
//                Database::getUsesSql(selectBuffer, sqlTemp);
//                for (string stmt:stmtStmtBuffer) {
//                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
//                        followBuffer.push_back(stmt);
//                    } else {
//                        continue;
//                    }
//                }
//                if (followBuffer.empty()) {
//                    return false;
//                }
//            } else if (tmpSynm == "variable") {
//                sqlTemp = "SELECT variable FROM uses WHERE variable  = '" + rhs + "';";
//                Database::getUsesSql(followBuffer, sqlTemp);
//                if (followBuffer.empty()) {
//                    return false;
//                }
//            } else {
//                Database::insertRelation("uses",lhs,rhs,"T");
//                return false;
//            }
//        }
//        else if (rhsSynm == "variable") {
//            if (lhsSynm == "procedure" || lhsSynm == "call") {
//                sqlTemp = "SELECT variable FROM uses";
//                Database::getUsesSql(followBuffer, sqlTemp);
//                if (followBuffer.empty()) {
//                    return false;
//                } else {
//                    Database::insertRelation("uses",lhs,rhs,"T");
//                    return true;
//                }
//            } else if (lhsSynm == "while" || lhsSynm == "if") {
//                selectBuffer.clear();
//                stmtStmtBuffer.clear();
//                Database::getStmtType(stmtStmtBuffer, tmpSynm);
//                sqlTemp =
//                        "SELECT child FROM parents WHERE parent in (SELECT stmtNum FROM statements WHERE stmtType = '" +
//                        tmpSynm + "');"; // return all child stmt
//                Database::getUsesSql(stmtStmtBuffer, sqlTemp);
//                sqlTemp = "SELECT stmtNum FROM uses;";
//                Database::getUsesSql(selectBuffer, sqlTemp);
//                for (string stmt:stmtStmtBuffer) {
//                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
//                        sqlTemp = "SELECT variable FROM uses WHERE variable = '" + stmt + "';";
//                        Database::getUsesSql(selectBuffer, sqlTemp);
//                        for (string s:selectBuffer)
//                            followBuffer.push_back(s);
//                    } else {
//                        continue;
//                    }
//                }
//                if (followBuffer.empty()) {
//                    return false;
//                }
//            } else if (lhsSynm == "print") {
//                selectBuffer.clear();
//                stmtStmtBuffer.clear();
//                Database::getStmtType(stmtStmtBuffer, tmpSynm);
//                sqlTemp = "SELECT stmtNum FROM uses;";
//                Database::getUsesSql(selectBuffer, sqlTemp);
//                for (string stmt:stmtStmtBuffer) {
//                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
////                        followBuffer.push_back(stmt);
//                        sqlTemp = "SELECT variable FROM uses WHERE variable = '" + stmt + "';";
//                        Database::getUsesSql(selectBuffer, sqlTemp);
//                        for (string s:selectBuffer)
//                            followBuffer.push_back(s);
//                    } else {
//                        continue;
//                    }
//                }
//                if (followBuffer.empty()) {
//                    return false;
//                }
//            } else if (lhsSynm == "stmt") {
//                for (int i = 0; i < select.size(); i++) {
//                    if (rhs == select[i].first) {
//                        sqlTemp = "SELECT variable FROM uses;";
//                        Database::getUsesSql(followBuffer, sqlTemp);//get all variables in procedure
//                        if (followBuffer.empty()) {
//                            return false;
//                        } else {
//                            Database::insertRelation("uses",lhs,rhs,"T");
//                            return true;
//                        }
//                    } else {
//                        sqlTemp = "SELECT stmtNum FROM uses;";
//                        Database::getUsesSql(followBuffer, sqlTemp);//get all variables in procedure
//                        if (followBuffer.empty()) {
//                            return false;
//                        } else {
//                            Database::insertRelation("uses",lhs,rhs,"T");
//                            return true;
//                        }
//                    }
//                }
//
//            }
//        }
//        else if (rhs== "_"){
//            cout << "                                                       debug " <<rhs<<endl;
//
//            if(lhsSynm == "stmt"){
//                sqlTemp = "SELECT stmtNum FROM uses";
//                Database::getUsesSql(followBuffer, sqlTemp);
//                if(followBuffer.empty()){
//                    return false;
//                }else{
//                    return true;
//                }
//            }
//            Database::insertRelation("uses",lhs,rhs,"T");
////            else{
////
////            }
//        }
//
//    }
//    return true;
//}
bool Use::useRelationship(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs){
    cout << "      debug                          "<<lhs<<" "<<rhs<<endl;

    //query
    string sqlTemp = "";
    //three type of query from SQL _,synm
    string tmpSynm="";
    vector<string> constStmtBuffer;
    vector<string> varStmtBuffer;
    vector<string> stmtStmtBuffer;
    vector<string> procedureBuffer;

    //use relaitionship
    vector<string> selectBuffer;
    vector<string> numBuffer; //_,num after compairinga and join back to Follow
    vector<string> varInRelationBuffer;
    vector<string> varInRelationExist;
    vector<string> constInRelationBuffer;
    vector<string> numBufferB;
    vector<string> buffer;
    bool exist=true;
    bool isParentStmt = false;
    bool isVar=false;
    bool result = true;
    string leftTmp = "";
    leftTmp = Query::getSynm(synonyms,lhs);
    vector<string> tmpLoop;

    string lhsSynm = Query::getSynm(synonyms,lhs);
    string rhsSynm = Query::getSynm(synonyms,rhs);

    vector<string> useVarBuffer;
    vector<string> useStmtBuffer;

    bool varCheck = false;
    for(int i = 0; i < select.size(); i++)
    {
        //check i is stmt, v, c select the stmts
        if(select[i].first == "variable") {
            varCheck = true;
        }
    }

    //_,?
    if( lhs == "_" ){
        //_,_
//        if(rhs == "_"){
//            return false;
//        }
        //_,"xx"
        if(rhsSynm=="-1" && rhs!= "_" && isVar){
            sqlTemp = "SELECT variable FROM uses WHERE variable = '"+ rhs +"';";
            Database::getUsesSql(followBuffer,sqlTemp);
        }
        else{
            //_,variable
            if(rhsSynm == "variable"){
                sqlTemp = "SELECT variable FROM uses;";
                Database::getUsesSql(followBuffer,sqlTemp);
            }
//            else{
//                return false;
//            }
        }
        Database::insertRelation("uses",lhs,rhs,"T");

    }

    //num,?
    else if(utils::isDigit(lhs)){
        stmtStmtBuffer.clear();
        selectBuffer.clear();
        //chcek if num exist in the data
        sqlTemp = "SELECT stmtNum FROM uses WHERE stmtNum = '"+ lhs+"';";
        Database::getUsesSql(stmtStmtBuffer,sqlTemp);
        if(!stmtStmtBuffer.empty()){
            sqlTemp = "SELECT child FROM parents WHERE parent = '" + lhs +"';";
            Database::getUsesSql(selectBuffer,sqlTemp);
            if(!selectBuffer.empty()){
                selectBuffer.push_back(lhs);
                isParentStmt = true;
            }
        }
        else{
            return false;
        }


        //num,synm -> need to check if theres parents
        if(isParentStmt){
            //selectBuffer stored stmt line from parent
            Database::insertRelation("uses",lhs,rhs,"T");
            for(string p:selectBuffer) {
                //multi procedure
                if(rhsSynm=="-1" && rhs!= "_") {
                    sqlTemp = "SELECT variable FROM uses WHERE variable = '" + rhs + "' AND stmtNum = '" + p + "';";
                    Database::getUsesSql(followBuffer, sqlTemp);
                }
                else if (rhsSynm == "variable") {
                    sqlTemp = "SELECT variable FROM uses WHERE stmtNum  = '" + p + "';";
                    Database::getUsesSql(followBuffer, sqlTemp);
                    for(string s:followBuffer){
                        cout << "                                       debug " << s<<endl;
                    }

                }
                else if(rhs == "_"){
                    sqlTemp = "SELECT variable FROM uses WHERE stmtNum  = '" + lhs + "';";
                    Database::getUsesSql(followBuffer, sqlTemp);
                    if(followBuffer.empty()){
                        return false;
                    }
                }
                else if(rhsSynm == "call" || "procedure"){
                    return false;
                }
            }
            Database::insertRelation("uses",lhs,rhs,"T");


        }
        else{
            if(rhsSynm=="-1" && rhs!= "_"){
                sqlTemp = "SELECT variable FROM uses WHERE variable = '"+ rhs +"' AND stmtNum = '"+lhs+"';";
                Database::getUsesSql(followBuffer,sqlTemp);
            }
            else{
                if(rhsSynm == "variable"){
                    sqlTemp = "SELECT variable FROM uses WHERE stmtNum  = '" + lhs + "';";
                    Database::getUsesSql(followBuffer,sqlTemp);
                }
            }
            Database::insertRelation("uses",lhs,rhs,"T");
        }


    }

    //synm,?
    //        //synm,?
    else if(lhs!= "_" && !utils::isDigit(lhs)) {
        //check what's the possible synm
//        tmpSynm = Query::getSynm(synonyms,lhs;
        //synm,synm
        if (lhsSynm == "-1" && rhsSynm == "variable" && rhs!= "_") {//procedure name
            sqlTemp = "SELECT variableName FROM variables WHERE procedureName = '" + lhs + "';";
            Database::getUsesSql(followBuffer, sqlTemp);//get all variables in procedure
            if(followBuffer.empty()){
                return false;
            }else{
                Database::insertRelation("uses",lhs,rhs,"T");
                return true;
            }
        }
        else if (rhsSynm == "-1" && rhs!= "_") {//rhs is the variable

            if (lhsSynm == "procedure" || lhsSynm == "call") {
                sqlTemp = "SELECT DISTINCT procedureName FROM variables WHERE variableName = '" + rhs + "';";
                Database::getUsesSql(followBuffer, sqlTemp);
                if (followBuffer.empty()) {
                    return false;
                }
            } else if (lhsSynm == "print") {
                Database::getStmtType(stmtStmtBuffer, lhsSynm);
                sqlTemp = "SELECT stmtNum FROM uses WHERE variable == '" + rhs + "';";
                Database::getUsesSql(selectBuffer, sqlTemp);
                for (string stmt:stmtStmtBuffer) {
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
                        followBuffer.push_back(stmt);
                    } else {
                        continue;
                    }
                }
                if (followBuffer.empty()) {
                    return false;
                }
            } else if (lhsSynm == "stmt") {
                stmtStmtBuffer.clear();
                selectBuffer.clear();
                Database::getStmt(stmtStmtBuffer);
                sqlTemp = "SELECT stmtNum FROM uses WHERE variable == '" + rhs + "';";
                Database::getUsesSql(selectBuffer, sqlTemp);
                for (string stmt:stmtStmtBuffer) {
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
                        followBuffer.push_back(stmt);
                    } else {
                        continue;
                    }
                }
                if (followBuffer.empty()) {
                    return false;
                }
            } else if (tmpSynm == "while" or tmpSynm == "if") {
                Database::getStmtType(stmtStmtBuffer, tmpSynm);
                sqlTemp =
                        "SELECT child FROM parents WHERE parent in (SELECT stmtNum FROM statements WHERE stmtType = '" +
                        tmpSynm + "');"; // return all child stmt
                Database::getUsesSql(stmtStmtBuffer, sqlTemp);
                sqlTemp = "SELECT stmtNum FROM uses;";
                Database::getUsesSql(selectBuffer, sqlTemp);
                for (string stmt:stmtStmtBuffer) {
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
                        followBuffer.push_back(stmt);
                    } else {
                        continue;
                    }
                }
                if (followBuffer.empty()) {
                    return false;
                }
            } else if (tmpSynm == "variable") {
                sqlTemp = "SELECT variable FROM uses WHERE variable  = '" + rhs + "';";
                Database::getUsesSql(followBuffer, sqlTemp);
                if (followBuffer.empty()) {
                    return false;
                }
            } else {
                Database::insertRelation("uses",lhs,rhs,"T");
                return false;
            }
        }
        else if (rhsSynm == "variable") {
            if (lhsSynm == "procedure" || lhsSynm == "call") {
                sqlTemp = "SELECT variable FROM uses";
                Database::getUsesSql(followBuffer, sqlTemp);
                if (followBuffer.empty()) {
                    return false;
                } else {
                    Database::insertRelation("uses",lhs,rhs,"T");
                    return true;
                }
            } else if (lhsSynm == "while" || lhsSynm == "if") {
                selectBuffer.clear();
                stmtStmtBuffer.clear();
                Database::getStmtType(stmtStmtBuffer, tmpSynm);
                sqlTemp =
                        "SELECT child FROM parents WHERE parent in (SELECT stmtNum FROM statements WHERE stmtType = '" +
                        tmpSynm + "');"; // return all child stmt
                Database::getUsesSql(stmtStmtBuffer, sqlTemp);
                sqlTemp = "SELECT stmtNum FROM uses;";
                Database::getUsesSql(selectBuffer, sqlTemp);
                for (string stmt:stmtStmtBuffer) {
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
                        sqlTemp = "SELECT variable FROM uses WHERE variable = '" + stmt + "';";
                        Database::getUsesSql(selectBuffer, sqlTemp);
                        for (string s:selectBuffer)
                            followBuffer.push_back(s);
                    } else {
                        continue;
                    }
                }
                if (followBuffer.empty()) {
                    return false;
                }
            } else if (lhsSynm == "print") {
                selectBuffer.clear();
                stmtStmtBuffer.clear();
                Database::getStmtType(stmtStmtBuffer, tmpSynm);
                sqlTemp = "SELECT stmtNum FROM uses;";
                Database::getUsesSql(selectBuffer, sqlTemp);
                for (string stmt:stmtStmtBuffer) {
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()) {
//                        followBuffer.push_back(stmt);
                        sqlTemp = "SELECT variable FROM uses WHERE variable = '" + stmt + "';";
                        Database::getUsesSql(selectBuffer, sqlTemp);
                        for (string s:selectBuffer)
                            followBuffer.push_back(s);
                    } else {
                        continue;
                    }
                }
                if (followBuffer.empty()) {
                    return false;
                }
            } else if (lhsSynm == "stmt") {
                for (int i = 0; i < select.size(); i++) {
                    if (rhs == select[i].first) {
                        sqlTemp = "SELECT variable FROM uses;";
                        Database::getUsesSql(followBuffer, sqlTemp);//get all variables in procedure
                        if (followBuffer.empty()) {
                            return false;
                        } else {
                            Database::insertRelation("uses",lhs,rhs,"T");
                            return true;
                        }
                    } else {
                        sqlTemp = "SELECT stmtNum FROM uses;";
                        Database::getUsesSql(followBuffer, sqlTemp);//get all variables in procedure
                        if (followBuffer.empty()) {
                            return false;
                        } else {
                            Database::insertRelation("uses",lhs,rhs,"T");
                            return true;
                        }
                    }
                }

            }
        }
        else if (rhs== "_"){
            cout << "                                                       debug " <<rhs<<endl;

            if(lhsSynm == "stmt"){
                sqlTemp = "SELECT stmtNum FROM uses";
                Database::getUsesSql(followBuffer, sqlTemp);
                if(followBuffer.empty()){
                    return false;
                }else{
                    return true;
                }
            }
            Database::insertRelation("uses",lhs,rhs,"T");
//            else{
//
//            }
        }

    }
    return true;
//    else if(lhs!= "_" && !utils::isDigit(lhs)){
    // only procedure and variable need parents/varName and rest just need stmt

    //synm,_
    //synm- procedure,variable_

    //stmt/read/print/while/if/,_


    //synm,num
    //synm- procedure,variable_
    //stmt/read/print/while/if/,_

    //synm,synm
    //synm- procedure | v
    //stmt/read/print/while/if/|v
//    }
//    return true;
}
