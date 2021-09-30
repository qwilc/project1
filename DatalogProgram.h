//
// Created by qgwil on 9/28/2021.
//

#ifndef PROJECT1_DATALOGPROGRAM_H
#define PROJECT1_DATALOGPROGRAM_H

#include <vector>
#include <set>
#include <string>
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string> domain;

public:
    std::string toString();
    std::vector<Predicate*> getSchemes() {return schemes;}
    std::vector<Predicate*> getFacts() {return facts;}
    std::vector<Predicate*> getQueries() {return queries;}
    std::vector<Rule*> getRules() {return rules;}
    std::set<std::string> getDomain() {return domain;}
};


#endif //PROJECT1_DATALOGPROGRAM_H
