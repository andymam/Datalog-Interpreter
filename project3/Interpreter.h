//
// Created by Andy Mam on 3/6/24.
//
#pragma once
#include <iostream>
#include "sstream"
#include <vector>
#include "Relation.h"
#include "Database.h"
#include "DatalogProgram.h"
#include "Predicate.h"

using namespace std;

class Interpreter {

private:
    Database database;
    DatalogProgram datalogProgram;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Predicate> rules;

public:
//    Interpreter() {}
    Interpreter(DatalogProgram datalog) {
    datalogProgram = datalog;
    schemes = datalog.
    }

};