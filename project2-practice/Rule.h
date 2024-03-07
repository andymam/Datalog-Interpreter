#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Predicate.h"
using namespace std;

class Rule {
private:
    Predicate headPred;
    vector<Predicate> bodyPreds;

public:
    Rule() {}

    void setHeadPred(Predicate head) {
        headPred = head;
    }

    Predicate getHeadPred() {
        return headPred;
    }

    void addBodyPreds(Predicate bodyPred) {
        bodyPreds.push_back(bodyPred);
    }

    vector<Predicate> getPredList() {
        return bodyPreds;
    }

    string toString() {
        stringstream out;
        out << headPred.toString() << " :- ";
        for (size_t i = 0; i < bodyPreds.size(); i++) {
            out << bodyPreds.at(i).toString();
            if (i < bodyPreds.size() - 1) {
                out << ',';
            }
        }
        return out.str();
    }

};