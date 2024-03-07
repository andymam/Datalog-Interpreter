#include <string>
#include <set>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"

#ifndef CS236_RELATION_H
#define CS236_RELATION_H

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

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (Tuple tuple : tuples) {
            if (tuple.at(index) == value) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    string toString() const {
        stringstream out;
        for (const auto& tuple : tuples) {
            out << tuple.toString(scheme) << endl;
        }
        return out.str();
    }

};

#endif //CS236_RELATION_H
