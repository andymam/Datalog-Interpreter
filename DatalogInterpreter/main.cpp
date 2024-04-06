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
#include "Node.h"
#include "Graph.h"
#include "Rule.h"
#include <queue>

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


    vector<Rule> rules = datalog.getRules();
//    Graph graph = interpreter.makeGraph(rules);
    pair<Graph, Graph> graphPair = interpreter.makeGraph(rules);
    Graph normalGraph = graphPair.first;
    Graph reversedGraph = graphPair.second;
    cout << "Dependency Graph" << endl << normalGraph.toString() << endl;
    reversedGraph.doDFSforest();
    stack<int> postorder = reversedGraph.getPostorder();
    queue<set<int>> sccs = normalGraph.doSCCforest(postorder);

    cout << "Rule Evaluation" << endl;
    interpreter.evaluateRules(normalGraph, sccs);
    cout << endl;
    interpreter.evaluateQueries();

    return 0;
}

//    g++ -std=c++17 main.cpp
