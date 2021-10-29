//
// Created by qgwil on 9/28/2021.
//

#include <iostream>
#include "Parser.h"

Parser::Parser(std::vector<Token*> tokens) {
    this->tokens = tokens;
}

DatalogProgram Parser::parse() {
    return parseDatalog();
}

Token * Parser::match(TokenType type) {
    Token * currToken = tokens.at(index);
    if(getNextTokenType() == type) {
        index++;
        return currToken;
    }
    else {
        throw currToken;
    }
}

DatalogProgram Parser::parseDatalog() {
    DatalogProgram datalogProgram;

    //datalogProgram->SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    datalogProgram.addSchemes(parseScheme());
    datalogProgram.addSchemes(parseSchemeList());
    match(TokenType::FACTS);
    match(TokenType::COLON);
    datalogProgram.addFacts(parseFactList());
    match(TokenType::RULES);
    match(TokenType::COLON);
    datalogProgram.addRules(parseRuleList());
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    datalogProgram.addQueries(parseQuery());
    datalogProgram.addQueries(parseQueryList());
    match(TokenType::ENDFILE);

    for(Predicate fact : datalogProgram.getFacts()) {
        for(Parameter param : fact.getParameters()) {
            datalogProgram.addToDomain(param.toString());
        }
    }

    //std::cout<<"Success!"<<std::endl;
    return datalogProgram;
}

std::vector<Predicate> Parser::parseSchemeList() {
    std::vector<Predicate> returnVec;
    if(notFollow(TokenType::FACTS)) {
        returnVec.push_back(parseScheme());
        returnVec = append(returnVec, parseSchemeList());
    }
    return returnVec;
}

std::vector<Predicate> Parser::parseFactList() {
    std::vector<Predicate> returnVec;
    if(notFollow(TokenType::RULES)) {
        returnVec.push_back(parseFact());
        returnVec = append(returnVec, parseFactList());
    }
    return returnVec;
}

std::vector<Rule> Parser::parseRuleList() {
    std::vector<Rule> returnVec;
    if(notFollow(TokenType::QUERIES)) {
        returnVec.push_back(parseRule());
        returnVec = append(returnVec, parseRuleList());
    }
    return returnVec;
}

std::vector<Predicate> Parser::parseQueryList() {
    std::vector<Predicate> returnVec;
    if(notFollow(TokenType::ENDFILE)) {
        returnVec.push_back(parseQuery());
        returnVec = append(returnVec, parseQueryList());
    }
    return returnVec;
}

Predicate Parser::parseScheme() {
    Predicate scheme;
    scheme.setID(match(TokenType::ID)->getDescription());
    match(TokenType::LEFT_PAREN);
    Parameter id(false, match(TokenType::ID)->getDescription());
    scheme.addParameter(id);
    scheme.addParameters(parseIDList());
    match(TokenType::RIGHT_PAREN);
    return scheme;
}

Predicate Parser::parseFact() {
    Predicate fact;
    fact.setID(match(TokenType::ID)->getDescription());
    match(TokenType::LEFT_PAREN);
    Parameter string(true, match(TokenType::STRING)->getDescription());
    fact.addParameter(string);
    fact.addParameters(parseStringList());
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
    return fact;
}

Rule Parser::parseRule() {
    Rule rule(parseHeadPredicate());
    match(TokenType::COLON_DASH);
    rule.addBodyPredicate(parsePredicate());
    rule.addBodyPredicate(parsePredicateList());
    match(TokenType::PERIOD);
    return rule;
}

Predicate Parser::parseQuery() {
    Predicate query = parsePredicate();
    match(TokenType::Q_MARK);
    return query;
}

Predicate Parser::parseHeadPredicate() {
    Predicate headPredicate;
    headPredicate.setID(match(TokenType::ID)->getDescription());
    match(TokenType::LEFT_PAREN);
    Parameter id(false, match(TokenType::ID)->getDescription());
    headPredicate.addParameter(id);
    headPredicate.addParameters(parseIDList());
    match(TokenType::RIGHT_PAREN);
    return headPredicate;
}

Predicate Parser::parsePredicate() {
    Predicate predicate;
    predicate.setID(match(TokenType::ID)->getDescription());
    match(TokenType::LEFT_PAREN);
    Parameter parameter = parseParameter();
    predicate.addParameter(parameter);
    predicate.addParameters(parseParameterList());
    match(TokenType::RIGHT_PAREN);
    return predicate;
}

std::vector<Predicate> Parser::parsePredicateList() {
    std::vector<Predicate> returnVec;
    if(notFollow(TokenType::PERIOD)) {
        match(TokenType::COMMA);
        returnVec.push_back(parsePredicate());
        returnVec = append(returnVec, parsePredicateList());
    }
    return returnVec;
}

std::vector<Parameter> Parser::parseParameterList() {
    std::vector<Parameter> returnVec;
    if(notFollow(TokenType::RIGHT_PAREN)) {
        match(TokenType::COMMA);
        returnVec.push_back(parseParameter());
        returnVec = append(returnVec, parseParameterList());
    }
    return returnVec;
}

std::vector<Parameter> Parser::parseStringList() {
    std::vector<Parameter> returnVec;
    if(notFollow(TokenType::RIGHT_PAREN)) {
        match(TokenType::COMMA);
        Parameter parameter(true, match(TokenType::STRING)->getDescription());
        returnVec.push_back(parameter);
        returnVec = append(returnVec, parseStringList());
    }
    return returnVec;
}

std::vector<Parameter> Parser::parseIDList() {
    std::vector<Parameter> returnVec;
    if(notFollow(TokenType::RIGHT_PAREN)) {
        match(TokenType::COMMA);
        Parameter id(false, match(TokenType::ID)->getDescription());
        returnVec.push_back(id);
        returnVec = append(returnVec, parseIDList());
    }
    return returnVec;
}

Parameter Parser::parseParameter() {
    if(getNextTokenType() == TokenType::STRING) {
        Parameter parameter(true, match(TokenType::STRING)->getDescription());
        return parameter;
    }
    else {
        Parameter parameter(false, match(TokenType::ID)->getDescription());
        return parameter;
    }
}




