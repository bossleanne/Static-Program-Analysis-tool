#include "SourceProcessor.h"

// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.

void SourceProcessor::process(string program) { // process == insertion
    // initialize the database
    Database::initialize();

    // tokenize the program
    Tokenizer tk;
    vector<string> tokens;
    tk.tokenize(program, tokens);

    //stmtNum -> &
    int stmtNum = 0;


    int i = 0;
    //insert procedure
    string procedureName;
    while(i<tokens.size()){
        if(tokens.at(i) == "procedure"){
            procedureName = tokens.at(i+1);
            Database::insertProcedure(procedureName);
            i+=2;
            //process stmt List
            stmtList(tokens,i,stmtNum,-1,procedureName);
//            Parent::parentsParse(procedureName,tokens);

        }
        i++;
    }


}

void SourceProcessor::stmtList(vector<string>tokens,int&i,int &stmtNum,int parentStmt, string procedureName) {
    //Variable & constant wait for the end -> to make sure the variable is unique before insert to database.

    string variable;
    int stmtBefore = 0;
    string condition;
    vector <string> expression;
    stack<int> nestedLevel;
    vector <string> follows;
    vector <string> parent;
    int ifcount = 0;
    int ifstmt = 0;
    string pp = "";
    string sqlTemp = "";
    vector <string> childBuffer;
    vector<string> callBuffer;
    vector<string> parentsBuffer;

    while (i < tokens.size()-1) {
        if (tokens.at(i)  == "read") { // insert read
            //check the follow relationship
            stmtNum++;
            if(stmtBefore != 0 ){
                Database::insertFollowS(procedureName,to_string(stmtBefore),to_string(stmtNum));
                Database::getFollowS(follows,to_string(stmtNum));
                for(string s:follows){
                    Database::insertFollowStar(procedureName,s,to_string(stmtNum));
                }
                Database::insertFollowStar(procedureName,to_string(stmtBefore),to_string(stmtNum));
            }
            if (parentStmt != -1) {
                Database::insertParentStar(procedureName, to_string(parentStmt), to_string(stmtNum));
//                Database::getParentS(parentsBuffer,to_string(stmtNum));
//                for(string s:parentsBuffer){
//                    Database::insertParentStar(procedureName,s,to_string(stmtNum));
//                }
                Database::insertParent(procedureName, to_string(parentStmt), to_string(stmtNum));
            }
            stmtBefore = stmtNum;
            readParser(stmtNum, procedureName, tokens.at(i+1));

        }
        else if (tokens.at(i)  == "print"){

            stmtNum++;
            if(stmtBefore != 0 ){
                Database::insertFollowS(procedureName,to_string(stmtBefore),to_string(stmtNum));
                Database::getFollowS(follows,to_string(stmtNum));
                for(string s:follows){
                    Database::insertFollowStar(procedureName,s,to_string(stmtNum));
                }
            }
            if (parentStmt != -1) {
                Database::insertParentStar(procedureName, to_string(parentStmt), to_string(stmtNum));
//                Database::getParentS(parentsBuffer,to_string(stmtNum));
//                for(string s:parentsBuffer){
//                    Database::insertParentStar(procedureName,s,to_string(stmtNum));
//                }
                Database::insertParent(procedureName, to_string(parentStmt), to_string(stmtNum));
            }
            stmtBefore = stmtNum;
            printParser(stmtNum, procedureName, tokens.at(i+1));

        }
        else if (tokens.at(i) == "if"){

            stmtNum++;
            ifstmt = stmtNum;
            if(stmtBefore != 0 && stmtNum > 1){
                Database::insertFollowS(procedureName,to_string(stmtBefore),to_string(stmtNum));
                Database::getFollowS(follows,to_string(stmtNum));
                for(string s:follows){
                    Database::insertFollowStar(procedureName,s,to_string(stmtNum));
                }
            }
            if (parentStmt != -1) {
                Database::insertParentStar(procedureName, to_string(parentStmt), to_string(stmtNum));
//                Database::getParentS(parentsBuffer,to_string(stmtNum));
//                for(string s:parentsBuffer){
//                    Database::insertParentStar(procedureName,s,to_string(stmtNum));
//                }
                Database::insertParent(procedureName, to_string(parentStmt), to_string(stmtNum));
            }

            stmtBefore = stmtNum;
            Database::insertStmt("if",procedureName, to_string(stmtNum));
            if(tokens.at(i) == "if" && tokens.at(i+1) == "("){
                i+=2;
                ifcount++;
                while(tokens.at(i+1)!= "then"){

                    if(tokens.at(i) == ")" && tokens.at(i+1) == "then"){
                        break;
                    }
                    if(InfixToPostfix::isCal(tokens.at(i))){
                        i++;
                        if(InfixToPostfix::isCal(tokens.at(i))){
                            i++;
                        }
                    }

                    //check if the lhs is a constant or variable
                    if(utils::isDigit(tokens.at(i))){
                        Database::insertConstant(tokens.at(i),to_string(stmtNum),procedureName);
                    }
                    else if(!utils::isDigit(tokens.at(i)) && !InfixToPostfix::isOptr(tokens.at(i)) && tokens.at(i)!= "(" && tokens.at(i)!= ")"){
                        Database::insertVariable(tokens.at(i),to_string(stmtNum),procedureName);
                        Database::insertUses(procedureName,to_string(stmtNum),tokens.at(i));
                    }

                    condition += tokens.at(i);
                    i++;
                }

            }
            if(tokens.at(i) == ")" && tokens.at(i+1) == "then" && tokens.at(i+2) == "{"){
                i+=3;
                stmtList(tokens,i,stmtNum,ifstmt,procedureName);
            }
        }
        else if(tokens.at(i) == "else"){
            i+=2;
            stmtList(tokens,i,stmtNum,ifstmt,procedureName);
        }
        else if (tokens.at(i) == "while"){

            stmtNum++;
            if(stmtBefore != 0 ){
                Database::insertFollowS(procedureName,to_string(stmtBefore),to_string(stmtNum));
                Database::getFollowS(follows,to_string(stmtNum));
                for(string s:follows){
                    Database::insertFollowStar(procedureName,s,to_string(stmtNum));
                }
            }
            if (parentStmt != -1) {
                Database::insertParentStar(procedureName, to_string(parentStmt), to_string(stmtNum));
//                Database::getParentS(parentsBuffer,to_string(stmtNum));
//                for(string s:parentsBuffer){
//                    Database::insertParentStar(procedureName,s,to_string(stmtNum));
//                }
                Database::insertParent(procedureName, to_string(parentStmt), to_string(stmtNum));
            }

            stmtBefore = stmtNum;

            Database::insertStmt("while",procedureName, to_string(stmtNum));
            if(tokens.at(i) == "while" && tokens.at(i+1) == "("){
                i+=2;

                while(tokens.at(i+1)!= "{"){

                    if(tokens.at(i) == ")" && tokens.at(i+1) == "{"){
                        break;
                    }
                    if(InfixToPostfix::isCal(tokens.at(i))){
                        i++;
                        if(InfixToPostfix::isCal(tokens.at(i))){
                            i++;
                        }

                        //check if the rhs is a constant or variable
                        if(utils::isDigit(tokens.at(i))){
                            Database::insertConstant(tokens.at(i),to_string(stmtNum),procedureName);
                        }else if(!InfixToPostfix::isOrAnd(tokens.at(i)) && !InfixToPostfix::isScope(tokens.at(i))){
                            Database::insertVariable(tokens.at(i),to_string(stmtNum),procedureName);
                        }
                    }

                    //check if the lhs is a constant or variable
                    if(utils::isDigit(tokens.at(i))){
                        Database::insertConstant(tokens.at(i),to_string(stmtNum),procedureName);
                    }else if(!utils::isDigit(tokens.at(i)) && !InfixToPostfix::isOptr(tokens.at(i)) && tokens.at(i)!= "(" && tokens.at(i)!= ")"){
                        Database::insertVariable(tokens.at(i),to_string(stmtNum),procedureName);
                        Database::insertUses(procedureName,to_string(stmtNum),tokens.at(i));
                    }
                    condition += tokens.at(i);
                    i++;
                }
            }
            if(tokens.at(i) == ")" && tokens.at(i+1) == "{"){
                nestedLevel.push(stmtNum);
                i+=2;
                stmtList(tokens,i,stmtNum,stmtNum,procedureName);
            }


        }
        else if (tokens.at(i)  == "=") { // insert assign

            if(InfixToPostfix::isOptr(tokens.at(i+1))){
                i++;
            }
            else{

                stmtNum++;
                if(stmtBefore != 0 ){
                    Database::insertFollowS(procedureName,to_string(stmtBefore),to_string(stmtNum));
                    Database::getFollowS(follows,to_string(stmtNum));
                    for(string s:follows){
                        Database::insertFollowStar(procedureName,s,to_string(stmtNum));
                    }
                }
                if (parentStmt != -1) {
                    Database::insertParentStar(procedureName, to_string(parentStmt), to_string(stmtNum));
//                    Database::getParentS(parentsBuffer,to_string(stmtNum));
//                    for(string s:parentsBuffer){
//                        Database::insertParentStar(procedureName,s,to_string(stmtNum));
//                    }
                    Database::insertParent(procedureName, to_string(parentStmt), to_string(stmtNum));
                }

                stmtBefore = stmtNum;
                assignParser(stmtNum, procedureName , tokens , i);
            }


        }
        else if (tokens.at(i) == "call"){
            stmtNum++;
            if(stmtBefore != 0 && stmtNum > 1){
                Database::insertFollowS(procedureName,to_string(stmtBefore),to_string(stmtNum));
                Database::getFollowS(follows,to_string(stmtNum));
                for(string s:follows){
                    Database::insertFollowStar(procedureName,s,to_string(stmtNum));
                }
            }
            if (parentStmt != -1) {
                Database::insertParentStar(procedureName, to_string(parentStmt), to_string(stmtNum));
//                Database::getParentS(parentsBuffer,to_string(stmtNum));
//                for(string s:parentsBuffer){
//                    Database::insertParentStar(procedureName,s,to_string(stmtNum));
//                }
                Database::insertParent(procedureName, to_string(parentStmt), to_string(stmtNum));
            }

            stmtBefore = stmtNum;

            Database::insertStmt("call",procedureName, to_string(stmtNum));
            Database::insertVariable(tokens.at(i+1),to_string(stmtNum),procedureName);
            Database::insertUses(procedureName,to_string(stmtNum),tokens.at(i+1));
            Database::insertModifies(procedureName,to_string(stmtNum),tokens.at(i+1));
            Database::insertCall(to_string(stmtNum),procedureName,tokens.at(i+1));
            Database::getCallS(callBuffer,tokens.at(i+1));
            for(string s:callBuffer){
                Database::insertCallStar(to_string(stmtNum),s,tokens.at(i+1));
            }


        }
        else if(tokens.at(i) == "}"){
            break;
        }
        i++;
    }
}

void SourceProcessor::readParser(int &stmtNum, string procedureName, string readVar){
    // insert read
    Database::insertRead(to_string(stmtNum), procedureName);
    Database::insertVariable(readVar,to_string(stmtNum),procedureName);
    Database::insertStmt("read", procedureName, to_string(stmtNum));
    Database::insertModifies(procedureName,to_string(stmtNum),readVar);
//    checkVar(variables,readVar);
}


void SourceProcessor::printParser(int &stmtNum, string procedureName, string printVar){
    Database::insertPrint(to_string(stmtNum), procedureName);
    Database::insertStmt("print",procedureName, to_string(stmtNum));
    Database::insertUses(procedureName,to_string(stmtNum),printVar);
    Database::insertVariable(printVar,to_string(stmtNum),procedureName);
}

void SourceProcessor::assignParser(int &stmtNum, string procedureName, vector<string>&tokens , int &i) {
    string expression = "";
    vector<string> postfixExp;
    string lhs;
    //insert stmts to the stmts table
    Database::insertStmt("assign", procedureName, to_string(stmtNum));

    //insert variable to assign table
    if(!InfixToPostfix::isOptr(tokens.at(i-1))) {
        Database::insertAssign(procedureName, to_string(stmtNum));
        Database::insertVariable(tokens.at(i-1),to_string(stmtNum),procedureName);
        Database::insertModifies(procedureName,to_string(stmtNum),tokens.at(i-1));
        lhs = tokens.at(i-1);
    }

    i++; //move i position to the left side;
    while(tokens.at(i) != ";"){
        if(utils::isDigit(tokens.at(i))){
            Database::insertConstant(tokens.at(i),to_string(stmtNum),procedureName);
            Database::insertSubPattern(procedureName,to_string(stmtNum),lhs,tokens.at(i));
        }
        else if(!InfixToPostfix::isOptr(tokens.at(i)) && tokens.at(i) != "(" && tokens.at(i) != ")"){
            Database::insertVariable(tokens.at(i),to_string(stmtNum),procedureName);
            Database::insertUses(procedureName,to_string(stmtNum),tokens.at(i));
            Database::insertSubPattern(procedureName,to_string(stmtNum),lhs,tokens.at(i));
//            InfixToPostfix::partialExp(procedureName,stmtNum,postfixExp);
        }
        expression += tokens.at(i);
        i++;
    }


    postfixExp = InfixToPostfix::in_to_post(expression);
    Database::insertExp(procedureName,to_string(stmtNum) , lhs, postfixExp);
    InfixToPostfix::partialExp(procedureName,stmtNum,postfixExp);
}