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
    Token () {type = UNDEFINED, value = "", lineNumber = 0;}
    Token(TokenType type, const string& value, int lineNumber)
            : type(type), value(value), lineNumber(lineNumber) {}


//            this->type = type;
//            this->value = value;
//            this->lineNumber = lineNumber;

    TokenType getType() const {
        return type;
    }

    string getValue() {
        return value;
    }

    string typeName(TokenType type) const {
        switch(type){
            case (COMMA): return "COMMA"; break;
            case (PERIOD): return "PERIOD"; break;
            case (Q_MARK): return "Q_MARK"; break;
            case (LEFT_PAREN): return "LEFT_PAREN"; break;
            case (RIGHT_PAREN): return "RIGHT_PAREN"; break;
            case (COLON): return "COLON"; break;
            case (COLON_DASH): return "COLON_DASH"; break;
            case (MULTIPLY): return "MULTIPLY"; break;
            case (ADD): return "ADD"; break;
            case (SCHEMES): return "SCHEMES"; break;
            case (FACTS): return "FACTS"; break;
            case (RULES): return "RULES"; break;
            case (QUERIES): return "QUERIES"; break;
            case (ID): return "ID"; break;
            case (STRING): return "STRING"; break;
            case (COMMENT): return "COMMENT"; break;
            case (UNDEFINED): return "UNDEFINED"; break;
            case (EOFILE): return "EOF"; break;
            default: return "uhhhhhhh"; break;
        }
        return "error";
    }

    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << lineNumber << ")";
        return out.str();
    }
};