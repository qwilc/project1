//
// Created by qgwil on 9/14/2021.
//

#ifndef PROJECT1_STRINGAUTOMATON_H
#define PROJECT1_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton{
public:
    StringAutomaton() : Automaton(TokenType::STRING) {}

    void S0(const std::string& input);

private:
    void S1(const std::string& input);

    void S2(const std::string& input);
};


#endif //PROJECT1_STRINGAUTOMATON_H
