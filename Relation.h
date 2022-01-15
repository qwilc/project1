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
    Relation(const std::string& name, Header* header);

    std::string toString();

    void AddTuple(const Tuple& newTuple);

    void SetTuples(std::set<Tuple> newTuples);

    std::string GetName();

    Header* GetHeader();

    std::set<Tuple> GetTuples();

    Relation Select(int index, const std::string& value);

    Relation Select(int idx1, int idx2);

    Relation Project(std::vector<unsigned int> indices);

    Relation Rename(const std::vector<std::string>& newHeader);

    Relation Join(Relation* r2);

    std::vector<std::string> joinHeaders(Relation* r2, std::vector<std::pair<unsigned int, unsigned int>>& overlapCols,
                                         std::vector<unsigned int>& uniqueCols);

    bool isJoinable(const Tuple& t1, const Tuple& t2, const std::vector<std::pair<unsigned int, unsigned int>>& overlapCols);

    Tuple combineTuples(const Tuple& t1, const Tuple& t2, const std::vector<unsigned int>& uniqueCols);

    void Unite(Relation* r2, bool& wasChanged);
};


#endif //PROJECT1_RELATION_H
