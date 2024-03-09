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

        evaluateSchemes();
        evaluateFacts();
    }

    void evaluateQueries() {
        for (unsigned int i = 0; i < queries.size(); ++i) {
            vector<string> queryVector = queries.at(i).getParamStrings();
            string predName = queries.at(i).getName();
            cout << queries.at(i).getName() << '(';

            for (unsigned int j = 0; j < queryVector.size(); ++j) {
                cout << queryVector.at(j);
                if (j < queryVector.size() - 1) {
                    cout << ',';
                } else {
                    cout << ")? ";
                }
            }

            evaluateUnoQuery(queryVector, predName);
        }
    }

    Relation evaluateUnoQuery(vector<string> queryVector, string predicateName) {
        Relation relation = database.at(predicateName);
        map<string, int> variables;
        vector<string> varNames;

        for (unsigned int i = 0; i < queryVector.size(); ++i) {
            if (queryVector.at(i).at(0) == '\'') {
                relation = relation.select(i, queryVector.at(i));
            } else {
                if (variables.find(queryVector.at(i)) != variables.end()) {
                    relation = relation.select(i, variables.at(queryVector.at(i)));
                } else {
                    variables.insert(make_pair(queryVector.at(i), i));
                    varNames.push_back(queryVector.at(i));
                }
            }
        }
        if (relation.getTuplesLength() > 0) {
            cout << "Yes(" << relation.getTuplesLength() << ')' << endl;
        } else {
            cout << "No" << endl;
        }

        relation = relation.project(variables, varNames);
        relation = relation.rename(varNames);

        if (!relation.schemeBeEmpty()) {
            cout << relation.printTuples();
        }
        return relation;
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
            database.insert(pair<string, Relation>(schemeName, relation));
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