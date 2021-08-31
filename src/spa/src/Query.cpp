//
// Created by Leanne on 3/3/21.
//

#include "Query.h"
/*
    for query:
    step 1 : check it's a Singale select or double select
    step 2 : check if there's a such clause behind it
    step 3 : determine which calause it is
    step 4 : parse the lhs and rhs
    - 9 possible lhs and rhs
        clause (_,_) // select all
        clause (_,stmt)
        clause (stmt,_)
        clause (synonymType,synonymType)
        clause (_,synonymType)
        clause (synonymType,_)
        clause (stmt,stmt)
        clause (_,stmt)
        clause (stmt,_)
 */
bool Query::isClause(vector<string> &tokens) {
    for(string s:tokens){
        if(s == "such" || s == "pattern"){
            return true;
        }
    }
    return false;
}
bool Query::isUseInRelation(vector<pair<string,vector<string>>> select) {
    vector<string> buffer;
    buffer.clear();
    string sqlTemp = "";
    Database::getRel(buffer);
    for (const auto& pair : select)
    {
        string key = pair.first;
        vector<string> value = pair.second;
        for( string s: buffer ){
            if (std::find(buffer.begin(), buffer.end(), pair.first) != buffer.end()){
                return true;
            }
        }
    }
    Database::emptyRel();
    return false;
}

string Query::getSynm(map<string,vector<string>> &synonyms,string &synm){

    for (const auto& pair : synonyms)
    {
        string key = pair.first;
        vector<string> value = pair.second;
        for( string s: pair.second ){
            if(s == synm){
                return key;
            }
        }
    }
    return "-1";
}




void Query::process(vector<string>tokens,vector<string> &databaseResults){
    int i = 0;
    string clause = "";
//    map<string, string> synonyms;
    vector<string> suchThat;
    vector<string> pattern;
    vector<string> databaseData; // store selected <?> data query from the database
    bool isClause_ = false;
    isClause_ = isClause(tokens);
    vector<string> finalResult;
    string stmtType = "";

    //declaration
    map<string,vector<string>> synonyms;
    string temp = "";

    //select
    vector<pair<string,vector<string>>> select;
    vector<string> synms;
    vector<string> constBuffer;
    vector<string> varBuffer;

    //relationship
    string lhs = "";
    string rhs = "";
    vector<pair<string,vector<string>>> FollowBuffer;
    string sqlTemp = "";
    //three type of query from SQL _,synm
    string tmpSynm="";
    vector<string> constStmtBuffer;
    vector<string> varStmtBuffer;
    vector<string> stmtStmtBuffer;
        //follow
    vector<string> followBuffer;
    vector<string> selectBuffer;
    vector<string> numBuffer; //_,num after compairinga and join back to Follow

    vector<string> varInRelationBuffer;
    vector<string> varInRelationExist;
    vector<string> constInRelationBuffer;
    bool followValid = true;

        //use
    string UseStr = "";
    bool hasProcedure = true;
    bool hasRelation = true;

    //relationship
    bool relationTF = true;
    vector<string> pendingResult;


    while(i < tokens.size()) {
//        cout << "       pp token "<<tokens.at(i)<<"   "<<rhs<<endl;

        if (tokens.at(i) == "stmt") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "read") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "print") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "assign") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "while") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "if") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "call") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "procedure") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "constant") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }
        else if (tokens.at(i) == "variable") {
            temp = tokens.at(i);
            i++;
            while(tokens.at(i)!=";"){
                synonyms[temp].push_back(tokens.at(i));
                i++;
            }
        }

        if (tokens.at(i) == "Select") { // single selection Select 1 item
            i++;
            if(tokens.at(i) == "<"){
                while(tokens.at(i)!=">"){
                    for( const auto& pair : synonyms ) {
                        for( string s: pair.second )  {
                            if(s == tokens.at(i)){ // found the name and start to query
//                                cout << " >>>> >>>>>>>>>>>>>>>>>>" << s << " " << pair.first <<endl;
                                //get the value from the backend first;
                                //1.get constant
                                if(pair.first == "constant"){
                                    Database::getConstant(constBuffer);
                                    select.push_back(make_pair(s,constBuffer));
                                }
                                    //2.get varibale
                                else if (pair.first == "variable"){
                                    Database::getVariables(varBuffer);
                                    select.push_back(make_pair(s,varBuffer));
                                }
                                    //3.get procedure
                                else if (pair.first == "procedure") {
                                    varBuffer.clear();
                                    Database::getProcedures(varBuffer);
                                    select.push_back(make_pair(s, varBuffer));
                                }
                                    //4.get all stmts
                                else if (pair.first == "stmt"){
                                    Database::getStmt(synms);
                                    select.push_back(make_pair(s,synms));
                                }
                                    //5.get all otherstmt
                                else{
                                    synms.clear();
                                    Database::getStmtType(synms,pair.first);
                                    select.push_back(make_pair(s,synms));
                                }
                            }
                            synms.clear();
                        }
                    }
                    i++;
                }
                i++;
            }
            else{
                for( const auto& pair : synonyms ) {

                    for( string s: pair.second )  {
                        if(s == tokens.at(i)){ // found the name and start to query

                            //get the value from the backend first;
                            //1.get constant
                            if(pair.first == "constant"){
                                Database::getConstant(constBuffer);
                                select.push_back(make_pair(s,constBuffer));
                            }
                            //2.get varibale
                            else if (pair.first == "variable"){
                                Database::getVariables(varBuffer);
                                select.push_back(make_pair(s,varBuffer));
                            }
                            //3.get procedure
                            else if (pair.first == "procedure") {
                                varBuffer.clear();
                                Database::getProcedures(varBuffer);
                                select.push_back(make_pair(s, varBuffer));
                            }
                            //4.get all stmts
                            else if (pair.first == "stmt"){
                                Database::getStmt(synms);
                                select.push_back(make_pair(s,synms));
                            }
                            //5.get all otherstmt
                            else{
                                synms.clear();
                                Database::getStmtType(synms,pair.first);
                                select.push_back(make_pair(s,synms));
                            }

                        }
                        synms.clear();
                    }
                }
                i++;
            }
        }
        if(!isClause_){
            for(int i = 0; i < select.size(); i++)
            {
                finalResult = select[i].second;
            }
        }
        else{
            if (tokens.at(i) == "such") {
                i+=2;
                //start to parser the relationship,

                //follow relationship
                if(tokens.at(i) == "Follows" && tokens.at(i+1)!="*"){
                    i+=2;
                    lhs = tokens.at(i);
                    i+=2;
                    rhs = tokens.at(i);
                    relationTF = Follow::follows(synonyms,select,followBuffer,lhs,rhs);
                    //combined with select
                    for(int j = 0; j < select.size(); ++j)
                    {
                        if(!isUseInRelation(select)){
                            if(relationTF){
                                //check i is stmt, v, c select the stmts
                                if(getSynm(synonyms,select[j].first) == "variable"){
                                    Database::getVariables(finalResult);
                                }
                                else if(getSynm(synonyms,select[j].first) == "constant"){
                                    Database::getConstant(finalResult);
                                }
                                else{
                                    finalResult = select[j].second;
                                }
                            }

                        }
                        else{
                            //check i is stmt, v, c select the stmts
                            if(getSynm(synonyms,select[j].first) == "variable"){
                                Database::getVariableStmt(varStmtBuffer);
                                selectBuffer = varStmtBuffer;
                                varInRelationBuffer = Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:varInRelationBuffer){
                                    Database::getVariableWithStmt(finalResult,s);
                                }
                            }
                            else if(getSynm(synonyms,select[j].first) == "constant"){
                                Database::getConstantStmt(constStmtBuffer);
                                selectBuffer = constStmtBuffer;
                                constInRelationBuffer=Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:constInRelationBuffer){
                                    Database::getConstantWithStmt(finalResult,s);
                                }
                            }
                            else{
//                                cout << "                   dunck --------- " <<endl;
                                selectBuffer = select[j].second;
                                //combined select with follow
                                finalResult=Query::matchTwoVect(selectBuffer,followBuffer);
                            }
                        }

                    }
                    i+=1;
                }

                    //followStar relationship
                else if(tokens.at(i) == "Follows" && tokens.at(i+1)=="*"){
                    i+=3;
                    lhs = tokens.at(i);
                    i+=2;
                    rhs = tokens.at(i);
                    Follow::followstar(synonyms,select,followBuffer,lhs,rhs);
                    //combined with select
                    for(int j = 0; j < select.size(); ++j)
                    {
                        if(!isUseInRelation(select)){
                            if(relationTF){
                                if(getSynm(synonyms,select[j].first) == "variable"){
                                    Database::getVariables(finalResult);
                                }
                                else if(getSynm(synonyms,select[j].first) == "constant"){
                                    Database::getConstant(finalResult);
                                }
                                else{
                                    finalResult = select[j].second;
                                }
                            }
                        }
                        else{
                            //check i is stmt, v, c select the stmts
                            if(getSynm(synonyms,select[j].first) == "variable"){
                                Database::getVariableStmt(varStmtBuffer);
                                selectBuffer = varStmtBuffer;
                                varInRelationBuffer = Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:varInRelationBuffer){
                                    Database::getVariableWithStmt(finalResult,s);
                                }
                            }else if(getSynm(synonyms,select[j].first) == "constant"){
                                Database::getConstantStmt(constStmtBuffer);
                                selectBuffer = constStmtBuffer;
                                constInRelationBuffer=Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:constInRelationBuffer){
                                    Database::getConstantWithStmt(finalResult,s);
                                }
                            }else{
                                selectBuffer = select[j].second;
                                //combined select with follow
                                finalResult=Query::matchTwoVect(selectBuffer,followBuffer);
                            }
                        }

                    }
                    i+=1;

                }

                    //use relationship
                else if(tokens.at(i) == "Uses"){
                    i+=2;
                    lhs = tokens.at(i);
                    i+=2;
                    rhs = tokens.at(i);

                    Use::useRelationship(synonyms,select,followBuffer,lhs,rhs);

                    //combined with select
                    for(int j = 0; j < select.size(); ++j)
                    {
                       //lhs / rhs used in uses
                        if(getSynm(synonyms,select[j].first) == "variable"){
                            finalResult = followBuffer;
                        }
                        //follow has all variables
                        else{
                            finalResult = followBuffer;
                        }

//                        else{
//                            finalResult
//                        }


//                        if(getSynm(synonyms,select[j].first) == "variable"){
//                            Database::getVariables(varStmtBuffer);
//                            finalResult = Query::matchTwoVect(varStmtBuffer,followBuffer);
//                        }
//                        else {
//                            if(getSynm(synonyms,select[j].first) == "procedure") {
//                                if(hasRelation)
//                                    Database::getProcedures(finalResult);
////                                finalResult = followBuffer;
//                            }
//                            else if (getSynm(synonyms,select[j].first) == "while" or select[j].first =="if"){
//                                if(hasRelation)
//                                    Database::getStmtType(finalResult,select[j].first);
//                            }
//                            else{
////                                if(isUseInRelation(select)){
//                                    cout << "                    ddddddd   "<<endl;
//                                    selectBuffer = select[j].second;
//                                    finalResult = Query::matchTwoVect(selectBuffer, followBuffer);
////                                }else{
////                                    finalResult = select[j].second;
////                                }else{
////                                    finalResult = select[j].second;
////                                }
//
//                            }
//
//                        }

                    }
                    i+=1;
                }

                //modifies
                else if(tokens.at(i) == "Modifies"){
                    i+=2;
                    if(lhs == ""){
                        while(tokens.at(i) !=","){
                            lhs += tokens.at(i);
                            i++;
                        }
                    }
                    if(rhs == ""){
                        i+=1;
                        while(tokens.at(i) !=")"){
                            rhs += tokens.at(i);
                            i++;
                        }
                    }
                    cout << "                    lhs  " << lhs<<"     rjs  " <<rhs<<endl;

                    hasRelation = Modifies::modRelation(synonyms,select,followBuffer,lhs,rhs);

                    //combined with select
                    for(int j = 0; j < select.size(); ++j)
                    {
                        if(getSynm(synonyms,select[j].first) == "variable"){

                            if(getSynm(synonyms,lhs) == "variable" || getSynm(synonyms,rhs) == "variable") {
                                finalResult.clear();
                                finalResult = followBuffer;
                            }

                        }
                        else {
                            if(getSynm(synonyms,select[j].first) == "procedure") {
                                if(hasRelation){
                                    if(getSynm(synonyms,lhs) == "procedure" || getSynm(synonyms,rhs) == "procedure"){
                                        finalResult = followBuffer;
                                    }
                                    else{
                                        Database::getProcedures(finalResult);
                                    }
                                }

                            }
                            else if (getSynm(synonyms,select[j].first) == "while" or select[j].first =="if"){
                                Database::getStmtType(finalResult,select[j].first);
                            }
                            else{
                                selectBuffer = select[j].second;
                                finalResult = Query::matchTwoVect(selectBuffer, followBuffer);
                            }

                        }

                    }
                    i+=1;
                }

                //parents
                else if(tokens.at(i) == "Parent" && tokens.at(i+1)!="*"){
                    i+=2;
                    lhs = tokens.at(i);
                    i+=2;
                    rhs = tokens.at(i);
                    relationTF = Parent::parents(synonyms,select,followBuffer,lhs,rhs);
                    //combined with select
                    for(int j = 0; j < select.size(); ++j)
                    {
                        if(!isUseInRelation(select)){
                            cout << "                   dunck --------- " <<endl;
                            if(relationTF){
                                cout << "                   realtion? --------- " <<endl;

                                //check i is stmt, v, c select the stmts
                                if(getSynm(synonyms,select[j].first) == "variable"){
                                    Database::getVariables(finalResult);
                                }
                                else if(getSynm(synonyms,select[j].first) == "constant"){
                                    Database::getConstant(finalResult);
                                }
                                else{
                                    finalResult = select[j].second;
                                }
                            }

                        }
                        else{
                            cout << "                   opposs --------- " <<endl;

                            //check i is stmt, v, c select the stmts
                            if(getSynm(synonyms,select[j].first) == "variable"){
                                Database::getVariableStmt(varStmtBuffer);
                                selectBuffer = varStmtBuffer;
                                varInRelationBuffer = Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:varInRelationBuffer){
                                    Database::getVariableWithStmt(finalResult,s);
                                }
                            }
                            else if(getSynm(synonyms,select[j].first) == "constant"){
                                Database::getConstantStmt(constStmtBuffer);
                                selectBuffer = constStmtBuffer;
                                constInRelationBuffer=Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:constInRelationBuffer){
                                    Database::getConstantWithStmt(finalResult,s);
                                }
                            }
                            else{
                                if(relationTF){
                                    selectBuffer = select[j].second;
                                    //combined select with follow
                                    finalResult=Query::matchTwoVect(selectBuffer,followBuffer);
                                }

                            }
                        }

                    }
                    i+=1;
                }

                    //parentstar
                else if(tokens.at(i) == "Parent" && tokens.at(i+1)=="*"){
                    i+=3;
                    lhs = tokens.at(i);
                    i+=2;
                    rhs = tokens.at(i);
                    relationTF = Parent::parentStar(synonyms,select,followBuffer,lhs,rhs);
                    //combined with select
                    for(int j = 0; j < select.size(); ++j)
                    {
                        if(!isUseInRelation(select)){
                            cout << "                   dunck --------- " <<endl;
                            if(relationTF){
                                cout << "                   realtion? --------- " <<endl;

                                //check i is stmt, v, c select the stmts
                                if(getSynm(synonyms,select[j].first) == "variable"){
                                    Database::getVariables(finalResult);
                                }
                                else if(getSynm(synonyms,select[j].first) == "constant"){
                                    Database::getConstant(finalResult);
                                }
                                else{
                                    finalResult = select[j].second;
                                }
                            }

                        }
                        else{
                            cout << "                   opposs --------- " <<endl;

                            //check i is stmt, v, c select the stmts
                            if(getSynm(synonyms,select[j].first) == "variable"){
                                Database::getVariableStmt(varStmtBuffer);
                                selectBuffer = varStmtBuffer;
                                varInRelationBuffer = Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:varInRelationBuffer){
                                    Database::getVariableWithStmt(finalResult,s);
                                }
                            }
                            else if(getSynm(synonyms,select[j].first) == "constant"){
                                Database::getConstantStmt(constStmtBuffer);
                                selectBuffer = constStmtBuffer;
                                constInRelationBuffer=Query::matchTwoVect(selectBuffer,followBuffer);
                                for(string s:constInRelationBuffer){
                                    Database::getConstantWithStmt(finalResult,s);
                                }
                            }
                            else{
                                if(relationTF){
                                    selectBuffer = select[j].second;
                                    //combined select with follow
                                    finalResult=Query::matchTwoVect(selectBuffer,followBuffer);
                                }
                            }
                        }

                    }
                    i+=1;
                }

            }
            else if(tokens.at(i) == "pattern"){
                i+=3;
                if(lhs == ""){
                    while(tokens.at(i) !=","){
                        lhs += tokens.at(i);
                        i++;
                    }
                }
                if(rhs == ""){
                    i+=1;
                    while(tokens.at(i) !=")"){
                        rhs += tokens.at(i);
                        i++;
                    }
                }
                Pattern::pattern(synonyms,select,followBuffer,lhs, rhs);
                stmtStmtBuffer.clear();
                for(int j = 0; j < select.size(); ++j)
                {
                    if(getSynm(synonyms,select[j].first) == "variable"){
//                        finalResult = followBuffer;
                        for(string s:followBuffer){
                            cout <<"                     "<<s<<endl;
                            sqlTemp = "SELECT lhs FROM pattern WHERE stmtNum = '"+ s +"';";
                            Database::getPattern(finalResult,sqlTemp);
                        }

                    }
                    else if(!isUseInRelation(select)){
                        if(getSynm(synonyms,select[j].first) == "stmt"){
                            if(!followBuffer.empty())
                                Database::getStmt(finalResult);
                        }
                        else if(getSynm(synonyms,select[j].first) == "assign"){
                            if(!followBuffer.empty())
                                finalResult = followBuffer;
                        }
                        else if(!followBuffer.empty()){
                            Database::getStmtType(finalResult,getSynm(synonyms,select[j].first));
                        }
                    }
                    else{
//                        for(string s:followBuffer){
//                            cout <<"                     "<<s<<endl;
//                            sqlTemp = "SELECT lhs FROM pattern WHERE stmtNum = '"+ s +"';";
////                            Database::getPattern(followBuffer,sqlTemp);
//                        }
                        finalResult = followBuffer;
                    }
                }

            }

        }

        i++;
    }
    databaseResults = finalResult;
}

vector<string> Query::matchTwoVect(vector<string> v1,vector<string> v2){
    vector<string> matchResult;
    for (vector<string>::iterator i = v1.begin(); i != v1.end(); ++i)
    {
        if (std::find(v2.begin(), v2.end(), *i) != v2.end())
        {
            matchResult.push_back(*i);
        }
    }
    return matchResult;
}