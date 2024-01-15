#pragma once
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

enum TokenType {
  COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
  ADD, SCHEMES, FACTS, RULES, QUERIES
};

class Token {
    private:
        TokenType type;
        string value;
        int lineNumber;

    public:
        Token(TokenType type, string value, int lineNumber) : type(type), value(value), lineNumber(lineNumber) {}

        string toString() const {
          stringstream out;
          out << "(" << type << "," << "\"" << value << "\"" << "," << lineNumber << ")";
          return out.str();
        }
};

int main() {
    Token t = Token(COMMA, ",", 2);
    cout << t.toString() << endl;
}
