#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"

using namespace std;

class Predicate {
private:
    string name;
    vector<Parameter> parameters;

public:
    Predicate() { }
    Predicate(string name) : name(name) { }

    void addParameter(Parameter parameter) {
        parameters.push_back(parameter);
    }

    void setName(string newName) {
        name = newName;
    }

    string getName() {
        return name;
    }

    vector<Parameter> getParameters() {
        return parameters;
    }

    vector<string> getParamStrings() {
        vector<string> paramStrings;
        for (auto &param : parameters) {
            paramStrings.push_back(param.getName());
        }
        return paramStrings;
    }


    string toString() {
        stringstream out;
        out << name << '(';
        for (size_t i = 0; i < parameters.size(); i++) {
            out << parameters.at(i).getName();
            if (i < parameters.size() - 1) { out << ','; }
        }
        out << ')';

        return out.str();
    }
};
