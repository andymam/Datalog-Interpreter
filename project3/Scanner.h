#pragma once
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include "Token.h"

using namespace std;

class Scanner {
private:
    string input;
    int line = 1;
    vector<Token> tokens;


public:
    Scanner(const string &input) : input(input), line(1) { }

    vector<Token> scanToken() {

        while(!input.empty()) {
            Token this_token;
            int index = 0;
            string value = "";

            switch (input.at(0)) {

                case('\n'):
                    line++;
                    break;

                case ',':
                    this_token = {COMMA, ",", line};
                    break;

                case '.':
                    this_token = {PERIOD, ".", line};
                    break;

                case '?':
                    this_token = {Q_MARK, "?", line};
                    break;

                case '(':
                    this_token = {LEFT_PAREN, "(", line};
                    break;

                case ')':
                    this_token = {RIGHT_PAREN, ")", line};
                    break;

                case ':':
                    input = input.substr(1);
                    if (!input.empty() && input.at(0) == '-') {
                        this_token = {COLON_DASH, ":-", line};
                    } else {
                        this_token = {COLON, ":", line};
                        input.insert(0, "a");
                    }
                    break;

                case '*':
                    this_token = {MULTIPLY, "*", line};
                    break;

                case '+':
                    this_token = {ADD, "+", line};
                    break;

                case 'S':
                    if (isKeyWord(input, "Schemes")) {
                        this_token = {SCHEMES, "Schemes", line};
                        input = input.substr(6);
                    } else {
                        goto Default;
                    }
                    break;

                case 'F':
                    if (isKeyWord(input, "Facts")) {
                        this_token = {FACTS, "Facts", line};
                        input = input.substr(4);
                    } else {
                        goto Default;
                    }
                    break;

                case 'R':
                    if (isKeyWord(input, "Rules")) {
                        this_token = {RULES, "Rules", line};
                        input = input.substr(4);
                    } else {
                        goto Default;
                    }
                    break;

                case 'Q':
                    if (isKeyWord(input, "Queries")) {
                        this_token = {QUERIES, "Queries", line};
                        input = input.substr(6);
                    } else {
                        goto Default;
                    }
                    break;

                case '\'':
                    index = checkString(input.substr(1));
                    if (index == -1) {
                        this_token = {UNDEFINED, input, line};

                        while (!input.empty()) {
                            if (input.at(0) == '\n') {
                                line++;
                            }
                            input = input.substr(1);
                        }
                        input = "a";
                    }
                    else {
                        this_token = {STRING, input.substr(0, index + 2), line };
                        input = input.substr(index + 1);
                    }
                    break;

                case '#': // single line comments
                    while (!input.empty() && input.at(0) != '\n') {
                        string str(1, input.at(0));
                        value = value.append(str);
                        input = input.substr(1);
                    }

                    this_token = {COMMENT, value, line };
                    input.insert(0, "z");
                    break;

                Default:
                default:
                    if (isalpha(input.at(0))) {
                        string id;

                        while ( !input.empty() && !isspace(input.at(0)) && ( isalpha(input.at(0)) || isdigit(input.at(0)) )) {
                            string letter(1, input.at(0));
                            id = id.append(letter);
                            input = input.substr(1);
                        }
                        input.insert(0, "a");
                        this_token = {ID, id, line};
                    }
                    else {
                        string und_val(1, input.at(0));
                        this_token = {UNDEFINED, und_val, line};
                    }
                    break;
            }
            if(!isspace(input.at(0))) {
                if (this_token.getType() != COMMENT) {
                    tokens.push_back(this_token);
                }
            }
            input = input.substr(1, input.length());
        }
        Token endToken(EOFILE, "", line);
        tokens.push_back(endToken);

        return tokens;
    }

    bool isKeyWord(string str_check, string key) {
        while (!str_check.empty()) {

            if (!str_check.empty() && key.empty()) {
                if ( isspace(str_check.at(0)) || str_check.at(0) == ':') { // is keyword
                    return true;
                }
                else {
                    return false;
                }
            } else if (str_check.at(0) == key.at(0)) {
                str_check = str_check.substr(1);
                key = key.substr(1);
            } else {
                return false;
            }
        }

        if (key.empty()) {
            return true;
        } else {
            return false;
        }
    }

    int checkString(string str_check) {
        if (str_check.find('\'') == string::npos) {
            return -1;
        } else {
            return str_check.find('\'');
        }
    }
};