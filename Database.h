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
    void AddRelation(Relation* relation) {
        relations.insert(std::pair<std::string,Relation*> (relation->GetName(), relation));
    }
    std::map<std::string, Relation*> GetRelations() {
        return relations;
    }
};


#endif //PROJECT1_DATABASE_H
