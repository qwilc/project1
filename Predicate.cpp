//
// Created by qgwil on 9/29/2021.
//

#include "Predicate.h"
#include <sstream>

std::string Predicate::toString() {
    std::stringstream output;

    output << id << "(";
    output << parameters.at(0)->toString();

    for(int i = 1; i < parameters.size(); i++) {
        output << "," << parameters.at(i)->toString();
    }

    output << ")";

    return output.str();
}
