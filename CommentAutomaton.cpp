//
// Created by qgwil on 9/15/2021.
//

#include <iostream>
#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input) {
    if(input[index] == '#') { //start of a comment; go to state 1
        index++;
        inputRead++;
        S1(input);
    }
    else { //not a comment; give up, go home
        Serr();
    }
}

void CommentAutomaton::S1(const std::string &input) {
    if(index >= input.size() || input[index] == '\n') {
        //TODO: Do I do nothing and have a comment that's just the pound?
    }
    else if(input[index] == '|') { //start of a block comment; go to state 2
        index++;
        inputRead++;
        S2(input);
    }
    else { //It's a line comment and that's all it will ever be; go to state 4
        index++;
        inputRead++;
        S4(input);
    }
}

void CommentAutomaton::S2(const std::string &input) {
    if(index >= input.size()) { //reached end of file, becomes UNDEFINED token
        type = TokenType::UNDEFINED;
    }
    else if(input[index] == '\n') { //newline, so update newLines; stay in state 2 //TODO: new line char counts for inputRead?
        index++;
        inputRead++;
        newLines++;
        S2(input);
    }
    else if(input[index] == '|') { //possible ending pipe; go to state 3
        index++;
        inputRead++;
        S3(input);
    }
    else { //any other character in the comment; stay in state 2
        index++;
        inputRead++;
        S2(input);
    }
}

void CommentAutomaton::S3(const std::string &input) {
    if(index >= input.size()) {
        type = TokenType::UNDEFINED;
    }
    else if(input[index] == '#') { //block comment completed; final update of inputRead
        inputRead++;
    }
    else if(input[index] == '|') { //in case the comment ends in extra pipes; stay in state 3
        index++;
        inputRead++;
        S3(input);
    }
    else { //the pipe was a lie (i.e. part of the comment); return to state 2
        index++;
        inputRead++;
        S2(input);
    }
}

void CommentAutomaton::S4(const std::string &input) {
    if(index < input.size() && input[index] != '\n') { //the comment continues; stay in state 4
        index++;
        inputRead++;
        S4(input);
    }
}
