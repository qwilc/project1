//
// Created by qgwil on 9/15/2021.
//

#ifndef PROJECT1_EXACTMATCHAUTOMATON_H
#define PROJECT1_EXACTMATCHAUTOMATON_H

#include "Automaton.h"

class ExactMatchAutomaton : public Automaton {
private:
    std::string toMatch;
public:
    ExactMatchAutomaton(std::string toMatch, TokenType tokenType);
    void S0(const std::string& input);
};


#endif //PROJECT1_EXACTMATCHAUTOMATON_H
