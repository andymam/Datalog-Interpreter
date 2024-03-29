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

public:

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
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
