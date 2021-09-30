//
// Created by qgwil on 9/29/2021.
//

#ifndef PROJECT1_RULE_H
#define PROJECT1_RULE_H

#include "Predicate.h"
#include <vector>
#include <string>
#include <iostream>

class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
public:
    Rule(Predicate* headPredicate) {this->headPredicate = headPredicate;}
    std::string toString();
    void addBodyPredicate(Predicate* predicate) {bodyPredicates.push_back(predicate);}
};


#endif //PROJECT1_RULE_H
