//
// Created by qgwil on 10/22/2021.
//

#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include <set>
#include <sstream>
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

    std::string toString() {
        std::stringstream output;
        for(Tuple tuple : tuples) {
            for(unsigned int i = 0; i < header->GetAttributes().size(); i++) {
                output << header->GetAttributes()[i] << "=\'" << tuple.GetValues()[i] << "\'";
                if(i + 1 < header->GetAttributes().size()) {
                    output << ", ";
                }
            }
            output << "\n";
        }

        return output.str();
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
    Relation Select(int index, const std::string& value) {
        Relation newRelation("", this->header); //TODO: Does it matter what the name is? I don't add it to the map, right?

        for(const Tuple& tuple : tuples) {
            if(tuple.GetValues()[index] == value) {
                newRelation.AddTuple(tuple);
            }
        }

        return newRelation;
    }
    Relation Select(int idx1, int idx2) {
        Relation newRelation("", this->header);

        for(const Tuple& tuple : tuples) {
            if(tuple.GetValues()[idx1] == tuple.GetValues()[idx2]) {
                newRelation.AddTuple(tuple);
            }
        }

        return newRelation;
    }
    Relation Project(std::vector<int> indices) {
        std::vector<std::string> attributes;
        for(int i : indices) { //TODO: is there a way to combine the for loops?
            attributes.push_back(header->GetAttributes()[i]);
        }

        Relation newRelation("", new Header(attributes));

        for(const Tuple& tuple : tuples) {
            std::vector<std::string> newValues;
            for(int i : indices) {
                newValues.push_back(tuple.GetValues()[i]);
            }
            newRelation.AddTuple(Tuple(newValues));
        }

        return newRelation;
    }
    //Relation Rename(Header hewHeader)
};


#endif //PROJECT1_RELATION_H
