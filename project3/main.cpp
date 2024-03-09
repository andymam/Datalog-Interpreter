#include "Tuple.h"
#include "Scheme.h"
#include <vector>
#include "Relation.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
#include "fstream"
#include "Token.h"
#include <string>


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

    DatalogProgram datalog = parser.getDatalog();
    Interpreter interpreter(datalog);

    interpreter.evaluateQueries();

    return 0;
}

//    g++ -std=c++17 main.cpp
