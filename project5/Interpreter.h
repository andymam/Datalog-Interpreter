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
#include "Graph.h"
#include "Rule.h"

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

    static Graph makeGraph(const vector<Rule> &rules) {
        Graph graph(rules.size());
        for (unsigned fromRuleID = 0; fromRuleID < rules.size(); fromRuleID++) {
            Rule fromRule = rules[fromRuleID];
//             cout << "from rule R" << fromRuleID << ": " << fromRule.toString() << endl;

             for (unsigned predID = 0; predID < fromRule.getBodySize(); predID++) {
                 Predicate bodyPredicate = fromRule.getBodyPred(predID);
//                 cout << "from body predicate: " << bodyPredicate.toString() << endl;

                 for (unsigned toRuleID = 0; toRuleID < rules.size(); toRuleID++) {
                     Rule toRule = rules[toRuleID];
//                     cout << "to rule R" << toRuleID << ": " << toRule.toString() << endl;

                     if (bodyPredicate.getName() == toRule.getHead().getName()) {
                         graph.addEdge(fromRuleID, toRuleID);
//                         cout << "dependency found: (" << "R" << fromRuleID << ",R" << toRuleID << ")" << endl;
                     }
                 }
             }
        }
        return graph;
    }

    void evaluateQueries() {
        cout << "Query Evaluation" << endl;
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

    Relation evaluatePredicate(Predicate pred) {
        Relation relation = database.at(pred.getName());
        map<string, int> variables;
        vector<string> variableNames;

        for (unsigned int i = 0; i < pred.getParameters().size(); i++) {
            Parameter parameter = pred.getParameters().at(i);
            if (parameter.getName().at(0) == '\'') {
                relation = relation.select(i, parameter.getName());
            } else {
                if (variables.find(parameter.getName()) != variables.end()) {
                    relation = relation.select(i, variables.at(parameter.getName()));
                } else {
                    variables.insert(pair<string, int>(parameter.getName(), i));
                    variableNames.push_back(parameter.getName());
                }
            }
        }
        relation = relation.project(variables, variableNames);
        relation = relation.rename(variableNames);
        return relation;
    }


    void evaluateRules() {
        int runs = 0;
        int preSize;
        int postSize;

        cout << "Rule Evaluation" << endl;

        do {
            preSize = database.getSize();
            for (auto &rule : rules) {
                cout << rule.toString() << "." << endl;
                evaluateRule(rule);
            }
                postSize = database.getSize();
                runs++;
        } while (preSize != postSize);

        cout << endl;
        cout << "Schemes populated after " << runs << " passes through the Rules.";
        cout << endl << endl;
    }

    void evaluateRule(Rule rule) {
        vector<Relation> relations;
        map<string, int> variables;
        vector<string> variableNames;
        vector<Predicate> predicates = rule.getPredicateList();

        for (unsigned int i = 0; i < predicates.size(); i++) {
            Relation relation = evaluatePredicate(predicates.at(i));
            relations.push_back(relation);
        }

        Relation joinedRelation = relations.at(0);

        for (unsigned int i = 0; i < relations.size(); i++) {
            joinedRelation = joinedRelation.join(relations.at(i));
        }

        for (unsigned int i = 0; i < rule.getHead().getParameters().size(); i++) {
            for (unsigned j = 0; j < joinedRelation.getScheme().size(); j++) {
                Predicate predicate = rule.getHead();
                string parameterName = joinedRelation.getScheme().at(j);
                vector<Parameter> parameters = predicate.getParameters();
                Parameter otherParameter = parameters.at(i);
                string otherParameterName = otherParameter.getName();

                if (parameterName == otherParameterName) {
                    variables.insert(pair<string, int>(otherParameterName, j));
                    variableNames.push_back(otherParameterName);
                }
            }
        }
        Relation newRelation = joinedRelation.project(variables, variableNames);
        newRelation = newRelation.rename(variableNames);
        database.at(rule.getHead().getName()).unite(newRelation);
    }
};