//
// Created by qgwil on 9/14/2021.
//

#ifndef PROJECT1_COMMAAUTOMATON_H
#define PROJECT1_COMMAAUTOMATON_H


#include "Automaton.h"

class CommaAutomaton : public Automaton {
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}
    void S0(const std::string& input);

};


#endif //PROJECT1_COMMAAUTOMATON_H
