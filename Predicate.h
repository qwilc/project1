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
    std::vector<Parameter> parameters;
public:
    std::string toString();

    void addParameter(Parameter parameter) {parameters.push_back(parameter);}
    void setID(std::string newID) { this->id = newID;}
    void addParameters(std::vector<Parameter> newParameters) {
        this->parameters.insert(this->parameters.end(), newParameters.begin(), newParameters.end());
    }

    std::string getID() {return id;}
    std::vector<Parameter> getParameters() {return parameters;}
};


#endif //PROJECT1_PREDICATE_H
