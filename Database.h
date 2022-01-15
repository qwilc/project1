//
// Created by qgwil on 10/22/2021.
//

#ifndef PROJECT1_DATABASE_H
#define PROJECT1_DATABASE_H

#include<map>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation*> relations;
public:
    void AddRelation(Relation* relation);

    std::map<std::string, Relation*> GetRelations();
};


#endif //PROJECT1_DATABASE_H
