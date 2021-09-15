//
// Created by qgwil on 9/15/2021.
//

#include "ExactMatchAutomaton.h"

ExactMatchAutomaton::ExactMatchAutomaton(std::string toMatch, TokenType tokenType) {
    this->toMatch = toMatch;
    this->type = tokenType;
}

void ExactMatchAutomaton::S0(const std::string& input) {
    bool isMatch = true;
    inputRead = 0;  // member variable inherited from Automaton class
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if (isMatch) {
        inputRead = toMatch.size();
    }
}
