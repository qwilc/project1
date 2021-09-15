//
// Created by qgwil on 9/15/2021.
//

#ifndef PROJECT1_COMMENTAUTOMATON_H
#define PROJECT1_COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string &input);

private:
    void S1(const std::string &input);

    void S2(const std::string &input);

    void S3(const std::string &input);

    void S4(const std::string &input);
};


#endif //PROJECT1_COMMENTAUTOMATON_H
