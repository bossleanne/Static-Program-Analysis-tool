#include "Database.h"

sqlite3* Database::dbConnection;
vector<vector<string> > Database::dbResults;
char* Database::errorMessage;

// method to connect to the database and initialize tables in the database
void Database::initialize() {
	// open a database connection and store the pointer into dbConnection
	sqlite3_open("database.db", &dbConnection);

	// drop the existing procedure table (if any)
	string dropProcedureTableSQL = "DROP TABLE IF EXISTS procedures";
	sqlite3_exec(dbConnection, dropProcedureTableSQL.c_str(), NULL, 0, &errorMessage);

	// create a procedure table
	string createProcedureTableSQL = "CREATE TABLE procedures ( procedureName VARCHAR(255) PRIMARY KEY);";
	sqlite3_exec(dbConnection, createProcedureTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing variable table (if any)
    string dropVariableTableSQL = "DROP TABLE IF EXISTS variables";
    sqlite3_exec(dbConnection, dropVariableTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a variable table
    string createVariableTableSQL = "CREATE TABLE variables ( \n"
                                    "\tvariableName VARCHAR(255),\n"
                                    "\tstmtNum VARCHAR(255),\n"
                                    "\tprocedureName VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createVariableTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing read table (if any)
    string dropReadTableSQL = "DROP TABLE IF EXISTS reads";
    sqlite3_exec(dbConnection, dropReadTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a reads table
    string createReadsTableSQL = "CREATE TABLE reads ( \n"
                                 "    stmtNum VARCHAR(255),\n"
                                 "\tprocedureName VARCHAR(255)\n"
                                 ");";
    sqlite3_exec(dbConnection, createReadsTableSQL.c_str(), NULL, 0, &errorMessage);


    // drop the existing call table (if any)
    string dropCallTableSQL = "DROP TABLE IF EXISTS call";
    sqlite3_exec(dbConnection, dropCallTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a call table
    string createCallTableSQL = "CREATE TABLE call ( \n"
                                 "    stmtNum VARCHAR(255),\n"
                                 "\tprocedureName VARCHAR(255),\n"
                                "\tcalling VARCHAR(255)\n"
                                 ");";
    sqlite3_exec(dbConnection, createCallTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing callStar table (if any)
    string dropCallStarableSQL = "DROP TABLE IF EXISTS callstar";
    sqlite3_exec(dbConnection, dropCallStarableSQL.c_str(), NULL, 0, &errorMessage);

    // create a call table
    string createCallStarTableSQL = "CREATE TABLE callstar ( \n"
                                "    stmtNum VARCHAR(255),\n"
                                "\tprocedureName VARCHAR(255),\n"
                                "\tcalling VARCHAR(255)\n"
                                ");";
    sqlite3_exec(dbConnection, createCallStarTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a call table
    string createNextTableSQL = "CREATE TABLE next ( \n"
                                "    stmtNum VARCHAR(255),\n"
                                "\tprocedureName VARCHAR(255),\n"
                                "\tcurNode VARCHAR(255),\n"
                                "\tnextNode VARCHAR(255)\n"
                                ");";
    sqlite3_exec(dbConnection, createNextTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing callStar table (if any)
    string dropNextStarableSQL = "DROP TABLE IF EXISTS nextstar";
    sqlite3_exec(dbConnection, dropNextStarableSQL.c_str(), NULL, 0, &errorMessage);

    // create a next table
    string createNextStarTableSQL = "CREATE TABLE nextstar ( \n"
                                    "    stmtNum VARCHAR(255),\n"
                                    "\tprocedureName VARCHAR(255),\n"
                                    "\tcurNode VARCHAR(255),\n"
                                    "\tnextNode VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createNextStarTableSQL.c_str(), NULL, 0, &errorMessage);


    // drop the existing statements table (if any)
    string dropStatementsTableSQL = "DROP TABLE IF EXISTS statements";
    sqlite3_exec(dbConnection, dropStatementsTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a statements table
    string createStmtTableSQL = "CREATE TABLE statements ( \n"
                                "\tstmtNum VARCHAR(255) PRIMARY KEY,\n"
                                "    stmtType VARCHAR(255),\n"
                                "    procedureName VARCHAR(255)\n"
                                ");";

    sqlite3_exec(dbConnection, createStmtTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing constants table (if any)
    string dropConstantTableSQL = "DROP TABLE IF EXISTS constants";
    sqlite3_exec(dbConnection, dropConstantTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a constants table
    string createConstantTableSQL = "CREATE TABLE constants ( \n"
                                    "\tconstantName VARCHAR(255),\n"
                                    "\tstmtNum VARCHAR(255),\n"
                                    "\tprocedureName VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createConstantTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing print table (if any)
    string dropPrintTableSQL = "DROP TABLE IF EXISTS prints";
    sqlite3_exec(dbConnection, dropPrintTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a prints table
    string createPrintsTableSQL = "CREATE TABLE prints ( \n"
                                  "    stmtNum VARCHAR(255),\n"
                                  "    procedureName VARCHAR(255)\n"
                                  ");";
    sqlite3_exec(dbConnection, createPrintsTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing assigns table (if any)
    string dropAssignsTableSQL = "DROP TABLE IF EXISTS assigns";
    sqlite3_exec(dbConnection, dropAssignsTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a assigns table
    string createAssignsTableSQL = "CREATE TABLE assigns ( \n"
                                 "\tstmtNum VARCHAR(255) PRIMARY KEY,\n"
                                 "    procedureName VARCHAR(255)\n"
                                 ");";
    sqlite3_exec(dbConnection, createAssignsTableSQL.c_str(), NULL, 0, &errorMessage);


    // drop the existing parents table (if any)
    string dropParentsTableSQL = "DROP TABLE IF EXISTS parents";
    sqlite3_exec(dbConnection, dropParentsTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a Parents table
    string createParentsTableSQL = "CREATE TABLE parents(\n"
                                    "\tparent VARCHAR(255),\n"
                                    "    procedureName VARCHAR(255), \n" //current procedure
                                    "    child VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createParentsTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing parentStar table (if any)
    string dropParentStarTableSQL = "DROP TABLE IF EXISTS parentstar";
    sqlite3_exec(dbConnection, dropParentStarTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a ParentStar table
    string createParentStarTableSQL = "CREATE TABLE parentstar(\n"
                                   "\tparent VARCHAR(255),\n"
                                   "    procedureName VARCHAR(255), \n" //current procedure
                                   "    child VARCHAR(255)\n"
                                   ");";
    sqlite3_exec(dbConnection, createParentStarTableSQL.c_str(), NULL, 0, &errorMessage);


//    // drop the existing follow table (if any)
    string dropFollowTableSQL = "DROP TABLE IF EXISTS follows";
    sqlite3_exec(dbConnection, dropFollowTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a follow table
    string createFollowTableSQL = "CREATE TABLE follows( \n"
                                  "\tprocedureName VARCHAR(255),\n"
                                  "\tstmtBefore VARCHAR(255),\n"
                                  "\tstmtAfter VARCHAR(255)\n"
                                  ");";
    sqlite3_exec(dbConnection, createFollowTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing follow table (if any)
    string dropFollowStarTableSQL = "DROP TABLE IF EXISTS followstar";
    sqlite3_exec(dbConnection, dropFollowStarTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a followsT table
    string createFollowStarTableSQL = "CREATE TABLE followstar( \n"
                                    "\tprocedureName VARCHAR(255),\n"
                                    "\tstmtBefore VARCHAR(255),\n"
                                    "\tstmtAfter VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createFollowStarTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing modifies table (if any)
    string dropModifiesTableSQL = "DROP TABLE IF EXISTS modifies";
    sqlite3_exec(dbConnection, dropModifiesTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a modifies table
    string createModifiesTableSQL = "CREATE TABLE modifies(\n"
                                    "\tstmtNum VARCHAR(255),\n"
                                    "    procedureName VARCHAR(255), \n" //current procedure
                                    "    variable VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createModifiesTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing uses table (if any)
    string dropUsesTableSQL = "DROP TABLE IF EXISTS uses";
    sqlite3_exec(dbConnection, dropUsesTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a uses table
    string createUsesTableSQL = "CREATE TABLE uses(\n"
                                    "\tstmtNum VARCHAR(255),\n"
                                    "    procedureName VARCHAR(255), \n" //current procedure
                                    "    variable VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createUsesTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing expression table (if any)
    string dropExpTableSQL = "DROP TABLE IF EXISTS expression";
    sqlite3_exec(dbConnection, dropExpTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a expression table
    string createExpTableSQL = "CREATE TABLE expression(\n"
                                "\tstmtNum VARCHAR(255) PRIMARY KEY,\n"
                                "    procedureName VARCHAR(255), \n" //current procedure
                                "    assign VARCHAR(255),\n"
                                "    rhs VARCHAR(255)\n"
                                ");";
    sqlite3_exec(dbConnection, createExpTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing pattern table (if any)
    string dropPatternTableSQL = "DROP TABLE IF EXISTS pattern";
    sqlite3_exec(dbConnection, dropPatternTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a pattern table
    string createPatternTableSQL = "CREATE TABLE pattern(\n"
                               "\tstmtNum VARCHAR(255),\n"
                               "    lhs VARCHAR(255), \n" //current procedure
                               "    partExp VARCHAR(255),\n"
                               "    procedureName VARCHAR(255)\n"
                               ");";
    sqlite3_exec(dbConnection, createPatternTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing relation table (if any)
    string dropRelTableSQL = "DROP TABLE IF EXISTS relationship";
    sqlite3_exec(dbConnection, dropRelTableSQL.c_str(), NULL, 0, &errorMessage);

    //create a expression table
    string createRelTableSQL = "CREATE TABLE relationship(\n"
                               "\trelType VARCHAR(255),\n"
                               "    lhs VARCHAR(255), \n" //current procedure
                               "    rhs VARCHAR(255),\n"
                               "    hasRel VARCHAR(255)\n"
                               ");";
    sqlite3_exec(dbConnection, createRelTableSQL.c_str(), NULL, 0, &errorMessage);

    // initialize the result vector
	dbResults = vector<vector<string> >();
}

// method to close the database connection
void Database::close() {
	sqlite3_close(dbConnection);
}

// method to insert a procedure into the database
void Database::insertProcedure(string procedureName) {
	string insertProcedureSQL = "INSERT INTO procedures ('procedureName') VALUES ('" + procedureName + "');";
	sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the procedures from the database
void Database::getProcedures(vector<string>& results){
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getProceduresSQL = "SELECT procedureName FROM procedures;";
	sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

// method to insert a variables into the database
void Database::insertVariable(string variableName,string stmtNum,string procedureName) {
    string insertVariableSQL="INSERT INTO variables ('variableName','stmtNum','procedureName') VALUES ('" + variableName + "','"+ stmtNum +"', '" + procedureName + "');";
//            "INSERT INTO variables ('variableName','stmtNum,'procedureName') VALUES ('" + variableName + "','"+ stmtNum +"', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertVariableSQL.c_str(), NULL, 0, &errorMessage);
}


// method to get all the variables from the database
void Database::getVariables(vector<string>& results){
    // clear the existing results
    dbResults.clear();
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getVariableSQL = "SELECT DISTINCT variableName FROM variables;";
    sqlite3_exec(dbConnection, getVariableSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}
void Database::getVariableStmt(vector<string>& results){
    // clear the existing results
    dbResults.clear();
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getVariableNameSQL = "SELECT stmtNum FROM variables;";
    sqlite3_exec(dbConnection, getVariableNameSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}
void Database::getVariableWithStmt(vector<string>& results,string stmtNum){
    // clear the existing results
    dbResults.clear();
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getVariableNameSQL = "SELECT DISTINCT variableName FROM variables WHERE stmtNum = '"+stmtNum+"';";
    sqlite3_exec(dbConnection, getVariableNameSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}



// method to insert a readVar into the database
void Database::insertRead(string stmtNum, string procedureName) {
    string insertReadSQL = "INSERT INTO reads ('stmtNum','procedureName') VALUES ('"+ stmtNum +"', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertReadSQL.c_str(), NULL, 0, &errorMessage);

}


void Database::getReads(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getReadsSQL = "SELECT stmtNum FROM reads;";
    sqlite3_exec(dbConnection, getReadsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a readVar into the database
void Database::insertPrint(string stmtNum,string procedureName) {
    string insertPrintSQL = "INSERT INTO prints ('stmtNum','procedureName') VALUES ('"+ stmtNum +"', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertPrintSQL.c_str(), NULL, 0, &errorMessage);
}


void Database::getPrints(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getPrintsSQL = "SELECT stmtNum FROM prints;";
    sqlite3_exec(dbConnection, getPrintsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

void Database::insertStmt(string stmtType, string procedureName, string stmtNum){
    string insertStmtSQL = "INSERT INTO statements ('stmtNum','stmtType','procedureName') VALUES ('" + stmtNum + "','"+ stmtType +"', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertStmtSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::getStmt(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getStmtsSQL = "SELECT DISTINCT stmtNum FROM statements;";
    sqlite3_exec(dbConnection, getStmtsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a variables into the database
void Database::insertConstant(string constantName,string stmtNum,string procedureName) {
//    string insertConstantSQL = "INSERT INTO constants ('constantName','stmtNum,'procedureName') VALUES ('" + constantName + "','" + stmtNum + "','" + procedureName + "');";
    string insertConstantSQL="INSERT INTO constants ('constantName','stmtNum','procedureName') VALUES ('" + constantName + "','"+ stmtNum +"', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertConstantSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::getConstant(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getConstantsSQL = "SELECT DISTINCT constantName FROM constants;";
    sqlite3_exec(dbConnection, getConstantsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

void Database::getConstantStmt(vector<string>& results){
    // clear the existing results
    dbResults.clear();
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getConstantStmtSQL = "SELECT constantStmt FROM constants;";
    sqlite3_exec(dbConnection, getConstantStmtSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


void Database::getConstantWithStmt(vector<string>& results,string stmtNum){
    // clear the existing results
    dbResults.clear();
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getConstantStmtSQL = "SELECT constantName FROM constants WHERE stmtNum = '"+stmtNum+"';";
    sqlite3_exec(dbConnection, getConstantStmtSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

//insert Assign
void Database::insertAssign(string procedureName, string stmtNum){
    string insertAssignSQL = "INSERT INTO assigns ('stmtNum','procedureName') VALUES ('" + stmtNum + "', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertAssignSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::getAssign(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getAssignsSQL = "SELECT stmtNum FROM assigns;";
    sqlite3_exec(dbConnection, getAssignsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a call into the database
void Database::insertCall(string stmtNum,string procedureName,string calling) {
    string insertCallSQL = "INSERT INTO call ('stmtNum','procedureName','calling') VALUES ('"+ stmtNum +"', '" + procedureName + "','"+calling+"');";
    sqlite3_exec(dbConnection, insertCallSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the values from the follows database
void Database::getCallSql(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getCallSQL = sql;
    sqlite3_exec(dbConnection, getCallSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

void Database::insertCallStar(string stmtNum,string procedureName,string calling) {
    string insertCallSQL = "INSERT INTO callstar ('stmtNum','procedureName','calling') VALUES ('"+ stmtNum +"', '" + procedureName + "','"+calling+"');";
    sqlite3_exec(dbConnection, insertCallSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the values from the follows database
void Database::getCallS(vector<string>& results,string call){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getCallSTSQL = "SELECT procedureName FROM call WHERE calling = '"+ call +"';";
    sqlite3_exec(dbConnection, getCallSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

void Database::getStmtType(vector<string>& results,string stmtType){
    // clear the existing results
    dbResults.clear();
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getAssignsSQL = "SELECT DISTINCT stmtNum FROM statements WHERE stmtType = '"+ stmtType +"';";
    sqlite3_exec(dbConnection, getAssignsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

void Database::getType(vector<string>& results,string type){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getWhileSQL = "SELECT stmtNum FROM statements where stmtType = '" + type + "';";
    sqlite3_exec(dbConnection, getWhileSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a values into the followstar database
void Database::insertFollowS(string procedureName, string stmtBefore ,string stmtAfter) {
    string insertFollowSTSQL = "INSERT INTO follows ('procedureName','stmtBefore','stmtAfter') VALUES ('" + procedureName + "', '" + stmtBefore + "','" + stmtAfter + "');";
    sqlite3_exec(dbConnection, insertFollowSTSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the values from the follows database
void Database::getFollowS(vector<string>& results,string currentStmt){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT stmtBefore FROM follows WHERE stmtAfter = '"+ currentStmt +"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}
// method to get all the values from the follows database
void Database::getIsFollow(vector<string>& results,string lhs,string rhs){
    // clear the existing results
    dbResults.clear();
    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT stmtBefore FROM follows WHERE stmtBefore = '"+ lhs +"' AND stmtAfter = '"+ rhs +"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the values from the follows database
string Database::getFollowRhs(string stmtBefore){
    // clear the existing results
    dbResults.clear();
    string stmtAfter;
    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT stmtAfter FROM follows WHERE stmtBefore = '"+stmtBefore+"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        stmtAfter = dbRow.at(0);
        return stmtAfter;
    }
}

// method to get all the values from the follows database
void Database::getFollow(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = sql;
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


string Database::getFollowLhs(string stmtAfters){
    // clear the existing results
    dbResults.clear();
    string stmtAfter;
    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT stmtBefore FROM follows WHERE stmtAfter = '"+ stmtAfters +"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        stmtAfter = dbRow.at(0);
        return stmtAfter;
    }
}

// method to insert a values into the followstar database
void Database::insertFollowStar(string procedureName, string stmtBefore ,string stmtAfter) {
    string insertFollowsTSQL = "INSERT INTO followstar ('procedureName','stmtBefore','stmtAfter') VALUES ('" + procedureName + "', '" + stmtBefore + "','" + stmtAfter + "');";
    sqlite3_exec(dbConnection, insertFollowsTSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the values from the follows database
void Database::getFollowStarS(vector<string>& results,string currentStmt){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT stmtBefore FROM followstar WHERE stmtAfter = '"+ currentStmt +"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the values from the follows database
void Database::getIsFollowStar(vector<string>& results,string lhs,string rhs){
    // clear the existing results
    dbResults.clear();
    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT stmtBefore FROM followstar WHERE stmtBefore = '"+ lhs +"' AND stmtAfter = '"+ rhs +"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

bool Database::checkStmt(string lhs,string rhs,string sql){
    // clear the existing results
    dbResults.clear();
    // The callback method is only used when there are results to be returned.
    string querySQL = sql;

    //    string getFollowSTSQL = "SELECT stmtBefore FROM followstar WHERE stmtBefore = '"+ lhs +"' AND stmtAfter = '"+ rhs +"';";
    sqlite3_exec(dbConnection, querySQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        if(!dbRow.empty()){
            return true;
        }
        else{
            return false;
        }
    }
}

// method to get all the values from the follows database
string Database::getFollowRhsStar(string stmtBefore){
    // clear the existing results
    dbResults.clear();
    string stmtAfter;
    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT stmtAfter FROM followstar WHERE stmtBefore = '"+stmtBefore+"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        stmtAfter = dbRow.at(0);
        return stmtAfter;
    }
}

// method to get all the values from the follows database
void Database::getFollowStar(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = sql;
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


string Database::getFollowLhsStar(string stmtAfters){
    // clear the existing results
    dbResults.clear();
    string stmtAfter;

    // The callback method is only used when there are results to be returned.
    string getFollowSTSQL = "SELECT DISTINCT stmtBefore FROM followstar WHERE stmtAfter = '"+ stmtAfters +"';";
    sqlite3_exec(dbConnection, getFollowSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        stmtAfter = dbRow.at(0);
        return stmtAfter;
    }
}

// method to get all the values from the parents database
void Database::getSon(vector<string>& results,string parent){
    // clear the existing results
    dbResults.clear();


    // The callback method is only used when there are results to be returned.
    string getParentSQL = "SELECT DISTINCT child FROM parents WHERE parent = " + parent;

    sqlite3_exec(dbConnection, getParentSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


// method to get all the values from the follows database
void Database:: getParentS(vector<string>& results,string currentStmt){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getParentSTSQL ="SELECT DISTINCT parent FROM parentstar where child = " + currentStmt + ";";
    sqlite3_exec(dbConnection, getParentSTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);

        results.push_back(result);
    }
}
// method to get all the values from the follows database
void Database::getIsParent(vector<string>& results,string lhs,string rhs){
    // clear the existing results
    dbResults.clear();
    // The callback method is only used when there are results to be returned.
    string getIsParentSQL = "SELECT parent FROM parents WHERE parent = '"+ lhs +"' AND stmtAfter = '"+ rhs +"';";
    sqlite3_exec(dbConnection, getIsParentSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the values from the follows database
void Database::getParentRhs(vector<string>& results,string parent){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getParentRhsSQL = "SELECT child FROM parents WHERE parent = '"+parent+"';";
    sqlite3_exec(dbConnection, getParentRhsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the values from the follows database
void Database::getParentSql(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getParentTSQL = sql;
    sqlite3_exec(dbConnection, getParentTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
//        cout << "                                       -------------- "<<result<<endl;
        results.push_back(result);
    }
}


void Database::getParentLhs(vector <string> &results,string child){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getParentLhsSQL = "SELECT DISTINCT parent FROM parents WHERE child = '"+ child +"';";
    sqlite3_exec(dbConnection, getParentLhsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


// method to insert a values into the parents database
void Database::insertParent(string procedureName,string parent , string child) {
    string insertParentSQL = "INSERT INTO parents ('parent','procedureName','child') VALUES ('" + parent + "', '" + procedureName + "','" + child + "');";
    sqlite3_exec(dbConnection, insertParentSQL.c_str(), NULL, 0, &errorMessage);
}


// method to insert a values into the parentstar database
void Database::insertParentStar(string procedureName,string parent, string child) {
    string insertParentStarSQL = "INSERT INTO parentstar ('parent','procedureName','child') VALUES ('" + parent + "', '" + procedureName + "','" + child + "');";
    sqlite3_exec(dbConnection, insertParentStarSQL.c_str(), NULL, 0, &errorMessage);
    vector<string> buffer;
    vector<string> tmp;
    getParentS(buffer, parent);

    for (string s : buffer) {
        string sqlTemp = "SELECT DISTINCT child FROM parentstar where parent = '"+ parent + "';";
        Database::getParentSql(tmp,sqlTemp);
        for(string s2:tmp){
            string insertParentdSSQL = "INSERT INTO parentstar ('parent','procedureName','child') VALUES ('" + s + "', '" + procedureName + "','" + s2 + "');";
            sqlite3_exec(dbConnection, insertParentdSSQL.c_str(), NULL, 0, &errorMessage);
            for (vector<string> dbRow : dbResults) {
                string result;
                result = dbRow.at(0);
            }
        }

    }
}

void Database::getParentStarLR(vector<string>& results,string parent,string son) {
    // clear the existing results
    dbResults.clear();


    // The callback method is only used when there are results to be returned.
    string getParentStarSQL = "SELECT DISTINCT parent FROM parentstar WHERE parent = '" + parent+"' and child = '" + son+"';";

    sqlite3_exec(dbConnection, getParentStarSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the values from the follows database
void Database::getIsParentStar(vector<string>& results,string lhs,string rhs){
    // clear the existing results
    dbResults.clear();
    // The callback method is only used when there are results to be returned.
    string getIsParentStarSQL = "SELECT DISTINCT parent FROM parentstar WHERE parent = '"+ lhs +"' AND stmtAfter = '"+ rhs +"';";
    sqlite3_exec(dbConnection, getIsParentStarSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the values from the follows database
void Database::getParentStarSql(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getParentStarTSQL = sql;
    sqlite3_exec(dbConnection, getParentStarTSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


void Database::getParentStarLhs(vector <string> &results,string child){
    // clear the existing results
    dbResults.clear();

    // The callback method is only used when there are results to be returned.
    string getParentStarSQL = "SELECT DISTINCT parent FROM parentstar WHERE child = '"+ child +"';";
    sqlite3_exec(dbConnection, getParentStarSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}




// method to insert a values into the modifies database
void Database::insertModifies(string procedureName,string stmtNum , string variable) {
    string insertModifiesSQL = "INSERT INTO modifies ('stmtNum','procedureName','variable') VALUES ('" + stmtNum + "', '" + procedureName + "','" + variable + "');";
    sqlite3_exec(dbConnection, insertModifiesSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the values from the database
void Database::getModifies(vector<string>& results,string lhs,string rhs){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getModifiesSQL = "SELECT variable FROM modifies WHERE " + lhs + " = " + rhs;

    sqlite3_exec(dbConnection, getModifiesSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


void Database::getModSql(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getModsSQL = sql;

    sqlite3_exec(dbConnection, getModsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a value into the database
void Database::insertUses(string procedureName,string stmtNum , string variable) {
    string insertUsesSQL = "INSERT INTO uses ('stmtNum','procedureName','variable') VALUES ('" + stmtNum + "', '" + procedureName + "','" + variable + "');";
    sqlite3_exec(dbConnection, insertUsesSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the lhs & rhs from the database
void Database::getUses(vector<string>& results,string lhs,string rhs){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getUsesSQL = "SELECT variable FROM uses WHERE " + lhs + " = " + rhs;

    sqlite3_exec(dbConnection, getUsesSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


void Database::getUsesSql(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getUsesSQL = sql;

    sqlite3_exec(dbConnection, getUsesSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

bool Database::checkUses(string lhs,string rhs){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getUsesSQL = "SELECT * FROM uses WHERE '" + lhs + "' AND = '" + rhs +"';";

    sqlite3_exec(dbConnection, getUsesSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        if(!dbRow.empty()){
            return true;
        }else{
            return false;
        }
    }
}

bool Database::checkFollow(string lhs,string rhs){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getUsesSQL = "SELECT * FROM Follows WHERE stmtBefore = '" + lhs + "' AND stmtAfter = '" + rhs +"';";

    sqlite3_exec(dbConnection, getUsesSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        if(!dbRow.empty()){
            return true;
        }else{
            return false;
        }
    }
}

void Database::getSql(vector<string>& results,string sql){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getUsesSQL = sql;

    sqlite3_exec(dbConnection, getUsesSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

void Database::emptyRel(){
    // clear the existing results
    dbResults.clear();
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string delSQL = "DELETE FROM relationship;";
    sqlite3_exec(dbConnection, delSQL.c_str(), callback, 0, &errorMessage);
}




// method to insert a expression into the database
void Database::insertExp(string procedureName,string stmtNum , string lhs, vector<string> postfix) {
    string expression;
    for (auto& it : postfix) {
        expression+=it;
    }
    string insertExpSQL = "INSERT INTO expression ('stmtNum','procedureName','assign','rhs') VALUES ('" + stmtNum + "', '" + procedureName + "','" + lhs + "','" + expression + "');";
    sqlite3_exec(dbConnection, insertExpSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get a expression from the database
void Database::getExp(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getExpSQL = "SELECT rhs FROM expression;";
    sqlite3_exec(dbConnection, getExpSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a subPattern into the database
void Database::insertSubPattern(string procedureName,string stmtNum , string fullExp, string partExp) {
    string insertExpSQL = "INSERT INTO pattern ('stmtNum','lhs','partExp','procedureName') VALUES ('" + stmtNum + "', '" + fullExp + "','" + partExp + "','" + procedureName + "');";
    sqlite3_exec(dbConnection, insertExpSQL.c_str(), NULL, 0, &errorMessage);
//    vector<string> varInSub;
//    Database::getVariableWithStmt(varInSub,stmtNum);
//    for(string s:varInSub){
//        string insertExpSQL = "INSERT INTO pattern ('stmtNum','lhs','partExp','procedureName') VALUES ('" + stmtNum + "', '" + fullExp + "','" + s + "','" + procedureName + "');";
//        sqlite3_exec(dbConnection, insertExpSQL.c_str(), NULL, 0, &errorMessage);
//    }

}

// method to get a subPattern from the database
void Database::getSubPattern(vector<string>& results,string stmt){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getExpSQL = "SELECT partExp FROM pattern where stmtNum = '"+ stmt +"';";
    sqlite3_exec(dbConnection, getExpSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a subPattern into the database
void Database::insertRelation(string relType,string lhs , string rhs, string hasRel) {
    cout << "         relType: "<<relType<<"  lhs:  "<<lhs<<"  rhs:  "<<rhs<<endl;

    string insertRelSQL = "INSERT INTO relationship ('relType','lhs','rhs','hasRel') VALUES ('" + relType + "', '" + lhs + "','" + rhs + "','" + hasRel + "');";
    sqlite3_exec(dbConnection, insertRelSQL.c_str(), NULL, 0, &errorMessage);
}
//
//method to get a relations from the database
void Database::getRel(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getRelSQL = "SELECT lhs FROM relationship UNION SELECT rhs FROM relationship;";
    sqlite3_exec(dbConnection, getRelSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

//method to get a pattern from the database
void Database::getPattern(vector<string>& results,string patternSql){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getRelSQL = patternSql;
    sqlite3_exec(dbConnection, getRelSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	NotUsed = 0;
	vector<string> dbRow;

	// argc is the number of columns for this row of results
	// argv contains the values for the columns
	// Each value is pushed into a vector.
	for (int i = 0; i < argc; i++) {
		dbRow.push_back(argv[i]);
	}

	// The row is pushed to the vector for storing all rows of results 
	dbResults.push_back(dbRow);

	return 0;
}
