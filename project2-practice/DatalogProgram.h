#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
using namespace std;

class DatalogProgram {
    private:
        vector<Predicate> schemes;
        vector<Predicate> facts;
        vector<Predicate> queries;
        vector<Rule> rules;
        set<string> domain;

    public:
        DatalogProgram() {}

        void addScheme(Predicate predicate) {
            schemes.push_back(predicate);
        }
        void addFact(Predicate predicate) {
            facts.push_back(predicate);
        }
        void addQuery(Predicate predicate) {
            queries.push_back(predicate);
        }
        void addRule(Rule rule) {
            rules.push_back(rule);
        }
        void addDomain(Parameter parameter) {
            domain.insert(parameter.getName());
        }

        string printSchemes() {
            stringstream output;
            output << "Schemes" << '(' << schemes.size() << "):" << endl;
            for(size_t i = 0; i < schemes.size(); i++) {
                output << "  " << schemes.at(i).toString() << endl;
            }
            return output.str();
        }

        string printFacts() {
            stringstream output;
            output << "Facts" << '(' << facts.size() << "):" << endl;
            for (size_t i = 0; i < facts.size(); i++) {
                output << "  " << facts.at(i).toString()  << '.' << endl;
            }
            return output.str();
        }

        string printRules() {
            stringstream output;
            output << "Rules" << '(' << rules.size() << "):" << endl;
            for (size_t i = 0; i < rules.size(); i++) {
                output << "  " << rules.at(i).toString()  << '.' << endl;
            }
            return output.str();
        }

        string printQueries() {
            stringstream output;
            output << "Queries" << '(' << queries.size() << "):" << endl;
            for (size_t i = 0; i < queries.size(); i++) {
                output << "  " << queries.at(i).toString() << '?' << endl;
            }
            return output.str();
        }

        string printDomain() {
            stringstream output;
            output << "Domain" << '(' << domain.size() << "):" << endl;
            set<string>::iterator i;
            for (i = domain.begin(); i != domain.end(); i++) {
                Parameter parameter = *i;
                output << "  " << parameter.getName() << endl;
            }
            return output.str();
        }




};