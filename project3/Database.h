//
// Created by Andy Mam on 3/6/24.
//

#include <string>
#include <map>
#include "Relation.h"

#ifndef CS236_DATABASE_H
#define CS236_DATABASE_H

class Database : public map<string, Relation> {
public:
    Database() {};

};


#endif //CS236_DATABASE_H
