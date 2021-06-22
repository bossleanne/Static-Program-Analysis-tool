//
// Created by Leanne on 2/3/21.
//

#include "Follow.h"

bool Follow::follows(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs) {
    //query
    string sqlTemp = "";
    //three type of query from SQL _,synm
    string tmpSynm="";
    vector<string> constStmtBuffer;
    vector<string> varStmtBuffer;
    vector<string> stmtStmtBuffer;

    //follow
    vector<string> selectBuffer;
    vector<string> numBuffer; //_,num after compairinga and join back to Follow
    vector<string> varInRelationBuffer;
    vector<string> varInRelationExist;
    vector<string> constInRelationBuffer;
    vector<string> numBufferB;
    vector<string> buffer;
    bool exist=true;

    //_?
    if( lhs == "_" ){
        //_,_
        sqlTemp = "SELECT stmtBefore FROM follows;";
        Database::getFollow(followBuffer,sqlTemp);

        // _,_
        if(rhs == "_"){
            sqlTemp = "SELECT stmtAfter FROM follows;";
            Database::getFollow(followBuffer,sqlTemp);
            if(followBuffer.empty()){
                return false;
            }
        }
            //_,num
        else if(utils::isDigit(rhs)){
            sqlTemp = "SELECT stmtAfter FROM follows;";
            Database::getFollow(selectBuffer,sqlTemp);
            if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
                exist = true;
                followBuffer.clear();
                followBuffer.push_back(Database::getFollowLhs(rhs));
            }else{
                exist = false;
                followBuffer.clear();
                return false;
            }

            if(exist){
                for(string s:selectBuffer){
                    if(stoi(s)<stoi(rhs)){
                        followBuffer.push_back(Database::getFollowLhs(s));
                    }
                }
            }
            selectBuffer.clear();
        }
        //_,synm
        else if(rhs!= "_" && !utils::isDigit(rhs)){
            tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
            if(tmpSynm == "stmt"){
                followBuffer.clear();
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(followBuffer,sqlTemp);
            }
            else if(tmpSynm == "variable"){

                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(selectBuffer,sqlTemp);

                for(string var:varStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), var) != selectBuffer.end()){
                        followBuffer.push_back(var);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                varStmtBuffer.clear();

            }else if(tmpSynm == "constant"){

                Database::getConstantStmt(constStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(selectBuffer,sqlTemp);

                for(string con:constStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), con) != selectBuffer.end()){
                        followBuffer.push_back(con);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                constStmtBuffer.clear();
            }
            else{
                followBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(selectBuffer,sqlTemp);

                for(string s:stmtStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                        followBuffer.push_back(s);
                    }else{
                        continue;
                    }
                }
                if(followBuffer.empty()){
                    return false;
                }
                selectBuffer.clear();
                stmtStmtBuffer.clear();
            }
        }
        Database::insertRelation("Follows",lhs,rhs,"T");
    }
        //num,?
    else if(utils::isDigit(lhs)){

        selectBuffer.clear();
        followBuffer.clear();
        constStmtBuffer.clear();
        numBuffer.clear();
        varStmtBuffer.clear();
        stmtStmtBuffer.clear();


        //chcek if num exist in the data
        sqlTemp = "SELECT stmtBefore FROM follows;";
        Database::getFollow(selectBuffer,sqlTemp);
        if (std::find(selectBuffer.begin(), selectBuffer.end(), lhs) != selectBuffer.end()){
            exist = true;
        }
        else{
            exist = false;
            return false;
        }

        if(exist){
            //num,_
            if(rhs == "_"){
                cout << "               pppp        p    "<<endl;
                sqlTemp = "SELECT stmtAfter FROM follows where stmtBefore = '"+lhs+"';";
                Database::getFollow(selectBuffer,sqlTemp);
                if(selectBuffer.empty()){
                    return false;
                }
            }
                //num,num
            else if(utils::isDigit(rhs)){

                if(stoi(lhs) == stoi(rhs) || stoi(rhs) < stoi(lhs)){
                    exist = false;
                    return false;
                }

                //check if left and right exist in dataset
                selectBuffer.clear();
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(selectBuffer,sqlTemp);
                if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
                    exist = true;
                }else{
                    followBuffer.clear();
                    exist = false;
                    return false;
                }

                if (exist) {
                    //check if the stmt is right
                    sqlTemp = "SELECT stmtBefore FROM follows;";
                    Database::getFollow(selectBuffer,sqlTemp);
                    for(string snum :selectBuffer){
                        if(snum > lhs){
                            numBuffer.push_back(snum);
                        }
                    }
                    selectBuffer.clear();
//                    //get num lhs in follow
                    followBuffer = numBuffer;
                    sqlTemp = "SELECT stmtAfter FROM follows;";
                    Database::getFollow(selectBuffer, sqlTemp);
                    for (string snum :selectBuffer) {
                        if (snum < rhs) {
                            followBuffer.push_back(snum);
                        }
                    }
                    selectBuffer.clear();

                }
            }
                //num,synm
            else{
                tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types


                if(tmpSynm == "stmt"){
                    Database::getStmt(selectBuffer);
                    for(string stmt:selectBuffer){
                        if(stmt == Database::getFollowRhs(lhs)){
                            followBuffer.push_back(stmt);
                        }
                    }
                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                }
                else if(tmpSynm == "variable"){
                    Database::getVariableStmt(varStmtBuffer);
                    for(string var:varStmtBuffer){
                        if(Database::getFollowLhs(var) == rhs){
                            followBuffer.push_back(Database::getFollowLhs(var));
                        }

                    }
                    selectBuffer.clear();
                    varStmtBuffer.clear();

                }else if(tmpSynm == "constant"){
                    Database::getConstantStmt(constStmtBuffer);
                    sqlTemp = "SELECT stmtAfter FROM follows;";
                    Database::getFollow(selectBuffer,sqlTemp);

                    for(string var:varStmtBuffer){
                        if (std::find(selectBuffer.begin(), selectBuffer.end(), var) != selectBuffer.end()){
                            followBuffer.push_back(var);
                        }else{
                            continue;
                        }
                    }
                    selectBuffer.clear();
                    varStmtBuffer.clear();
                }
                else{
                    selectBuffer.clear();
                    Database::getStmtType(selectBuffer,tmpSynm);
                    for(string stmt:selectBuffer){
                        if(stmt == Database::getFollowRhs(lhs)){
                            followBuffer.push_back(stmt);
                        }
                    }
                    if(followBuffer.empty()){
                        return false;
                    }
                    for(string s:followBuffer){
                        cout << "                                                     "<<s<<"  "<<lhs<<endl;
                    }
                    selectBuffer.clear();
                    varStmtBuffer.clear();
                }
            }
        }
        Database::insertRelation("Follows",lhs,rhs,"T");
    }
    //synm,?
    else if(lhs!= "_" && !utils::isDigit(lhs)){

        //get synm from the table
        tmpSynm = Query::getSynm(synonyms,lhs); // get the raw synm type
        if(tmpSynm == "stmt"){
            followBuffer.clear();
            sqlTemp = "SELECT stmtBefore FROM follows;";
            Database::getFollow(followBuffer,sqlTemp);
            if(followBuffer.empty()){
                return false;
            }
        }
        else if(tmpSynm == "variable"){
            Database::getVariableStmt(varStmtBuffer);
            sqlTemp = "SELECT stmtBefore FROM follows;";
            Database::getFollow(selectBuffer,sqlTemp);
            for(string stmt:varStmtBuffer){
                if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()){
                    followBuffer.push_back(stmt);
                }else{
                    continue;
                }
            }
            if(followBuffer.empty()){
                return false;
            }
            selectBuffer.clear();
            varStmtBuffer.clear();
        }
        else if(tmpSynm == "constant"){
            Database::getConstantStmt(constStmtBuffer);
            sqlTemp = "SELECT stmtBefore FROM follows;";
            Database::getFollow(selectBuffer,sqlTemp);
            for(string stmt:constStmtBuffer){
                if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()){
                    followBuffer.push_back(stmt);
                }else{
                    continue;
                }
            }
            if(followBuffer.empty()){
                return false;
            }
            selectBuffer.clear();
            constStmtBuffer.clear();
        }
        else{
            stmtStmtBuffer.clear();
            Database::getStmtType(stmtStmtBuffer,tmpSynm);
            sqlTemp = "SELECT stmtBefore FROM follows;";
            Database::getFollow(selectBuffer,sqlTemp);
            for(string stmt:stmtStmtBuffer){
                if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()){
                    followBuffer.push_back(stmt);
                }else{
                    continue;
                }
            }
            if(followBuffer.empty()){
                return false;
            }
            selectBuffer.clear();
            stmtStmtBuffer.clear();
        }

        //synm,_
        if(rhs == "_"){
            selectBuffer.clear();
            selectBuffer = followBuffer;
            followBuffer.clear();
            stmtStmtBuffer.clear();
            for(string s:selectBuffer){
                sqlTemp = "SELECT stmtAfter FROM follows WHERE stmtBefore = '"+ s +"';";
                Database::getFollow(stmtStmtBuffer,sqlTemp);
                if(!stmtStmtBuffer.empty()){
                    followBuffer.push_back(s);
                }else{
                    return false;
                }
            }
//            for(string s:followBuffer){
//                cout << "                                " <<s<<endl;
//            }
//
//            if(followBuffer.empty()){
//                return false;
//            }
            Database::insertRelation("Follows",lhs,rhs,"T");
        }
        //synm,num
        else if(utils::isDigit(rhs)) {
            selectBuffer.clear();
            selectBuffer = followBuffer;
            followBuffer.clear();
            for(string s:selectBuffer){
                if(Database::getFollowRhs(s) == rhs){
                    followBuffer.push_back(s);
                }
            }
            if(followBuffer.empty()){
                return false;
            }else{
                Database::insertRelation("Follows",lhs,rhs,"T");
            }

            selectBuffer.clear();
        }
        //synm,synm
        else{
            tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
            if(rhs==lhs){
                followBuffer.clear();
                return false;
            }
            else if(tmpSynm == "stmt"){ //stmt
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(followBuffer,sqlTemp);
            }

            else if(tmpSynm == "variable"){
                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(selectBuffer,sqlTemp);

                for(string s:varStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                        buffer.push_back(s);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                selectBuffer = followBuffer;
                followBuffer.clear();
                for(string stmt:buffer){ //1st synm
                    for(string s:selectBuffer){
                        Database::getIsFollow(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                varStmtBuffer.clear();

            }else if(tmpSynm == "constant"){
                Database::getConstantStmt(constStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(selectBuffer,sqlTemp);

                for(string s:constStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                        buffer.push_back(s);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                selectBuffer = followBuffer;
                followBuffer.clear();
                for(string stmt:buffer){ //1st synm
                    for(string s:selectBuffer){
                        Database::getIsFollow(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                constStmtBuffer.clear();
            }
            else{
                stmtStmtBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT stmtAfter FROM follows;";
                Database::getFollow(selectBuffer,sqlTemp);

                for(string s:stmtStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                        buffer.push_back(s);
                    }else{
                        continue;
                    }
                }
                //buffer has all rhs synm stmt number
                //select has all lhs synm stmt number
                selectBuffer.clear();
                selectBuffer = followBuffer;
                followBuffer.clear();
                for(string stmt:buffer){ //1st synm
                    for(string s:selectBuffer){
                        if(stmt == Database::getFollowRhs(s)){
                            for(int i = 0; i < select.size(); i++)
                            {
                                //check i is stmt, v, c select the stmts
                                if(rhs == select[i].first){
                                    followBuffer.push_back(stmt);
                                }else if(lhs == select[i].first){
                                    followBuffer.push_back(s);
                                }
                                else if (rhs != select[i].first && lhs != select[i].first){
                                    followBuffer.push_back(s);
                                    followBuffer.push_back(stmt);
                                }
                            }

                        }
                    }
                }
                if(followBuffer.empty()){
                    return false;
                }
                selectBuffer.clear();
                stmtStmtBuffer.clear();
            }
            Database::insertRelation("Follows",lhs,rhs,"T");
            return true;
        }
    }
//    Database::insertRelation("Follows",lhs,rhs,"T");
    return true;
}


bool Follow::followstar(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs) {
    //query
    string sqlTemp = "";
    //three type of query from SQL _,synm
    string tmpSynm="";
    vector<string> constStmtBuffer;
    vector<string> varStmtBuffer;
    vector<string> stmtStmtBuffer;

    //follow
    vector<string> selectBuffer;
    vector<string> numBuffer; //_,num after compairinga and join back to Follow
    vector<string> varInRelationBuffer;
    vector<string> varInRelationExist;
    vector<string> constInRelationBuffer;
    vector<string> numBufferB;
    vector<string> buffer;
    bool exist=true;
    //_?
    if( lhs == "_" ){
        //_,_
        sqlTemp = "SELECT stmtBefore FROM followstar;";
        Database::getFollowStar(followBuffer,sqlTemp);

        // _,_
        if(rhs == "_"){
            sqlTemp = "SELECT stmtAfter FROM followstar;";
            Database::getFollowStar(followBuffer,sqlTemp);
            if(followBuffer.empty()){
                cout << "                            "<<endl;
                return false;
            }
        }
            //_,num
        else if(utils::isDigit(rhs)){
            followBuffer.clear();
            sqlTemp = "SELECT stmtBefore FROM followstar WHERE stmtAfter = '"+rhs+"';";
            Database::getFollowStar(selectBuffer,sqlTemp);
            if(!selectBuffer.empty()){
                followBuffer = selectBuffer;
            }
            selectBuffer.clear();
        }
            //_,synm
        else if(rhs!= "_" && !utils::isDigit(rhs)){
            tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
            if(tmpSynm == "stmt"){
                followBuffer.clear();
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(followBuffer,sqlTemp);
            }
            else if(tmpSynm == "variable"){
                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);

                for(string var:varStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), var) != selectBuffer.end()){
                        followBuffer.push_back(var);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                varStmtBuffer.clear();

            }else if(tmpSynm == "constant"){
                Database::getConstantStmt(constStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);

                for(string con:constStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), con) != selectBuffer.end()){
                        followBuffer.push_back(con);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                varStmtBuffer.clear();
            }
            else{
                followBuffer.clear();
                stmtStmtBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);
                for(string s:stmtStmtBuffer){ // all r stmt
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                        followBuffer.push_back(s);
                    }else{
                        continue;
                    }
                }
                if(followBuffer.empty()){
                    return false;
                }
                selectBuffer.clear();
                stmtStmtBuffer.clear();
            }
        }
        Database::insertRelation("Followstar",lhs,rhs,"T");
    }
    //num,?
    else if(utils::isDigit(lhs)){
        selectBuffer.clear();
        followBuffer.clear();
        constStmtBuffer.clear();
        numBuffer.clear();
        varStmtBuffer.clear();
        stmtStmtBuffer.clear();


        //chcek if num exist in the data
        sqlTemp = "SELECT stmtBefore FROM followstar;";
        Database::getFollowStar(selectBuffer,sqlTemp);
        if (std::find(selectBuffer.begin(), selectBuffer.end(), lhs) != selectBuffer.end()){
            exist = true;
        }
        else{
            exist = false;
            return false;
        }

        if(exist){
            //num,_
            selectBuffer.clear();
            if(rhs == "_"){
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);
                for(string s:selectBuffer){
                    if(stoi(s)>stoi(lhs)){
                        followBuffer.push_back(s);
                    }
                }
            }
                //num,num
            else if(utils::isDigit(rhs)){
                if(stoi(lhs) == stoi(rhs) || stoi(rhs) < stoi(lhs)){
                    exist = false;
                    return false;
                }
                //check if left and right exist in dataset
                selectBuffer.clear();
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);

                if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
                    exist = true;
                }else{
                    followBuffer.clear();
                    exist = false;
                    return false;
                }

                if (exist) {
//                    check if the stmt is right
                    followBuffer.clear();
                    //get all the follower(num,)
                    sqlTemp = "SELECT stmtAfter FROM followstar WHERE stmtBefore = '"+lhs+"';";
                    Database::getFollowStar(followBuffer,sqlTemp);

                    //return all follow(,num) relationship
                    if (std::find(followBuffer.begin(), followBuffer.end(), rhs) != followBuffer.end()){
                        sqlTemp = "SELECT stmtBefore FROM followstar WHERE stmtAfter = '"+rhs+"';";
                        Database::getFollowStar(followBuffer,sqlTemp);
                    }else{
                        followBuffer.clear();
                        return false;
                    }
                    selectBuffer.clear();

                }
            }
                //num,synm
            else{
                tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types


                if(tmpSynm == "stmt"){
                    Database::getStmt(selectBuffer);
                    for(string stmt:selectBuffer){
                        if(stmt == Database::getFollowRhsStar(lhs)){
                            followBuffer.push_back(stmt);
                        }
                    }
                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                }
                else if(tmpSynm == "variable"){
                    Database::getVariableStmt(varStmtBuffer);
                    for(string var:varStmtBuffer){
                        if(Database::getFollowLhsStar(var) == rhs){
                            followBuffer.push_back(Database::getFollowLhsStar(var));
                        }

                    }
                    selectBuffer.clear();
                    varStmtBuffer.clear();

                }else if(tmpSynm == "constant"){
                    Database::getConstantStmt(constStmtBuffer);
                    sqlTemp = "SELECT stmtAfter FROM followstar;";
                    Database::getFollowStar(selectBuffer,sqlTemp);

                    for(string con:constStmtBuffer){
                        if (std::find(selectBuffer.begin(), selectBuffer.end(), con) != selectBuffer.end()){
                            followBuffer.push_back(con);
                        }else{
                            continue;
                        }
                    }
                    selectBuffer.clear();
                    varStmtBuffer.clear();
                }
                else{
                    followBuffer.clear();
                    selectBuffer.clear();
                    Database::getStmtType(selectBuffer,tmpSynm);
                    for(string stmt:selectBuffer){
                        if(stmt == Database::getFollowRhsStar(lhs)){
                            followBuffer.push_back(stmt);
                        }
                    }
                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                    varStmtBuffer.clear();
                }
            }
        }
    }
    //synm?
    else if(lhs!= "_" && !utils::isDigit(lhs)){
        //get synm from the table
        tmpSynm = Query::getSynm(synonyms,lhs); // get the raw synm type
        if(tmpSynm == "stmt"){
            followBuffer.clear();
            sqlTemp = "SELECT stmtBefore FROM followstar;";
            Database::getFollowStar(followBuffer,sqlTemp);
        }
        else if(tmpSynm == "variable"){
            Database::getVariableStmt(varStmtBuffer);
            sqlTemp = "SELECT stmtBefore FROM followstar;";
            Database::getFollowStar(selectBuffer,sqlTemp);
            for(string stmt:varStmtBuffer){
                if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()){
                    followBuffer.push_back(stmt);
                }else{
                    continue;
                }
            }
            if(followBuffer.empty()){
                return false;
            }
            selectBuffer.clear();
            varStmtBuffer.clear();
        }
        else if(tmpSynm == "constant"){
            Database::getConstantStmt(constStmtBuffer);
            sqlTemp = "SELECT stmtBefore FROM followstar;";
            Database::getFollow(selectBuffer,sqlTemp);
            for(string stmt:constStmtBuffer){
                if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()){
                    followBuffer.push_back(stmt);
                }else{
                    continue;
                }
            }
            if(followBuffer.empty()){
                return false;
            }
            selectBuffer.clear();
            constStmtBuffer.clear();
        }
        else{
            stmtStmtBuffer.clear();
            Database::getStmtType(stmtStmtBuffer,tmpSynm);
            sqlTemp = "SELECT stmtBefore FROM followstar;";
            Database::getFollowStar(selectBuffer,sqlTemp);
            for(string stmt:stmtStmtBuffer){
                if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()){
                    followBuffer.push_back(stmt);
                }else{
                    continue;
                }
            }
            if(followBuffer.empty()){
                return false;
            }
            selectBuffer.clear();
            stmtStmtBuffer.clear();
        }
        //synm,_
        if(rhs == "_"){
            selectBuffer.clear();
            selectBuffer = followBuffer;
            followBuffer.clear();
            stmtStmtBuffer.clear();
            for(string s:selectBuffer){
                sqlTemp = "SELECT stmtAfter FROM followstar WHERE stmtBefore = '"+ s +"';";
                Database::getFollowStar(stmtStmtBuffer,sqlTemp);
                if(!stmtStmtBuffer.empty()){
                    followBuffer.push_back(s);
                }else{
                    return false;
                }
            }
            Database::insertRelation("Followstar",lhs,rhs,"T");
        }
            //synm,num
        else if(utils::isDigit(rhs)) {
            selectBuffer.clear();
            selectBuffer = followBuffer;
            followBuffer.clear();
            for(string s:selectBuffer){
                if(Database::getFollowRhsStar(s) == rhs){
                    followBuffer.push_back(s);
                }
            }
            if(followBuffer.empty()){
                return false;
            }else{
                Database::insertRelation("Followstar",lhs,rhs,"T");
            }

            selectBuffer.clear();
//            sqlTemp = "SELECT stmtAfter FROM followstar;";
//            Database::getFollow(selectBuffer,sqlTemp);
//            if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
//                exist = true;
//                followBuffer.clear();
//                followBuffer.push_back(Database::getFollowLhsStar(rhs));
//            }else{
//                exist = false;
//                followBuffer.clear();
//                return false;
//            }
//
//            if(exist){
//                for(string s:selectBuffer){
//                    if(stoi(s)<stoi(rhs)){
//                        Database::getIsFollowStar(followBuffer,s,rhs);
//                    }
//                }
//            }
//            selectBuffer.clear();
        }
            //synm,synm
        else{
            tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
            if(rhs==lhs){
                followBuffer.clear();
                return false;
            }
            else if(tmpSynm == "stmt"){ //stmt
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(followBuffer,sqlTemp);
            }

            else if(tmpSynm == "variable"){
                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);

                for(string s:varStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                        buffer.push_back(s);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                selectBuffer = followBuffer;
                followBuffer.clear();
                for(string stmt:buffer){ //1st synm
                    for(string s:selectBuffer){
                        Database::getIsFollowStar(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                varStmtBuffer.clear();

            }else if(tmpSynm == "constant"){
                Database::getConstantStmt(constStmtBuffer);
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);

                for(string s:constStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                        buffer.push_back(s);
                    }else{
                        continue;
                    }
                }
                selectBuffer.clear();
                selectBuffer = followBuffer;
                followBuffer.clear();
                for(string stmt:buffer){ //1st synm
                    for(string s:selectBuffer){
                        Database::getIsFollowStar(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                constStmtBuffer.clear();
            }
            else{
                buffer.clear();
                stmtStmtBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT stmtAfter FROM followstar;";
                Database::getFollowStar(selectBuffer,sqlTemp);

                for(string s:stmtStmtBuffer){
                    if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
//                        cout << "       rs " << s <<"                "<<endl;
                        buffer.push_back(s);
                    }else{
                        continue;
                    }
                }

                selectBuffer.clear();
                stmtStmtBuffer.clear();
                selectBuffer = followBuffer;
                followBuffer.clear();
                //select -> all lhs stmt
                //buffer -> all rhs stmt
                for(string ls:selectBuffer){
                    for(string rs:buffer){
                        sqlTemp = "SELECT * FROM followstar WHERE stmtBefore = '"+ ls +"' AND stmtAfter = '"+ rs +"';";
                        if(Database::checkStmt(ls,rs,sqlTemp) ) {
                            for(int i = 0; i < select.size(); i++)
                            {
                                //check i is stmt, v, c select the stmts
                                if(rhs == select[i].first){
                                    followBuffer.push_back(rs);
                                }else if(lhs == select[i].first){
                                    followBuffer.push_back(ls);
                                }
                                else if (rhs != select[i].first && lhs != select[i].first){
                                    followBuffer.push_back(ls);
                                    followBuffer.push_back(rs);
                                }
                            }
                        }
                    }
                }


                selectBuffer.clear();
                stmtStmtBuffer.clear();
            }
        }
    }
    return true;

}