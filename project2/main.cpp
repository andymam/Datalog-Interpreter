#include <fstream>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) {

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