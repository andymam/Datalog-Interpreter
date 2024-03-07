#include "Parser.h"
#include <vector>
#include <iostream>
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char* argv[1]) {

    ifstream inFile;
    inFile.open(argv[1]);
    stringstream ss;
    ss << inFile.rdbuf();
    string input = ss.str();
    inFile.close();

    Scanner scanner(input);
    Parser parser = scanner.scanToken();
    parser.parse();

    return 0;
}

//g++ -std=c++17 main.cpp
