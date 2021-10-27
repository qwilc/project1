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
    Tuple(const std::vector<std::string>& values) { //TODO: Add values one at a time as we toString parameters?
        this->values = values;
    }
    bool operator< (const Tuple& other) {
        for(int i = 0; i < values.size(); i++) {
            if(values[i] > other.GetValues()[i]) {
                return false;
            }
        }
        return true;
    }
    std::vector<std::string> GetValues() const {
        return values;
    }
    void Print() {
        for(std::string value : values) {
            std::cout << value << ", ";
        }
    }

};


#endif //PROJECT1_TUPLE_H
