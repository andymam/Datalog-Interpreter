#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Predicate.h"

using namespace std;

class Rule
{
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;

public:
    Rule() { }
    Rule(Predicate head) : headPredicate(head) {}

    void setHead(Predicate head) {
        headPredicate = head;
    }

    Predicate getHead() {
        return headPredicate;
    }

    void addBodyPredicate(Predicate predicate) {
        bodyPredicates.push_back(predicate);
    }

    vector<Predicate> getPredicateList() {
        return bodyPredicates;
    }

    Predicate getBodyPred(int predID) {
        return bodyPredicates[predID];
    }


    int getBodySize() {
        return bodyPredicates.size();
    }

    string toString() {
        stringstream out;
        out << headPredicate.toString() << " :- ";
        for (size_t i = 0; i < bodyPredicates.size(); i++)
        {
            out << bodyPredicates.at(i).toString();
            if (i < bodyPredicates.size() - 1)
            {
                out << ',';
            }
        }
        return out.str();
    }
};
