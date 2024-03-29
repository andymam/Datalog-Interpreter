//
// Created by Andy Mam on 3/6/24.
//

#include <string>
#include <map>
#include "Relation.h"
using namespace std;

#ifndef CS236_DATABASE_H
#define CS236_DATABASE_H

class Database : public map<string, Relation> {
public:
    Database() {};

    int getSize() {
        int size = 0;
        Database database = *this;
        for (auto i = database.begin(); i != database.end(); i++) {
            for (Tuple tuple : i->second.getTuples()) {
                size++;
            }
        }
        return size;
    }
};


#endif //CS236_DATABASE_H
