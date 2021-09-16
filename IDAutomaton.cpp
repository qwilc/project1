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
    /*else {
        std::string stringRead = input.substr(0, inputRead);
        if(stringRead == "Schemes" || stringRead == "Facts" ||
            stringRead == "Rules" || stringRead == "Queries") { //If the input is a keyword, don't count as an ID
            // TODO: Do I want to handle keywords here? Though, I think the way I have it set up, if ExactMatch is in the automata vector before ID, it will always display the keyword token
            Serr();
        }
    }*/
}
