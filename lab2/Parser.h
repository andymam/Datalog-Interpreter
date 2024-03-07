#pragma once
#include <vector>
#include "Token.h"
#include <iostream>
#include "DatalogProgram.h"
#include <string>
#include <sstream>

using namespace std;

class Parser {
private:
    vector<Token> tokens;
    DatalogProgram datalog;

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }

    TokenType tokenType() const {
        return tokens.at(0).getType();
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }

    DatalogProgram getDatalog() {
        return datalog;
    }

    void parse() {
        try {
            parseDatalog();
            printSuccess();
        } catch (Token token) {
            throwError(token);
        }
    }

    void throwError(Token token) {
        cout << "error" << endl;
        cout << "  " << token.toString() << endl;
    }

    void printSuccess() {
        cout << "Success!" << endl;
        cout << datalog.printSchemes() << endl;
        cout << datalog.printFacts() << endl;
        cout << datalog.printQueries() << endl;
        cout << datalog.printRules() << endl;
        cout << datalog.printDomain() << endl;
    }

    void parseDatalog() {

    }

    void match(TokenType t) {
        // cout << "match: " << t << endl;
        if (t == tokenType()) {
            advanceToken();
        } else {
            throwError();
        }
    }

    void parse() {

    }

    void idList(Predicate &predicate) {
        if (tokenType() == COMMA) {
            match(COMMA);

            Parameter parameter(tokens.at(0).getValue());
            predicate.addParameter(parameter);

            match(ID);
            idList(predicate);
        } else {
            // lambda
        }
    }

    void scheme() {
        if (tokenType() == ID) {

            match(ID);
            match(LEFT_PAREN);

            Predicate predicate(tokens.at(0).getValue());
            Parameter parameter(tokens.at(0).getValue());

            match(ID);
            idList(predicate);
            match(RIGHT_PAREN);
            datalog.addScheme(predicate);
        } else {
            throw tokens.at(0);
        }
    }


};