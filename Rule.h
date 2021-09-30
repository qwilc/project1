//
// Created by qgwil on 9/29/2021.
//

#ifndef PROJECT1_RULE_H
#define PROJECT1_RULE_H

#include "Predicate.h"
#include <vector>
#include <string>

class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
public:
    std::string toString();
};


#endif //PROJECT1_RULE_H
