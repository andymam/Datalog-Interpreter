#pragma once
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

enum TokenType {
  COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
  ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFILE
};

class Token {
    private:
        TokenType type;
        string value;
        int lineNumber;

    public:
        Token(TokenType type, string value, int lineNumber) : type(type), value(value), lineNumber(lineNumber) {}

        string typeName(TokenType type) const {
          switch (type) {
            case COMMA: return "COMMA";
            case PERIOD: return "PERIOD";
            case Q_MARK: return "Q_MARK";
            case LEFT_PAREN: return "LEFT_PAREN";
            case RIGHT_PAREN: return "RIGHT_PAREN";
            case COLON: return "COLON";
            case COLON_DASH: return "COLON_DASH";
            case MULTIPLY: return "MULTIPLY";
            case ADD: return "ADD";
            case SCHEMES: return "SCHEMES";
            case FACTS: return "FACTS";
            case RULES: return "RULES";
            case QUERIES: return "QUERIES";
            case ID: return "ID";
            case STRING: return "STRING";
            case COMMENT: return "COMMENT";
            case UNDEFINED: return "UNDEFINED";
            case EOFILE: return "EOF";
            default: return "uhhhhh";
          }
        }

        string toString() const {
          stringstream out;
          out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << lineNumber << ")";
          return out.str();
        }
};
