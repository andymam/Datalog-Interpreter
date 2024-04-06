#pragma once
#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"
#include <map>
#include <algorithm>
using namespace std;


class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation() { }

    Relation(const string& name, const Scheme& scheme)
            : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    int getTuplesLength() {
        return tuples.size();
    }

    set<Tuple> getTuples() {
        return tuples;
    }

    Scheme getScheme() {
        return scheme;
    }

    bool schemeBeEmpty() {
        return scheme.empty();
    }

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto &tuple : tuples) {
            if (tuple[index] == value) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation select(int pos1, int pos2) const {
        Relation result(name, scheme);
        for (auto &tuple : tuples) {
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

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
                         const Tuple& leftTuple, const Tuple& rightTuple) {
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string &leftName = leftScheme.at(leftIndex);
            const string &leftValue = leftTuple.at(leftIndex);
            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);

                if ((leftName == rightName) && (leftValue != rightValue)) {
                    return false;
                }
            }
        }
        return true;
    }

    Relation join(const Relation& right) {
        const Relation& left = *this;
        Scheme newScheme = joinSchemes(right);
        Relation result(name, newScheme);

        for (const Tuple& leftTuple : left.tuples) {
            for (const Tuple& rightTuple : right.tuples) {
                if (joinable(left.scheme, right.scheme, leftTuple, rightTuple)) {
                    Tuple newTuple;
                    newTuple = joinTuples(newScheme, left.scheme, right.scheme, leftTuple, rightTuple);
                    result.addTuple(newTuple);
                }
            }
        }
        return result;
    }

    Scheme joinSchemes(const Relation &right) {
        const Relation &left = *this;
        const Scheme leftScheme = left.scheme;
        const Scheme rightScheme = right.scheme;

        Scheme otherNewScheme = leftScheme;

        for (unsigned int i = 0; i < rightScheme.size(); i++) {
            if (find(leftScheme.begin(), leftScheme.end(), rightScheme.at(i)) == leftScheme.end()) {
                otherNewScheme.push_back(rightScheme.at(i));
            }
        }
        return otherNewScheme;
    }

    Tuple joinTuples(const Scheme &joinedScheme, const Scheme &leftScheme, const Scheme &rightScheme, const Tuple &leftTuple, const Tuple &rightTuple) {
        Tuple result;
        for (auto &scheme : joinedScheme) {
            bool in = false;
            for (unsigned int i = 0; i < leftScheme.size(); i++) {
                if (scheme == leftScheme.at(i)) {
                    in = true;
                    result.push_back(leftTuple.at(i));
                    break;
                }
            }
            if (!in) {
                for (unsigned int i = 0; i < rightScheme.size(); i++) {
                    if (scheme == rightScheme.at(i)) {
                        in = true;
                        result.push_back(rightTuple.at(i));
                        break;
                    }
                }
            }
        }
        return result;
    }

    void unite(const Relation &right) {
        Relation relation = *this;
        Scheme scheme = relation.scheme;
        set<Tuple> leftTuples = relation.tuples;
        for (const Tuple &tuple : right.tuples) {
            if (leftTuples.find(tuple) == leftTuples.end()) {
                addTuple(tuple);
                cout << " " << tuple.toString(scheme) << endl;
            }
        }
    }
};

