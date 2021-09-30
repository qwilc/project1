//
// Created by qgwil on 9/29/2021.
//

#ifndef PROJECT1_PREDICATE_H
#define PROJECT1_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    std::string id;
    std::vector<Parameter*> parameters;
public:
    std::string toString();

};


#endif //PROJECT1_PREDICATE_H
