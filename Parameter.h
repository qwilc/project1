//
// Created by qgwil on 9/29/2021.
//

#ifndef PROJECT1_PARAMETER_H
#define PROJECT1_PARAMETER_H

#include <string>

class Parameter {
    bool string;
    std::string value;

public:
    Parameter(bool isString, std::string value);

    bool isString() {return string;};

    std::string toString();
};


#endif //PROJECT1_PARAMETER_H
