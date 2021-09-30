//
// Created by qgwil on 9/29/2021.
//

#include "Rule.h"
#include <sstream>

std::string Rule::toString() {
    std::stringstream output;

    output << headPredicate->toString();
    output << bodyPredicates.at(0)->toString();

    for(int i = 1; i < bodyPredicates.size(); i++) {
        output << "," << bodyPredicates.at(i)->toString();
    }

    output << ").";

    return output.str();
}
