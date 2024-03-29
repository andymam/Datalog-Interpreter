//
// Created by Andy Mam on 3/25/24.
//
#include <map>
#include <sstream>
#include <string>
#include "Node.h"

using namespace std;

#ifndef CS236_GRAPH_H
#define CS236_GRAPH_H

class Graph {

private:

    map<int,Node> nodes;

public:

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    string toString() {
        stringstream out;
        for (auto pair : nodes) {
            out << "R" << pair.first << ":" << pair.second.toString() << endl;
        }
        return out.str();
    }
};

#endif //CS236_GRAPH_H
