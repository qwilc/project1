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
    DatalogProgram() {};
    std::string toString();

    std::vector<Predicate*> getSchemes() {return schemes;}
    std::vector<Predicate*> getFacts() {return facts;}
    std::vector<Predicate*> getQueries() {return queries;}
    std::vector<Rule*> getRules() {return rules;}
    std::set<std::string> getDomain() {return domain;}

    void addScheme(Predicate* scheme) {schemes.push_back(scheme);}
    void addFact(Predicate* fact) {facts.push_back(fact);}
    void addQuery(Predicate* query) {queries.push_back(query);}
    void addRule(Rule* rule) {rules.push_back(rule);}
    void addToDomain(std::string string) {domain.insert(string);}
};


#endif //PROJECT1_DATALOGPROGRAM_H
