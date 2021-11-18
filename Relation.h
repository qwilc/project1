//
// Created by qgwil on 10/22/2021.
//

#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include <set>
#include <sstream>
#include <algorithm>
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
        for(const Tuple& tuple : tuples) {
            if(!header->GetAttributes().empty()) {
                output << "  ";
            }
            for(unsigned int i = 0; i < header->GetAttributes().size(); i++) {
                output << header->GetAttributes()[i] << "=" << tuple.GetValues()[i];
                if (i + 1 < header->GetAttributes().size()) {
                    output << ", ";
                }
                else {
                    output << "\n";
                }
            }
        }
        return output.str();
    }

    void AddTuple(const Tuple& newTuple) {
        tuples.insert(newTuple);
    }
    void SetTuples(std::set<Tuple> newTuples) {
        this->tuples = newTuples;
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
        Relation newRelation(this->name, this->header);

        for(const Tuple& tuple : tuples) {
            if(tuple.GetValues()[index] == value) {
                newRelation.AddTuple(tuple);
            }
        }

        return newRelation;
    }
    Relation Select(int idx1, int idx2) {
        Relation newRelation(this->name, this->header);

        for(const Tuple& tuple : tuples) {
            if(tuple.GetValues()[idx1] == tuple.GetValues()[idx2]) {
                newRelation.AddTuple(tuple);
            }
        }

        return newRelation;
    }
    Relation Project(std::vector<unsigned int> indices) {
        std::vector<std::string> attributes;
        for(int i : indices) { //TODO: is there a way to combine the for loops?
            attributes.push_back(header->GetAttributes()[i]);
        }

        Relation newRelation(this->name, new Header(attributes));

        for(const Tuple& tuple : tuples) {
            std::vector<std::string> newValues;
            for(int i : indices) {
                newValues.push_back(tuple.GetValues()[i]);
            }
            newRelation.AddTuple(Tuple(newValues));
        }

        return newRelation;
    }
    Relation Rename(const std::vector<std::string>& newHeader) {
        Relation newRelation(this->name, new Header(newHeader));
        newRelation.SetTuples(this->tuples);
        return newRelation;
    }

    Relation Join(Relation* r2) {
        std::vector<std::pair<unsigned int, unsigned int>> overlapCols;
        std::vector<unsigned int> uniqueCols;
        std::vector<std::string> newHeader = joinHeaders(r2, overlapCols, uniqueCols);
        Relation newRelation("Joined Relation", new Header(newHeader));

        for(const Tuple& t1 : tuples) {
            for(const Tuple& t2 : r2->GetTuples()) {
                if(isJoinable(t1, t2, overlapCols)) {
                    newRelation.AddTuple(combineTuples(t1, t2, uniqueCols));
                }
            }
        }
        return newRelation;
    }

    std::vector<std::string> joinHeaders(Relation* r2, std::vector<std::pair<unsigned int, unsigned int>>& overlapCols, std::vector<unsigned int>& uniqueCols) {
        std::vector<std::string> r2Attributes = r2->GetHeader()->GetAttributes();
        std::vector<std::string> newAttributes = this->GetHeader()->GetAttributes();

        for(unsigned int i = 0; i < r2Attributes.size(); i++) {
            unsigned int idx = find(newAttributes.begin(), newAttributes.end(), r2Attributes.at(i)) - newAttributes.begin();
            if(idx == newAttributes.size()) {
                newAttributes.push_back(r2Attributes.at(i));
                uniqueCols.push_back(i);
            }
            else {
                std::pair<unsigned int, unsigned int> cols = {idx, i};
                overlapCols.push_back(cols);
            }
        }

        return newAttributes;
    }

    bool isJoinable(const Tuple& t1, const Tuple& t2, const std::vector<std::pair<unsigned int, unsigned int>>& overlapCols) {
        std::vector<std::string> vec1 = t1.GetValues();
        std::vector<std::string> vec2 = t2.GetValues();

        for(std::pair<unsigned int, unsigned int> pair : overlapCols) {
            if(vec1.at(pair.first) != vec2.at(pair.second)) {
                return false;
            }
        }
        return true;
    }

    Tuple combineTuples(const Tuple& t1, const Tuple& t2, const std::vector<unsigned int>& uniqueCols) {
        std::vector<std::string> combinedVals = t1.GetValues();
        for(unsigned int idx : uniqueCols) {
            combinedVals.push_back(t2.GetValues().at(idx));
        }
        return Tuple(combinedVals);
    }

    void Unite(Relation* r2, bool& wasChanged) {
        for(Tuple tuple : r2->GetTuples()) {
            if(tuples.insert(tuple).second) {
                wasChanged = true;
                for(unsigned int i = 0; i < header->GetAttributes().size(); i++) {
                    std::cout << header->GetAttributes()[i] << "=" << tuple.GetValues()[i];
                    if (i + 1 < header->GetAttributes().size()) {
                        std::cout << ", ";
                    }
                    else {
                        std::cout << "\n";
                    }
                }
            }
        }
    }
};


#endif //PROJECT1_RELATION_H
