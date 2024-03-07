#pragma once
#include <string>
#include <cctype>

#include "Token.h"

using namespace std;

class Scanner {
    private:
        string input;
        int line;



    public:
        Scanner(const string& input) : input(input) { }

    Token scanToken() {
        while (!input.empty() && isspace(input.at(0))) {
            input = input.substr(1);
        }
        if (!input.empty() && input.at(0) == ',') {
            TokenType type = COMMA;
            string value = ",";
            int line = 4;
            // Remove the comma character from the input
            input = input.substr(1);
            return Token(type, value, line);
        }
    }
};