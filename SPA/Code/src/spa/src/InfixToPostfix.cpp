//
// Created by Leanne on 20/2/21.
//


#include "InfixToPostfix.h"

using namespace std;

bool InfixToPostfix::isOptr(string s){
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^" || s == "=" || s == "!" || s == ">" || s == "<" || s == "==" ||
            s == ">=" || s == "<=" || s == "!=" || s == "&" || s == "|" ||
            s == "&&" || s == "||");
}

bool InfixToPostfix::isCal(string s){
    return ( s == "=" || s == ">" || s == "<" || s == "==" || s == "!" || s == "|" || s == "&" ||
            s == ">=" || s == "<=" || s == "!=");
}

bool InfixToPostfix::isOrAnd(string s){
    return (s == "&&" || s == "||");
}

bool InfixToPostfix::isScope(string s){
    return (s == "(" || s == ")");
}


int InfixToPostfix::priority(string c) {
    if (c == "+" || c =="-"){
        return 0;
    }
    else if (c == "*" || c =="/" || c =="%"){
        return 1;
    }
    else if (c == "^"){
        return 2;
    }
    return -1;
}

//Infix to Postfix
vector <string> InfixToPostfix::in_to_post(string expression) {
    vector <string> output;
    stack<string> optr;
    stack<string> opnd;

    Tokenizer tk;
    vector<string> tokens;
    tk.tokenize(expression, tokens);

    for(int i = 0; i<tokens.size();i++){
        //direct push operands into vector
        if(!isOptr(tokens.at(i)) && tokens.at(i) != "(" && tokens.at(i) != ")"){
            output.push_back(tokens.at(i));
        }

        //push the open ( to optr
        else if(tokens.at(i) == "("){
            optr.push(tokens.at(i));
        }

            //push the close ) to optr
        else if(tokens.at(i) == ")"){
            while(optr.top()!="("){
                output.push_back(optr.top());
                optr.pop();
            }
            optr.pop();
        }

            // pop the content
        else{
                if(optr.empty()){
                    optr.push(tokens.at(i));
                }
                else if(priority(tokens.at(i)) > priority(optr.top())){
                    optr.push(tokens.at(i));
                }
                else{
                    while (!optr.empty() && priority(tokens.at(i)) <= priority(optr.top()))
                    {
                        output.push_back(optr.top());
                        optr.pop();
                    }
                    optr.push(tokens.at(i));
                }
        }
    }

    //case end expression
    while(!optr.empty()){
        output.push_back(optr.top());
        optr.pop();
    }

    return output;
}

bool isOperand(char x)
{
    return (x >= 'a' && x <= 'z') ||
           (x >= 'A' && x <= 'Z');
}


// Get Infix for a given postfix
// expression
string getInfix(string exp)
{
    stack<string> s;

    for (int i=0; exp[i]!='\0'; i++)
    {
        // Push operands
        if (isOperand(exp[i]))
        {
            string op(1, exp[i]);
            s.push(op);
        }

            // We assume that input is
            // a valid postfix and expect
            // an operator.
        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push("(" + op2 + exp[i] +
                   op1 + ")");
        }
    }

    // There must be a single element
    // in stack now which is the required
    // infix.
    return s.top();
}

void InfixToPostfix::partialExp(string procedureName, int stmtNum, vector<string> expression) {

    vector<string> currentExp;
    vector<string> subPattern;
    vector<string> followBuffer;

    string subTree="";
    currentExp = expression;

    string exp = "";
    string sqlTemp = "";
    string assign = "";

    for (string s:expression){
        exp+=s;
    }
    sqlTemp = "SELECT assign FROM expression WHERE stmtNum = '"+to_string(stmtNum)+"';";
    Database::getPattern(followBuffer,sqlTemp);
    assign = followBuffer.at(0);
    for(int i = 0; i< currentExp.size();i++){
        if (InfixToPostfix::isOptr(currentExp[i])) {
            subTree = currentExp[i - 2] + " " + currentExp[i - 1] + " " + currentExp[i];
            Database::insertSubPattern(procedureName,to_string(stmtNum),assign,subTree);
            if (!currentExp.empty()) {
                //erase the pattern
                currentExp.erase(currentExp.begin() + (i - 2), currentExp.begin() + i + 1);\
                //insert the subTree as whole string into that index where erase take place.
                currentExp.insert( currentExp.begin() + (i-2),subTree);
            }
            i = 0;
        }
        subTree.clear();
    }
}