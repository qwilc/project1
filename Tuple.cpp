//
// Created by qgwil on 1/15/2022.
//

#include "Tuple.h"

Tuple::Tuple(const std::vector<std::string>& values) {
    this->values = values;
}

bool Tuple::operator< (const Tuple& other) const {
    return values < other.values;
}

std::vector<std::string> Tuple::GetValues() const {
    return values;
}

void Tuple::Print() {
    for(std::string value : values) {
        std::cout << value << ", ";
    }
}