
#include <sstream>
#include "Lexer.h"
#include "CommentAutomaton.h"
#include "StringAutomaton.h"
#include "ExactMatchAutomaton.h"
#include "IDAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for(unsigned int i = 0; i < automata.size(); i++) {
        delete automata.at(i);
        automata.at(i) = nullptr;
    }

    for(unsigned int i = 0; i < tokens.size(); i++) {
        delete tokens.at(i);
        tokens.at(i) = nullptr;
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new ExactMatchAutomaton(":", TokenType::COLON));
    automata.push_back(new ExactMatchAutomaton(":-", TokenType::COLON_DASH));
    automata.push_back(new ExactMatchAutomaton(",", TokenType::COMMA));
    automata.push_back(new ExactMatchAutomaton(".", TokenType::PERIOD));
    automata.push_back(new ExactMatchAutomaton("?", TokenType::Q_MARK));
    automata.push_back(new ExactMatchAutomaton("(", TokenType::LEFT_PAREN));
    automata.push_back(new ExactMatchAutomaton(")", TokenType::RIGHT_PAREN));
    automata.push_back(new ExactMatchAutomaton("*", TokenType::MULTIPLY));
    automata.push_back(new ExactMatchAutomaton("+", TokenType::ADD));
    automata.push_back(new ExactMatchAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new ExactMatchAutomaton("Facts", TokenType::FACTS));
    automata.push_back(new ExactMatchAutomaton("Rules", TokenType::RULES));
    automata.push_back(new ExactMatchAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
}

void Lexer::Run(std::string& input) {
    int maxRead;
    int inputRead;
    int lineNum = 1;
    Automaton * maxAutomaton;
    Token * newToken;

    // While there are more characters to tokenize
    while (input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata.at(0);

        while(input.size() > 0 && isspace(input.at(0))) {
            if(input.at(0) == '\n') {
                lineNum ++;
            }
            input.erase(0, 1);
        }
        if(input.size() <= 0) {
            break;
        }

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        for(Automaton * automaton : automata) {
            inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }

        // Here is the "Max" part of the algorithm
        //Does not create COMMENT tokens
        if (maxRead > 0) {
            if(maxAutomaton->getType() != TokenType::COMMENT) {
                newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNum);
                tokens.push_back(newToken);
            }
            lineNum += maxAutomaton->NewLinesRead();
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            maxRead = 1;
            newToken =  new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNum);
            tokens.push_back(newToken);
        }
        // Update `input` by removing characters read to create Token
        input.erase(0, maxRead);
    }
    tokens.push_back(new Token(TokenType::ENDFILE, "", lineNum));
}

std::string Lexer::toString() {
    std::stringstream tokenString;
    for(Token * token : tokens) {
         tokenString << token->toString() << std::endl;
    }
    tokenString << "Total Tokens = " << tokens.size();
    return tokenString.str();
}

std::vector<Token *> Lexer::getTokens() {
    return tokens;
}
