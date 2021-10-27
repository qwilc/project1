//
// Created by qgwil on 10/22/2021.
//

#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include <set>
#include "Tuple.h"
#include "Header.h"

class Relation {
private:
    std::string name;
    Header* header;
    std::set<Tuple> tuples;
public:
    Relation(const std::string& name, Header* header) {
        this->name = name;
        this->header = header;
    }

    void AddTuple(const Tuple& newTuple) {
        tuples.insert(newTuple);
    }
    std::string GetName() {
        return name;
    }
    Header* GetHeader() {
        return header;
    }
    std::set<Tuple> GetTuples() {
        return tuples;
    }
    //GetTuple?
    //Relation Select(position, value)
    //Relation Select(position, position)
    //Relation Project(list of positions)
    //Relation Rename(Header hewHeader)
};


#endif //PROJECT1_RELATION_H
