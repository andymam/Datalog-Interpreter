#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOFILE
};

class Token{
private:
    TokenType type;
    string value;
    int lineNumber;

public:
    Token(TokenType type, string value, int lineNumber) : type(type), value(value), lineNumber(lineNumber){
        this->type = type;
        this->value = value;
        this->lineNumber = lineNumber;
    }

    string typeName(TokenType type) const {
        switch(type){
//            case COMMA: return "COMMA";
//            case PERIOD: return "PERIOD";
//            case Q_MARK return "Q_MARK";
//            case LEFT_PAREN: return "LEFT_PAREN";
//            case RIGHT_PAREN: return "RIGHT_PAREN";
//            case COLON: return "COLON";
//            case COLON_DASH: return "COLON_DASH";
//            case MULTIPLY: return "MULTIPLY";
//            case ADD: return "ADD";
//            case SCHEMES: return "SCHEMES";
//            case FACTS: return "FACTS";
//            case RULES: return "RULES";
//            case QUERIES: return "QUERIES";
//            case ID: return "ID";
//            case STRING: return "STRING";
//            case COMMENT: return "COMMENT";
//            case UNDEFINED: return "UNDEFINED";
//            case EOFILE: return "EOF";
//            default: return "uhhhhhhh";

            case 0: return "COMMA";
            case 1: return "PERIOD";
            case 2: return "Q_MARK";
            case 3: return "LEFT_PAREN";
            case 4: return "RIGHT_PAREN";
            case 5: return "COLON";
            case 6: return "COLON_DASH";
            case 7: return "MULTIPLY";
            case 8: return "ADD";
            case 9: return "SCHEMES";
            case 10: return "FACTS";
            case 11: return "RULES";
            case 12: return "QUERIES";
            case 13: return "ID";
            case 14: return "STRING";
            case 15: return "COMMENT";
            case 16: return "UNDEFINED";
            case 17: return "EOF";
            default: return "uhhhhhhh";
        }
    }

    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << lineNumber << ")";
        return out.str();
    }
};