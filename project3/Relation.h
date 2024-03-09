#pragma once
#include <string>
#include <set>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"
#include <map>


class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme)
            : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    int getTuplesLength() {
        return tuples.size();
    }

    bool schemeBeEmpty() {
        return scheme.empty();
    }

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (Tuple tuple : tuples) {
            if (tuple.at(index) == value) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation select(int pos1, int pos2) const {
        Relation result(name, scheme);
        for (Tuple tuple : tuples) {
            if (tuple.at(pos1) == tuple.at(pos2)) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(map<string, int> indices, vector<string> projectedVars) {
        Relation result(name, projectedVars);
        for (auto &ogTuple : tuples) {
            vector<string> projectedTupleItems;
            vector<string> projectedTuple;
            for (unsigned int i = 0; i < projectedVars.size(); ++i) {
                int index = indices.at(projectedVars.at(i));
                projectedTuple.push_back(ogTuple.at(index));
            }
            result.addTuple(projectedTuple);
        }
        return result;
    }


    Relation rename(vector<string> variables) {
        Relation newRelation(name, variables);
        newRelation.tuples = tuples;
        return newRelation;
    }

    string printTuples() {
        stringstream output;
        for (auto &tuple : tuples) {
            vector<string> values = tuple;
            output << "  ";
            for (size_t index = 0; index < values.size(); ++index) {
                output << scheme.at(index) << '=' << values.at(index);
                if (index < values.size() - 1) {
                    output << ", ";
                }
            }
            output << endl;
        }
        return output.str();
    }


    string toString() const {
        stringstream out;
        for (const auto& tuple : tuples) {
            out << tuple.toString(scheme) << endl;
        }
        return out.str();
    }

};

