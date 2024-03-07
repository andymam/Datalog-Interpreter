#pragma once
#include <string>
#include "Token.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Scanner {
private:
    string input;
    string value = "";
    int line = 1;
    int startOfLine = 0;
    ifstream infile;
    ofstream outfile;
    char c;
    char next;
    vector<Token> tokens;

public:
    Scanner(){}

    void scan(string fileName){
        infile.open(fileName.c_str());
        if(infile){
            while(infile.get(c)){
                scanToken();
            }
            addToken(EOFILE, line);

            cout << "Total Tokens = " << tokens.size() << endl;
        }

    }

    void scanToken(){
        while(isspace(c)){
            if (c == '\n'){
                line++;
            }
//            eatspace();
            infile.get(c);
            if(infile.eof()){
                break;
            }
        }
        switch (c){
            case ',':
                value = ",";
                addToken(COMMA, line);
                break;
            case '.':
                value = ".";
                addToken(PERIOD, line);
                break;
            case '?':
                value = "?";
                addToken(Q_MARK, line);
                break;
            case '(':
                value = "(";
                addToken(LEFT_PAREN, line);
                break;
            case ')':
                value = ")";
                addToken(RIGHT_PAREN, line);
                break;
            case ':':
                value = ":";
                next = infile.peek();
                if(next == '-'){
                    value = ":-";
                    addToken(COLON_DASH, line);
                    infile.get(c);
                }
                else{
                    addToken(COLON, line);
                }
                break;
            case '*':
                value = "*";
                addToken(MULTIPLY, line);
                break;
            case '+':
                value = "+";
                addToken(ADD, line);
                break;
            case '\'':
                addString();
                break;
            case '#':
                addComment();
                break;
            default:
                if(isalpha(c)){
                    addID();
                }
                else if(!infile.eof()){
                    value += c;
                    addToken(UNDEFINED, line);
                }
                break;

        }
    }
//
//    void eatspace() {
//        while (isspace(next)) {
//            infile.get(next);
//            line += (next == '\n');
//        }
//    }

    void addString(){
        bool end = false;
        value += c;
        startOfLine = line;
        while(end == false){
            if(infile.peek() == -1){
                addToken(UNDEFINED, startOfLine);
                end = true;
            }
            else{
                infile.get(c);
                switch(c){
                    case '\n':
                        line++;
                        value += c;
                        break;
                    case '\'':
                        value += c;
                        next = infile.peek();
                        if(next != '\''){
                            addToken(STRING, startOfLine);
                            end = true;
                        }
                        else{
                            infile.get(c);
                            value += c;
                        }
                        break;
                    default:
                        value += c;
                        break;
                }
            }
        }
    }

    void addComment(){
        value += c;
        startOfLine = line;

//        while (c != '\n' && !infile.eof()) {
//            infile.get(c);
//            value += c;
//        }
//        if (c == '\n') {
//            line++;
//        }
//        addToken(COMMENT, startOfLine);

        next = infile.peek();
        if(next != '|'){
            infile.get(c);
            while(c != '\n'){
                value += c;
                infile.get(c);
            }
            if(c == '\n'){
                line++;
            }
            addToken(COMMENT, startOfLine);
        }
        else{
            infile.get(c);
            value += c;
            infile.get(c);
            next = infile.peek();
            while((c != '|' || next != '#') && next != -1){
                if(c == '\n'){
                    line++;
                }
                value += c;
                infile.get(c);
                next = infile.peek();
            }
            if(c == '|' && next == '#'){
                value += c;
                infile.get(c);
                value += c;
                addToken(COMMENT, startOfLine);
            }
            else if(infile.eof()){
                line++;
                addToken(UNDEFINED, startOfLine);
            }
        }
    }

    void addID(){
        value += c;
        infile.get(c);
        while(isalnum(c)){
            value += c;
            infile.get(c);
        }
        if(value == "Schemes"){
            addToken(SCHEMES, line);
        }
        else if (value == "Facts"){
            addToken(FACTS, line);
        }
        else if (value == "Rules"){
            addToken(RULES, line);
        }
        else if (value == "Queries"){
            addToken(QUERIES, line);
        }
        else{
            addToken(ID, line);
        }
        scanToken();
    }

    void addToken(TokenType type, int lineNumber){
        Token newToken(type, value, lineNumber);
        tokens.push_back(newToken);
        cout << newToken.toString() << endl;
        value = "";
    }

};