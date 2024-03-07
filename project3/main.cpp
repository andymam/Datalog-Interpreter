#pragma once
#include "Tuple.h"
#include <iostream>
#include "Scheme.h"
#include <vector>
#include "Relation.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"


using namespace std;

int main(int argc, char *argv[]) {
    ifstream inFile;
    inFile.open(argv[1]);
    stringstream ss;
    ss << inFile.rdbuf();
    string input = ss.str();
    inFile.close();

    Scanner scanner(input);
    vector<Token> tokens = scanner.scanToken();
    Parser parser(tokens);
    parser.parse();

    DatalogProgram datalogProgram = parser.getDatalogProgram();
    Interpreter interpreter(datalogProgram);

    interpreter.evaluateQueries();

    return 0;
}

//    g++ -std=c++17 main.cpp
