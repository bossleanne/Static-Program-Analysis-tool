#pragma once

#include <string>
#include <vector>
#include "sqlite3.h"
#include <iostream>
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
    static void insertVariable(string variableName,string stmtNum,string procedureName);

    // method to insert a read value into the database
    static void insertRead(string stmtNum,string procedureName);

    // method to insert a print value into the database
    static void insertPrint(string stmtNum, string procedureName);

    // method to insert a stmtType and stmt number into the database
    static void insertStmt(string stmtType, string procedureName, string stmtNum);

    // method to insert a Constant into the database
    static void insertConstant(string constantName,string stmtNum,string procedureName);

    // method to insert a Assign into the database
    static void insertAssign(string procedureName, string stmtNum);

    // method to insert a insertFollowS into the followStar database
    static void insertFollowS(string procedureName, string stmtBefore ,string stmtAfter);

    // method to insert a insertFollowS into the followStar database
    static void insertFollowStar(string procedureName, string stmtBefore ,string stmtAfter);

    // method to insert a values into the parents database
    static void insertParent(string procedureName,string parent , string child);

    // method to insert a values into the parentstar database
    static void insertParentStar(string procedureName,string parent , string child);

    // method to insert a Modifies into the database
    static void insertModifies(string procedureName,string stmtNum , string variable);

    // method to insert a Uses into the database
    static void insertUses(string procedureName,string stmtNum , string variable);

    // method to insert a Expression into the database
    static void insertExp(string procedureName,string stmtNum , string lhs, vector<string> postfix);

    // method to insert SubPattern into the database
    static void insertSubPattern(string procedureName,string stmtNum , string fullExp, string partExp);

    // method to insert calling into the database
    static void insertCall(string stmtNum,string procedureName,string calling);

    // method to insert realtionship into the database
    static void insertRelation(string relType,string lhs , string rhs, string hasRel);

    // method to get all the procedures from the database
	static void getProcedures(vector<string>& results);

    // method to get all the variable from the database
	static void getVariables(vector<string>& results);
    static void getVariableStmt(vector<string>& results);
    static void getVariableWithStmt(vector<string>& results,string stmtNum);

    // method to get all the reads from the database
    static void getReads(vector<string>& results);

    // method to get all the prints from the database
    static void getPrints(vector<string>& results);

    // method to get all the stmt from the database
    static void getStmt(vector<string>& results);

    // method to get all the constant from the database
    static void getConstant(vector<string>& results);
    static void getConstantStmt(vector<string>& results);
    static void getConstantWithStmt(vector<string>& results,string stmtNum);

    // method to get all the Assign from the database
    static void getAssign(vector<string>& results);



    // method to get required the stmt type from the database
    static void getStmtType(vector<string>& results,string stmtType);



    // method to get all the While from the database
    static void getType(vector<string>& results,string type);


    //get parents SQL stmt
    static void getSon(vector<string>& results,string parent);
    static void getSonAll(vector<string>& results);
    static void getParent(vector<string>& results,string child);
    static void getParentAll(vector<string>& results);
    static void getParentStar(vector<string>& results,string son);
    static void getChildStar(vector<string>& results,string parent);
    static void getParentStarLR(vector<string>& results,string parent,string son);

    // method to get all the Modifies from the database
    static void getModifies(vector<string>& results,string lhs,string rhs);
    static void getModSql(vector<string>& results,string sql);

    // method to get all the Uses from the database
    static void getUses(vector<string>& results,string lhs,string rhs);
    static bool checkUses(string lhs,string rhs);
    static void getUsesSql(vector<string>& results,string sql);

    // method to get all the Expression from the database
    static void getExp(vector<string>& results);

    // method to get a subPattern from the database
    static void getSubPattern(vector<string>& results,string stmt);

    // method to get a subPattern from the database
    static void getRel(vector<string>& results);

    // all follows query
    static void getFollow(vector<string>& results,string sql);
    static void getFollowS(vector<string>& results,string lhs);
    static void getIsFollow(vector<string>& results,string lhs,string rhs);
    static string getFollowRhs(string stmtBefore);
    static string getFollowLhs(string stmtAfter);

    static void getFollowStarS(vector<string>& results,string currentStmt);
    static void getIsFollowStar(vector<string>& results,string lhs,string rhs);
    static string getFollowRhsStar(string stmtBefore);
    static void getFollowStar(vector<string>& results,string sql);
    static string getFollowLhsStar(string stmtAfters);

    // all parents query
    static void getParentS(vector<string>& results,string currentStmt);
    static void getIsParent(vector<string>& results,string lhs,string rhs);
    static void getParentSql(vector<string>& results,string sql);
    static void getParentLhs(vector <string> &results,string child);
    static void getParentRhs(vector <string> &results,string parent);

    //all parent star;
    static void getParentStarLhs(vector <string> &results,string child);
    static void getParentStarSql(vector<string>& results,string sql);
    static void getIsParentStar(vector<string>& results,string lhs,string rhs);

    //check the valid relation:
    static bool checkStmt(string lhs,string rhs,string sql);
    static bool checkFollow(string lhs,string rhs);
    static void emptyRel();
    static void getSql(vector<string>& results,string sql);
    static void getPattern(vector<string>& results,string patternSql);

    //get call
    static void getCallSql(vector<string>& results,string sql);
    static void insertCallStar(string stmtNum,string procedureName,string calling);
    static void getCallS(vector<string>& results,string call);


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

