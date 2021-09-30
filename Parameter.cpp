//
// Created by qgwil on 9/29/2021.
//

#include "Parameter.h"

Parameter::Parameter(bool isString, std::string value) {
    this->string = isString;
    this->value = value;
}

std::string Parameter::toString() {
    if(string) {
        return "'" + value + "'";
    }
    else {
        return value;
    }
}
