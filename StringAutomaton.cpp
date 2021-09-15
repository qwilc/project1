//
// Created by qgwil on 9/14/2021.
//

#include <iostream>
#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') { //a single quote; go to state 1
        index++;
        inputRead++;
        S1(input);
    }
    else { //not a string; go away
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if(index >= input.size()) { //end of file reached, becomes an UNDEFINED token
        type = TokenType::UNDEFINED;
    }
    else if(input[index] == '\n') { //new line, so update newLines; stay in state 1 TODO: Do newlines count for inputRead?
        index++;
        inputRead++;
        newLines++;
        S1(input);
    }
    else if (input[index] == '\'') { //*gasp* A single quote! Could this be the end?; go to state 2
        index++;
        inputRead++;
        S2(input);
    }
    else { //another char doing char things; stay in state 1
        index++;
        inputRead++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'') { //Another single quote; It was all a lie (i.e. an apostrophe); back to state 1
        index++;
        inputRead++;
        S1(input);
    }
}
