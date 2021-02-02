#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include "sqlite3.h"

using namespace std;

// The Database has to be a static class due to various constraints.
// It is advisable to just add the insert / get functions based on the given examples.
class Database {
public:
	// method to connect to the database and initialize tables in the database
	static void initialize();

	// method to close the database connection
	static void close();

	// method to insert a procedure into the database
	static void insertProcedure(string procedureName);

    // method to insert a variable into the database
    static void insertVariable(vector<string> variableName,string procedureName);

    // method to insert a read value into the database
    static void insertRead(string readVar,string procedureName,string stmtNum);

    // method to insert a print value into the database
    static void insertPrint(string stmtNum, string procedureName);

    // method to insert a stmtType and stmt number into the database
    static void insertStmt(string stmtType, string procedureName, string stmtNum);

    // method to insert a Constant into the database
    static void insertConstant(string result, string procedureName);

    // method to insert a Assign into the database
    static void insertAssign(string procedureName, string stmtNum);

	// method to get all the procedures from the database
	static void getProcedures(vector<string>& results);

    // method to get all the variable from the database
	static void getVariables(vector<string>& results);

    // method to get all the reads from the database
    static void getReads(vector<string>& results);

    // method to get all the prints from the database
    static void getPrints(vector<string>& results);

    // method to get all the stmt from the database
    static void getStmt(vector<string>& results);

    // method to get all the constant from the database
    static void getConstant(vector<string>& results);

    // method to get all the Assign from the database
    static void getAssign(vector<string>& results);


private:
	// the connection pointer to the database
	static sqlite3* dbConnection; 
	// a vector containing the results from the database
	static vector< vector<string> > dbResults;
	// the error message from the database
	static char* errorMessage;
	// callback method to put one row of results from the database into the dbResults vector
	// This method is called each time a row of results is returned from the database
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};

