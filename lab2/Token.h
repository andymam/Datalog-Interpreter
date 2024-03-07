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
        Token(TokenType type, const string& value, int lineNumber)
        : type(type), value(value), lineNumber(lineNumber) {}


//            this->type = type;
//            this->value = value;
//            this->lineNumber = lineNumber;

        TokenType getType() const {
            return type;
        }

        string typeName(TokenType type) const {
            switch(type){
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