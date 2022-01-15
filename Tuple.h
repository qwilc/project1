//
// Created by qgwil on 10/22/2021.
//

#ifndef PROJECT1_TUPLE_H
#define PROJECT1_TUPLE_H
#include <vector>
#include <string>
#include <iostream>

class Tuple {
private:
    std::vector<std::string> values;

public:
    Tuple(const std::vector<std::string>& values);

    bool operator< (const Tuple& other) const;

    std::vector<std::string> GetValues() const;

    void Print();

};


#endif //PROJECT1_TUPLE_H
