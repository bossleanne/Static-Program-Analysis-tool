#include "SourceProcessor.h"
#include <iostream>
// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.
void SourceProcessor::process(string program) {
    // initialize the database
    Database::initialize();

    // tokenize the program
    Tokenizer tk;
    vector<string> tokens;
    tk.tokenize(program, tokens);
    string procedureName;
    procedureName = tokens.at(1);

    unsigned int stmtNum = 0;

    //Variable wait for the end -> to make sure the variable is unique before insert to database.
    vector<string> variables;

    //Parser procedure and insert it to procedure table
    //start to read thought the lines:
    for(int i = 0; i<tokens.size();i++){

        //insert procedure
        if (tokens.at(i)  == "procedure"){
            procedureName = tokens.at(i+1);
            Database::insertProcedure(tokens.at(i + 1));
        }
        else if (tokens.at(i)  == "read") { // insert read
            stmtNum++;
            Database::insertRead(tokens.at(i + 1), procedureName, to_string(stmtNum));
            Database::insertStmt("read", procedureName, to_string(stmtNum));
            if (!(std::find(variables.begin(), variables.end(), tokens.at(i+1)) != variables.end()))
            {
                variables.push_back(tokens.at(i+1));
            }
        }
        else if (tokens.at(i)  == "=") { // insert read
            stmtNum++;
            Database::insertStmt("assign", procedureName, to_string(stmtNum));

            //check if the variable on the left hand side already exist, else push_back to the variable vector
            if (!(std::find(variables.begin(), variables.end(), tokens.at(i-1)) != variables.end()))
            {
                variables.push_back(tokens.at(i-1));
            }

            //check right hand side is digit or string, if digit push to constant, else push to variable, but check variable
            if(!isDigit(tokens.at(i+1))){
                if (!(std::find(variables.begin(), variables.end(), tokens.at(i+1)) != variables.end()))
                {
                    variables.push_back(tokens.at(i+1));
                }
            }else{
                //push to constant table
                Database::insertConstant(tokens.at(i+1), procedureName);
            }
            Database::insertAssign(procedureName, to_string(stmtNum));

        }
        else if (tokens.at(i)  == "print"){
            stmtNum++;
            Database::insertStmt("print",procedureName, to_string(stmtNum));
            if (!(std::find(variables.begin(), variables.end(), tokens.at(i+1)) != variables.end()))
            {
                variables.push_back(tokens.at(i+1));
            }
            Database::insertPrint(to_string(stmtNum), procedureName);
        }

        Database::insertVariable(variables, procedureName);


    }

}

//check if the variable is a c or int
bool SourceProcessor::isDigit(string str) {
    for (char& ch : str) {
        if (isdigit(ch)==false) {
            return false;
        }
    }
    return true;
}
