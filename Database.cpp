//
// Created by qgwil on 1/15/2022.
//

#include "Database.h"

void Database::AddRelation(Relation* relation) {
    relations.insert(std::pair<std::string,Relation*> (relation->GetName(), relation));
}
std::map<std::string, Relation*> Database::GetRelations() {
    return relations;
}