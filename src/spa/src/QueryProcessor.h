#pragma once

#include <string>
#include <vector>
#include "Database.h"

using namespace std;

class QueryProcessor {
public:
	// default constructor
	QueryProcessor();

	// destructor
	~QueryProcessor();

	// method for evaluating a query
    void checkClause(vector<string> &tokens,int &i);
    void patternParser();
    void suchThatParser();
	void evaluate(string query, vector<string>& results);
};