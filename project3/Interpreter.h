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
    vector<Rule> rules;
    set<string> domain;

public:
    Interpreter() {}
    Interpreter(DatalogProgram datalog) {
    datalogProgram = datalog;
    schemes = datalog.getSchemes();
    facts = datalog.getFacts();
    queries = datalog.getQueries();
    rules = datalog.getRules();
    domain = datalog.getDomain();
    }

    void evaluateQueries() {

    }

    void evaluateUnoQuery() {

    }

    void evaluateSchemes() {
        for (size_t i = 0; i < schemes.size(); i++) {
            Scheme scheme;
            string schemeName = schemes.at(i).getName();
            vector<Parameter> parameters = schemes.at(i).getParameters();

            for (size_t j = 0; j < parameters.size(); j++) {
                string value = parameters.at(j).getName();
                scheme.push_back(value);
            }

            Relation relation(schemeName, scheme);
            database.insert(make_pair(schemeName, relation));
        }

    }

    void evaluateFacts() {
        for (size_t i = 0; i < facts.size(); i++) {
            Tuple tuple;
            string predName = facts.at(i).getName();
            vector<Parameter> factParams = facts.at(i).getParameters();

            for (size_t j = 0; j < factParams.size(); j++) {
                string value = factParams.at(j).getName();
                tuple.push_back(value);
            }

            database.at(predName).addTuple(tuple);
        }
    }

//    void evaluateRules() {
//
//    }


};