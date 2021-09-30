//
// Created by qgwil on 9/28/2021.
//

#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

class Parser {
private:
    int index = 0;
    std::vector<Token*> tokens;

    void match(TokenType type);
    TokenType getNextTokenType() {return tokens.at(index)->getType();}
    bool notFollow(TokenType followSet) {return getNextTokenType() != followSet;}

    void parseDatalog();
    void parseScheme();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();

    void parseFact();
    void parseRule();
    void parseQuery();

    void parseHeadPredicate();
    void parsePredicate();

    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIDList();
    void parseParameter();

public:
    Parser(std::vector<Token*> tokens);
    void parse();
};


#endif //PROJECT1_PARSER_H
