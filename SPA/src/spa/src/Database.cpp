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
                                    "\tvariableName VARCHAR(255) PRIMARY KEY,\n"
                                    "    procedureName VARCHAR(255)\n"
                                    ");";
    sqlite3_exec(dbConnection, createVariableTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing read table (if any)
    string dropReadTableSQL = "DROP TABLE IF EXISTS reads";
    sqlite3_exec(dbConnection, dropReadTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a reads table
    string createReadsTableSQL = "CREATE TABLE reads ( \n"
                                 "\treadVar VARCHAR(255) PRIMARY KEY,\n"
                                 "    stmtNum VARCHAR(255),\n"
                                 "    procedureName VARCHAR(255)\n"
                                 ");";
    sqlite3_exec(dbConnection, createReadsTableSQL.c_str(), NULL, 0, &errorMessage);

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
                                    "\tresult VARCHAR(255) PRIMARY KEY,\n"
                                    "    procedureName VARCHAR(255)\n"
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
void Database::insertVariable(vector<string> variableName,string procedureName) {
    for(int i = 0;i<variableName.size();i++){
        string insertVariableSQL = "INSERT INTO variables ('variableName','procedureName') VALUES ('" + variableName[i] + "','" + procedureName + "');";
        sqlite3_exec(dbConnection, insertVariableSQL.c_str(), NULL, 0, &errorMessage);
    }

}


// method to get all the variables from the database
void Database::getVariables(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getProceduresSQL = "SELECT variableName FROM variables;";
    sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}


// method to insert a readVar into the database
void Database::insertRead(string readVar, string procedureName, string stmtNum) {
    string insertReadSQL = "INSERT INTO reads ('readVar','stmtNum','procedureName') VALUES ('" + readVar + "','"+ stmtNum +"', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertReadSQL.c_str(), NULL, 0, &errorMessage);

}


void Database::getReads(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getReadsSQL = "SELECT readVar FROM reads;";
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
    string insertReadSQL = "INSERT INTO prints ('stmtNum','procedureName') VALUES ('"+ stmtNum +"', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertReadSQL.c_str(), NULL, 0, &errorMessage);
}


void Database::getPrints(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getReadsSQL = "SELECT stmtNum FROM prints;";
    sqlite3_exec(dbConnection, getReadsSQL.c_str(), callback, 0, &errorMessage);

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
    string getReadsSQL = "SELECT stmtNum FROM statements;";
    sqlite3_exec(dbConnection, getReadsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

//insertConstant
void Database::insertConstant(string result, string procedureName){
    string insertStmtSQL = "INSERT INTO constants ('result','procedureName') VALUES ('" + result + "', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertStmtSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::getConstant(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getReadsSQL = "SELECT result FROM constants;";
    sqlite3_exec(dbConnection, getReadsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

//insert Assign
void Database::insertAssign(string procedureName, string stmtNum){
    string insertStmtSQL = "INSERT INTO assigns ('stmtNum','procedureName') VALUES ('" + stmtNum + "', '" + procedureName + "');";
    sqlite3_exec(dbConnection, insertStmtSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::getAssign(vector<string>& results){
    // clear the existing results
    dbResults.clear();

    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getReadsSQL = "SELECT stmtNum FROM assigns;";
    sqlite3_exec(dbConnection, getReadsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

//
//// method to get all the variables from the database
//void Database::getVariables(vector<string>& results){
//    // clear the existing results
//    dbResults.clear();
//
//    // retrieve the variables from the procedure table
//    // The callback method is only used when there are results to be returned.
//    string getVariablesSQL = "SELECT variableName FROM variables;";
//    sqlite3_exec(dbConnection, getVariablesSQL.c_str(), callback, 0, &errorMessage);
//
//    // postprocess the results from the database so that the output is just a vector of variables names
//    for (vector<string> dbRow : dbResults) {
//        string result;
//        result = dbRow.at(0);
//        results.push_back(result);
//    }
//}


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
