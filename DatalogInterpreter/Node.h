//
// Created by Andy Mam on 3/25/24.
//
#include <set>
#include <sstream>
#include <string>

using namespace std;

#ifndef CS236_NODE_H
#define CS236_NODE_H

class Node {

private:

    set<int> adjacentNodeIDs;
    bool visitedFlag;

public:

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    void setVisited(bool value) {
        visitedFlag = value;
    }

    bool visited() {
        return visitedFlag;
    }

    set<int> getEdges() {
        return adjacentNodeIDs;
    }

    string toString() {
        stringstream out;
        for (auto it = adjacentNodeIDs.begin(); it != adjacentNodeIDs.end(); ++it) {
            out << "R" << *it;
            if (next(it) != adjacentNodeIDs.end()) {
                out << ",";
            }
        }
        return out.str();
    }


};

#endif //CS236_NODE_H
