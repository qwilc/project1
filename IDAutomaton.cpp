//
// Created by qgwil on 9/16/2021.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string &input) {
    if(isalpha(input[index])) {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string &input) {
    if(isalnum(input[index])) {
        index++;
        inputRead++;
        S1(input);
    }
}
