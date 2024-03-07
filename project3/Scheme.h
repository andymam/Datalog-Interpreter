//
// Created by Andy Mam on 2/28/24.
//
#pragma once
#import <string>
#import <vector>

using namespace std;


class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) { }
    Scheme() : vector<string>(){};

};
