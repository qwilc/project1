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

    Token * match(TokenType type);
    TokenType getNextTokenType() {return tokens.at(index)->getType();}
    bool notFollow(TokenType followSet) {return getNextTokenType() != followSet;}

    template <typename T>
    std::vector<T> append(std::vector<T> baseVec, std::vector<T> addVec) {
        baseVec.insert(baseVec.end(), addVec.begin(), addVec.end());
        return baseVec;
    }

    DatalogProgram parseDatalog();
    Predicate parseScheme();
    std::vector<Predicate> parseSchemeList();
    std::vector<Predicate> parseFactList();
    std::vector<Rule> parseRuleList();
    std::vector<Predicate> parseQueryList();

    Predicate parseFact();
    Rule parseRule();
    Predicate parseQuery();

    Predicate parseHeadPredicate();
    Predicate parsePredicate();

    std::vector<Predicate> parsePredicateList();
    std::vector<Parameter> parseParameterList();
    std::vector<Parameter> parseStringList();
    std::vector<Parameter> parseIDList();
    Parameter parseParameter();

public:
    Parser(std::vector<Token*> tokens);
    DatalogProgram parse();
};


#endif //PROJECT1_PARSER_H
