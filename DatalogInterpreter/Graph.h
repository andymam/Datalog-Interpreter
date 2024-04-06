//
// Created by Andy Mam on 3/25/24.
//
#include <map>
#include <sstream>
#include <string>
#include "Node.h"
#include <stack>
#include <queue>

using namespace std;

#ifndef CS236_GRAPH_H
#define CS236_GRAPH_H

class Graph {

private:

    map<int,Node> nodes;
    vector<Node> visited;
    stack<int> postorder;

public:

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    Graph(map<int, Node> newNodes) : nodes(newNodes) {}

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    stack<int> getPostorder() {
        return postorder;
    }

    map<int, Node> getNodes() {
        return nodes;
    }

    string toString()
    {
        stringstream out;
        for (auto pair : nodes)
        {
            out << "R" << pair.first << ":" << pair.second.toString() << endl;
        }

        return out.str();
    }

    Graph reverseGraph() {
        map<int, Node> newNodes;
        for (auto &node : nodes) {
            int num = node.first;
            for (int edge : node.second.getEdges()) {
                newNodes[edge].addEdge(num);
            }
        }
        return Graph{newNodes};
    }

    void doDFSforest() {
        for (auto &node : nodes) {
            node.second.setVisited(false);
        }
        for (auto &node : nodes) {
            if (!node.second.visited()) {
                doDfs(node.second, node.first);
            }
        }
    }

    void doDfs(Node &node, int nodeID) {
        node.setVisited(true);
        for (auto &nodeEdge : node.getEdges()) {
            if (!nodes[nodeEdge].visited()) {
                doDfs(nodes[nodeEdge], nodeEdge);
            }
        }
        postorder.push(nodeID);
    }

    queue<set<int>> doSCCforest(stack<int> postorder) {
        queue<set<int>> trees;

        for (auto &node : nodes) {
            node.second.setVisited(false);
        }

        for (auto &node : nodes) {
            set<int> tree;
            if (!nodes[postorder.top()].visited()) {
                tree = doSccDfs(nodes[postorder.top()], postorder.top());
                trees.push(tree);
            }
            postorder.pop();
        }
        return trees;
    }

    set<int> doSccDfs(Node &node, int nodeID) {
        node.setVisited(true);
        set<int> tree;
        for (auto &edge : node.getEdges()) {
            if (!nodes[edge].visited()) {
                auto subtree = doSccDfs(nodes[edge], edge);
                tree.insert(subtree.begin(), subtree.end());
            }
        }
        tree.insert(nodeID);
        return tree;
    }
};

#endif //CS236_GRAPH_H