//
// Created by Andy Mam on 2/28/24.
//
#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "Scheme.h"

using namespace std;


class Tuple : public vector<string> {

public:

    Tuple(vector<string> values) : vector<string>(values) { }

    string toString(const Scheme& scheme) const {
        stringstream out;
        for (size_t i = 0; i < size(); ++i) {
            out << scheme.at(i) << "=" << at(i);
            if (i < size() - 1)
                out << ", ";
        }
        return out.str();
    }
};