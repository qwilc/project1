//
// Created by qgwil on 9/29/2021.
//

#include "Predicate.h"
#include <sstream>
#include <iostream>

std::string Predicate::toString() {
    std::stringstream output;

    output << id << "(";
    output << parameters.at(0).toString();

    for(unsigned int i = 1; i < parameters.size(); i++) {
        output << "," << parameters.at(i).toString();
    }

    output << ")";

    return output.str();
}

void Predicate::addParameters(std::vector<Parameter> newParameters) {
    this->parameters.insert(this->parameters.end(), newParameters.begin(), newParameters.end());
}
