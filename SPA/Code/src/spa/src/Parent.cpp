//
// Created by Leanne on 2/3/21.
//

#include "Parent.h"

void Parent::parentsParse(string procedureName,vector<string> tokens){
    int i = 0;
    int stmtNum = 0;
    int scope_c = 0;
    stack<int> nestLevel;
    string s = "";
    int start = 0;
    vector <string> sons;
    vector <string> parents;
    pair<int,vector<int>> parent_son;

    int parent = 0;
    int ifparents = 0;
    stack<int> ifs;

    vector<int>scopeloop;
    vector<string> parentsHead;
    bool elseLoop = false;
    vector<string>buffer;
    string currentProcedure = "";
    currentProcedure = tokens.at(1);

    while(i < tokens.size()){
        if(currentProcedure != procedureName){
            cout << "                                       debug " << s<<endl;
        }
        s = tokens.at(i);
        if(s == ";") {
            stmtNum++;
            if(scope_c == 1){
                scopeloop.clear();

//                for(string s:parentsHead){
////                    cout << " s " << s<<endl;
//                    Database::getSon(sons,s);
//                    for(string son:sons){
//                        Database::getParentStarLR(buffer,s,son);
////                        cout << "dd  " <<buffer.size() << " p " << s << " s " <<son <<endl;
//                        if(buffer.empty()) {
//                            Database::insertParentStar(parentsHead.front(), procedureName, son);
//                        }else{
//                            buffer.clear();
//                        }
//                    }
//                }
//                sons.clear();
//                parentsHead.clear();
            }
            else if(scope_c>1){
                scopeloop.push_back(stmtNum);
            }
            if (parent != 0) {
                Database::insertParent(procedureName, to_string(parent), to_string(stmtNum));
            }
        }

        if(s == "if"){
            stmtNum++;
            if(parent!=0){
                Database::insertParent(procedureName,to_string(parent),to_string(stmtNum));
            }
            parent = stmtNum;
            ifparents = parent;
        }

        if(s == "while"){
            stmtNum++;
            if(parent!=0){
                Database::insertParent(procedureName,to_string(parent),to_string(stmtNum));
            }
            parent = stmtNum;

        }
        if(s == "else"){
            parent = ifparents;
        }
        //if there's a while or if
        if(s == "{"){
            scope_c++;
            nestLevel.push(scope_c);
            //check if:
            if(tokens.at(i-1) == "then" && stmtNum>0){
                parentsHead.push_back(to_string(stmtNum));
                ifs.push(stmtNum);

            }else if(tokens.at(i-1)!= "else" && stmtNum>0){
                parentsHead.push_back(to_string(stmtNum));
            }
        }

        //coming to the end of while or if
        if(s == "}"){
            if(i<tokens.size()-1 && tokens.at(i+1)== "else" ){
                parentsHead.push_back(to_string(ifs.top()));
                ifs.pop();
            }
            nestLevel.pop();
            scope_c--;
            if(scope_c == 1){
                parent = 0;
            }
        }

        i++;
    }


}

//void Parent::parentStarParse(string procedureName,vector<string> tokens){
//    string getStmtNumberSQL = "SELECT parent FROM parents WHERE statementNumber='" + stmtNo + "' AND procedureName = '" + procedureName + "';";
//    sqlite3_exec(dbConnection, getStmtNumberSQL.c_str(), callback, 0, &errorMessage);
//
//}

bool Parent::parents(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs){
    //query
    string sqlTemp = "";
    //three type of query from SQL _,synm
    string tmpSynm="";
    vector<string> constStmtBuffer;
    vector<string> varStmtBuffer;
    vector<string> stmtStmtBuffer;

    //parent
    vector<string> selectBuffer;
    vector<string> numBuffer; //_,num after comparing and join back to Follow
    vector<string> varInRelationBuffer;
    vector<string> varInRelationExist;
    vector<string> constInRelationBuffer;
    vector<string> numBufferB;
    vector<string> buffer;
    bool exist=true;

    //_?
    if( lhs == "_" ){
        //_,_
        sqlTemp = "SELECT DISTINCT parent FROM parents;";
        Database::getParentSql(followBuffer,sqlTemp);

        // _,_
        if(rhs == "_"){
            sqlTemp = "SELECT child FROM parents;";
            Database::getParentSql(followBuffer,sqlTemp);

            if(followBuffer.empty()){
                return false;
            }
        }
            //_,num
        else if(utils::isDigit(rhs)){
            sqlTemp = "SELECT child FROM parents;";
            Database::getParentSql(selectBuffer,sqlTemp);
            if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
                exist = true;
                return true;
//                followBuffer.clear();
//                followBuffer.push_back(Database::getParentLhs(rhs));
            }else{
                exist = false;
                followBuffer.clear();
                return false;
            }

//            if(exist){
//                for(string s:selectBuffer){
//                    if(stoi(s)<stoi(rhs)){
//                        followBuffer.push_back(Database::getParentLhs(s));
//                    }
//                }
//            }
            selectBuffer.clear();
        }
            //_,synm
        else if(rhs!= "_" && !utils::isDigit(rhs)){
            tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
            cout << "                                       debug " << tmpSynm<<endl;

            if(tmpSynm == "stmt"){
                followBuffer.clear();
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(followBuffer,sqlTemp);
                if(followBuffer.empty()){
                    return false;
                }
            }
            else if(tmpSynm == "variable"){

                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(selectBuffer,sqlTemp);

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
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(selectBuffer,sqlTemp);

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
            else if(tmpSynm == "-1"){
                return false;
            }
            else{
                followBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(selectBuffer,sqlTemp);

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
        Database::insertRelation("Parent",lhs,rhs,"T");
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
        sqlTemp = "SELECT DISTINCT parent FROM parents;";
        Database::getParentSql(selectBuffer,sqlTemp);

        if (std::find(selectBuffer.begin(), selectBuffer.end(), lhs) != selectBuffer.end()){
            exist = true;
        }
        else{
            exist = false;
            return false;
        }

        if(exist){ //means it's a parents
            selectBuffer.clear();
            //num,_
            if(rhs == "_"){
                sqlTemp = "SELECT child FROM parents where parent = '"+lhs+"';";
                Database::getParentSql(followBuffer,sqlTemp);

                if(followBuffer.empty()){
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
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(selectBuffer,sqlTemp);
                if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
                    exist = true;
                }else{
                    followBuffer.clear();
                    exist = false;
                    return false;
                }

                if (exist) {
                    sqlTemp = "SELECT DISTINCT parent FROM parents WHERE parent = '"+lhs+"' AND child = '"+rhs+"';";
                    Database::getParentSql(followBuffer,sqlTemp);
                    if(followBuffer.empty()){
                        return false;
                    }
                    //check if the stmt is right
//                    sqlTemp = "SELECT DISTINCT parent FROM parents;";
//                    Database::getParentSql(selectBuffer,sqlTemp);
//                    for(string snum :selectBuffer){
//                        if(snum > lhs){
//                            numBuffer.push_back(snum);
//                        }
//                    }
//                    selectBuffer.clear();
////                    //get num lhs in follow
//                    followBuffer = numBuffer;
//                    sqlTemp = "SELECT child FROM parents;";
//                    Database::getParentSql(selectBuffer, sqlTemp);
//                    for (string snum :selectBuffer) {
//                        if (snum < rhs) {
//                            followBuffer.push_back(snum);
//                        }
//                    }
                    selectBuffer.clear();

                }
            }
                //num,synm
            else{
                tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
                stmtStmtBuffer.clear();
                if(tmpSynm == "stmt"){
                    sqlTemp = "SELECT child FROM parents WHERE parent == '"+ lhs +"';";
                    Database::getParentSql(followBuffer,sqlTemp);

                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                }
                else if(tmpSynm == "variable"){
                    Database::getVariableStmt(varStmtBuffer);
                    for(string var:varStmtBuffer){
                        Database::getParentLhs(stmtStmtBuffer,var);
                        for(string s:stmtStmtBuffer){
                            followBuffer.push_back(s);
                        }
                    }
                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                    varStmtBuffer.clear();

                }else if(tmpSynm == "constant"){
                    Database::getConstantStmt(constStmtBuffer);
                    sqlTemp = "SELECT child FROM parents;";
                    Database::getParentSql(selectBuffer,sqlTemp);

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
                else if(tmpSynm == "-1"){
                    return false;
                }
                else{
                    stmtStmtBuffer.clear();
                    sqlTemp = "SELECT DISTINCT child FROM parentstar WHERE parent = '"+ lhs +"';";
                    Database::getParentStarSql(stmtStmtBuffer,sqlTemp);

                    sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                    Database::getParentStarSql(selectBuffer,sqlTemp);

                    for(string s:stmtStmtBuffer){
                        if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                            followBuffer.push_back(s);
                        }
                    }
                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                    stmtStmtBuffer.clear();
                }
            }
        }
        Database::insertRelation("Parent",lhs,rhs,"T");
    }

    //synm,?
    else if(lhs!= "_" && !utils::isDigit(lhs)){

        //get synm from the table
        tmpSynm = Query::getSynm(synonyms,lhs); // get the raw synm type
        if(tmpSynm == "stmt"){
            sqlTemp = "SELECT DISTINCT parent FROM parents;";
            Database::getParentSql(followBuffer,sqlTemp);
            if(followBuffer.empty()){
                return false;
            }
        }
        else if(tmpSynm == "variable"){
            Database::getVariableStmt(varStmtBuffer);
            sqlTemp = "SELECT DISTINCT parent FROM parents;";
            Database::getParentSql(selectBuffer,sqlTemp);
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
            sqlTemp = "SELECT DISTINCT parent FROM parents;";
            Database::getParentSql(selectBuffer,sqlTemp);
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
        else if(tmpSynm == "-1"){
            return false;
        }
        else{
            stmtStmtBuffer.clear();
            Database::getStmtType(stmtStmtBuffer,tmpSynm);
            sqlTemp = "SELECT DISTINCT parent FROM parents;";
            Database::getParentSql(selectBuffer,sqlTemp);
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
                sqlTemp = "SELECT child FROM parents WHERE parent = '"+ s +"';";
                Database::getParentSql(stmtStmtBuffer,sqlTemp);
                if(!stmtStmtBuffer.empty()){
                    followBuffer.push_back(s);
                }else{
                    return false;
                }
            }
            Database::insertRelation("Parents",lhs,rhs,"T");
        }
            //synm,num
        else if(utils::isDigit(rhs)) {

            selectBuffer.clear();
            selectBuffer = followBuffer;
            followBuffer.clear();
            for(string s:selectBuffer){
                Database::getParentLhs(followBuffer,rhs);
            }

            if(followBuffer.empty()){
                return false;
            }else{
                Database::insertRelation("Parents",lhs,rhs,"T");
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
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(followBuffer,sqlTemp);
            }

            else if(tmpSynm == "variable"){
                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(selectBuffer,sqlTemp);

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
                        Database::getIsParent(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                varStmtBuffer.clear();

            }else if(tmpSynm == "constant"){
                Database::getConstantStmt(constStmtBuffer);
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(selectBuffer,sqlTemp);

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
                        Database::getIsParent(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                constStmtBuffer.clear();
            }
            else if(tmpSynm == "-1"){
                return false;
            }
            else{
                stmtStmtBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT child FROM parents;";
                Database::getParentSql(selectBuffer,sqlTemp);

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

                stmtStmtBuffer.clear();


                for(string s1:buffer){
                    Database::getParentLhs(stmtStmtBuffer,s1); //extract all child with lhs parents


                    for(string stmt:stmtStmtBuffer) { //1st synm
                        for (string s:selectBuffer) {
                            if (stmt == s) {
                                for (int i = 0; i < select.size(); i++) {
                                    //check i is stmt, v, c select the stmts
                                    if (rhs == select[i].first) {
                                        followBuffer.push_back(s1);
                                    } else if (lhs == select[i].first) {
                                        cout << "                        222               debug " << s << " " << stmt
                                             << endl;
                                        followBuffer.push_back(s);
                                    } else if (rhs != select[i].first && lhs != select[i].first) {
                                        cout << "                        333               debug " << lhs << "  " << rhs
                                             << endl;

                                        followBuffer.push_back(s);
                                        followBuffer.push_back(stmt);
                                    }
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
            Database::insertRelation("Parents",lhs,rhs,"T");
//            return true;
        }
    }

    return true;

}

bool Parent::parentStar(map<string,vector<string>> &synonyms,vector<pair<string,vector<string>>> &select,vector<string> &followBuffer,string lhs, string rhs){
    //query
    string sqlTemp = "";
    //three type of query from SQL _,synm
    string tmpSynm="";
    vector<string> constStmtBuffer;
    vector<string> varStmtBuffer;
    vector<string> stmtStmtBuffer;

    //parent
    vector<string> selectBuffer;
    vector<string> numBuffer; //_,num after comparing and join back to Follow
    vector<string> varInRelationBuffer;
    vector<string> varInRelationExist;
    vector<string> constInRelationBuffer;
    vector<string> numBufferB;
    vector<string> buffer;
    bool exist=true;

    //_?
    if( lhs == "_" ){
        //_,_
        sqlTemp = "SELECT DISTINCT parent FROM parentstar;";
        Database::getParentStarSql(followBuffer,sqlTemp);

        // _,_
        if(rhs == "_"){
            sqlTemp = "SELECT DISTINCT child FROM parentstar;";
            Database::getParentStarSql(followBuffer,sqlTemp);

            if(followBuffer.empty()){
                return false;
            }
        }
            //_,num
        else if(utils::isDigit(rhs)){
            sqlTemp = "SELECT DISTINCT child FROM parentstar;";
            Database::getParentStarSql(selectBuffer,sqlTemp);
            cout << "                                       debug " << rhs<<endl;

            if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
                exist = true;

                return true;
//                followBuffer.clear();
//                followBuffer.push_back(Database::getParentLhs(rhs));
            }else{
                exist = false;
                followBuffer.clear();
                return false;
            }

            selectBuffer.clear();
        }
            //_,synm
        else if(rhs!= "_" && !utils::isDigit(rhs)){
            tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
            if(tmpSynm == "stmt"){

                followBuffer.clear();
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(followBuffer,sqlTemp);
            }
            else if(tmpSynm == "variable"){

                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(selectBuffer,sqlTemp);

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
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(selectBuffer,sqlTemp);

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
            else if(tmpSynm == "-1"){
                return false;
            }
            else{
                followBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(selectBuffer,sqlTemp);

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
        Database::insertRelation("Parent",lhs,rhs,"T");
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
        sqlTemp = "SELECT DISTINCT parent FROM parentstar;";
        Database::getParentStarSql(selectBuffer,sqlTemp);

        if (std::find(selectBuffer.begin(), selectBuffer.end(), lhs) != selectBuffer.end()){
            exist = true;
        }
        else{
            exist = false;
            return false;
        }

        if(exist){ //means it's a parents
            selectBuffer.clear();
            //num,_
            if(rhs == "_"){
                sqlTemp = "SELECT DISTINCT child FROM parentstar where parent = '"+lhs+"';";
                Database::getParentStarSql(followBuffer,sqlTemp);

                if(followBuffer.empty()){
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
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(selectBuffer,sqlTemp);
                if (std::find(selectBuffer.begin(), selectBuffer.end(), rhs) != selectBuffer.end()){
                    exist = true;
                }else{
                    followBuffer.clear();
                    exist = false;
                    return false;
                }

                if (exist) {
                    //check if the stmt is right
                    sqlTemp = "SELECT DISTINCT parent FROM parentstar WHERE parent = '"+lhs+"' AND child = '"+rhs+"';";
                    Database::getParentSql(followBuffer,sqlTemp);
                    if(followBuffer.empty()){
                        return false;
                    }
//                    sqlTemp = "SELECT DISTINCT parent FROM parentstar;";
//                    Database::getParentStarSql(selectBuffer,sqlTemp);
//                    for(string snum :selectBuffer){
//                        if(snum > lhs){
//                            numBuffer.push_back(snum);
//                        }
//                    }
//                    selectBuffer.clear();
////                    //get num lhs in follow
//                    followBuffer = numBuffer;
//                    sqlTemp = "SELECT DISTINCT child FROM parentstar;";
//                    Database::getParentStarSql(selectBuffer,sqlTemp);
//                    for (string snum :selectBuffer) {
//                        if (snum < rhs) {
//                            followBuffer.push_back(snum);
//                        }
//                    }
                    selectBuffer.clear();

                }
            }
                //num,synm
            else{
                tmpSynm = Query::getSynm(synonyms,rhs); // get the raw synm types
                stmtStmtBuffer.clear();
                if(tmpSynm == "stmt"){
                    sqlTemp = "SELECT DISTINCT child FROM parentstar WHERE parent == '"+ lhs +"';";
                    Database::getParentStarSql(followBuffer,sqlTemp);

                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                }
                else if(tmpSynm == "variable"){
                    Database::getVariableStmt(varStmtBuffer);
                    for(string var:varStmtBuffer){
                        Database::getParentLhs(stmtStmtBuffer,var);
                        for(string s:stmtStmtBuffer){
                            followBuffer.push_back(s);
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
                    sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                    Database::getParentStarSql(selectBuffer,sqlTemp);

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
                else if(tmpSynm == "-1"){
                    return false;
                }
                else{
                    stmtStmtBuffer.clear();
                    sqlTemp = "SELECT DISTINCT child FROM parentstar WHERE parent = '"+ lhs +"';";
                    Database::getParentStarSql(stmtStmtBuffer,sqlTemp);

                    sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                    Database::getParentStarSql(selectBuffer,sqlTemp);

                    for(string s:stmtStmtBuffer){
                        if (std::find(selectBuffer.begin(), selectBuffer.end(), s) != selectBuffer.end()){
                            followBuffer.push_back(s);
                        }
                    }
                    if(followBuffer.empty()){
                        return false;
                    }
                    selectBuffer.clear();
                    stmtStmtBuffer.clear();
                }
            }
        }
        Database::insertRelation("Parent",lhs,rhs,"T");
    }

        //synm,?
    else if(lhs!= "_" && !utils::isDigit(lhs)){

        //get synm from the table
        tmpSynm = Query::getSynm(synonyms,lhs); // get the raw synm type
        if(tmpSynm == "stmt"){
            sqlTemp = "SELECT DISTINCT parent FROM parentstar;";
            Database::getParentStarSql(followBuffer,sqlTemp);
            if(followBuffer.empty()){
                return false;
            }
        }
        else if(tmpSynm == "variable"){
            Database::getVariableStmt(varStmtBuffer);
            sqlTemp = "SELECT DISTINCT parent FROM parentstar;";
            Database::getParentStarSql(selectBuffer,sqlTemp);
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
            sqlTemp = "SELECT DISTINCT parent FROM parentstar;";
            Database::getParentStarSql(selectBuffer,sqlTemp);
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
        else if(tmpSynm == "-1"){
            return false;
        }
        else{
            stmtStmtBuffer.clear();
            Database::getStmtType(stmtStmtBuffer,tmpSynm);
            sqlTemp = "SELECT DISTINCT parent FROM parentstar;";
            Database::getParentStarSql(selectBuffer,sqlTemp);
            for(string stmt:stmtStmtBuffer){
                if (std::find(selectBuffer.begin(), selectBuffer.end(), stmt) != selectBuffer.end()){
                    cout << "             parents                          debug " << stmt<<endl;
                    followBuffer.push_back(stmt);
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
                sqlTemp = "SELECT DISTINCT child FROM parentstar WHERE parent = '"+ s +"';";
                Database::getParentStarSql(stmtStmtBuffer,sqlTemp);
                if(!stmtStmtBuffer.empty()){
                    followBuffer.push_back(s);
                }else{
                    return false;
                }
            }
            Database::insertRelation("Parents",lhs,rhs,"T");
        }
            //synm,num
        else if(utils::isDigit(rhs)) {

            selectBuffer.clear();
            selectBuffer = followBuffer;
            followBuffer.clear();
            for(string s:selectBuffer){
                Database::getParentStarLhs(followBuffer,rhs);
            }

            if(followBuffer.empty()){
                return false;
            }else{
                Database::insertRelation("Parents",lhs,rhs,"T");
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
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(followBuffer,sqlTemp);
            }

            else if(tmpSynm == "variable"){
                Database::getVariableStmt(varStmtBuffer);
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(selectBuffer,sqlTemp);

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
                        Database::getIsParentStar(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                varStmtBuffer.clear();

            }
            else if(tmpSynm == "constant"){
                Database::getConstantStmt(constStmtBuffer);
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(selectBuffer,sqlTemp);

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
                        Database::getIsParentStar(followBuffer,s,stmt);
                    }
                }

                buffer.clear();
                selectBuffer.clear();
                constStmtBuffer.clear();
            }
            else if(tmpSynm == "-1"){
                cout << "                        lhs " << lhs << " rhs " << rhs
                     << endl;
                return false;
            }
            else{


                stmtStmtBuffer.clear();
                Database::getStmtType(stmtStmtBuffer,tmpSynm);
                sqlTemp = "SELECT DISTINCT child FROM parentstar;";
                Database::getParentStarSql(selectBuffer,sqlTemp);

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

                stmtStmtBuffer.clear();


                for(string s1:buffer){
                    Database::getParentStarLhs(stmtStmtBuffer,s1); //extract all child with lhs parents

                    for(string stmt:stmtStmtBuffer) { //1st synm

                        for (string s:selectBuffer) {
                            if (stmt == s) {
                                for (int i = 0; i < select.size(); i++) {
                                    //check i is stmt, v, c select the stmts

                                    if (rhs == select[i].first) {
                                        followBuffer.push_back(s1);
                                    } else if (lhs == select[i].first) {

                                        followBuffer.push_back(s);
                                    } else if (rhs != select[i].first && lhs != select[i].first) {
                                        cout << "                        333               debug " << lhs << "  " << rhs
                                             << endl;

                                        followBuffer.push_back(s);
                                        followBuffer.push_back(stmt);
                                    }
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
            Database::insertRelation("Parents",lhs,rhs,"T");
            return true;
        }
    }

    return true;

}



