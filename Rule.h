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
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;

public:
    Rule(Predicate headPredicate) { //TODO: Should I not define functions here?
        this->headPredicate.setID(headPredicate.getID());
        this->headPredicate.addParameters(headPredicate.getParameters());
    }

    std::string toString();

    void addBodyPredicate(Predicate predicate) {bodyPredicates.push_back(predicate);}

    void addBodyPredicate(std::vector<Predicate> predicates) {
        bodyPredicates.insert(bodyPredicates.end(), predicates.begin(), predicates.end());
    }

    std::vector<Predicate> GetBodyPredicates() {return bodyPredicates;}

    Predicate GetHeadPredicate() {return headPredicate;}
};


#endif //PROJECT1_RULE_H
