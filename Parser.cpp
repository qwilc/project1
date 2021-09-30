//
// Created by qgwil on 9/28/2021.
//

#include <iostream>
#include "Parser.h"

Parser::Parser(std::vector<Token*> tokens) {
    this->tokens = tokens;
}

void Parser::parse() {
    try {
        parseDatalog();
    }
    catch (Token * error) {
        std::cout<<"Failure!"<<std::endl<<"  "<<error->toString()<<std::endl;
    }
}

void Parser::match(TokenType type) {
    if(getNextTokenType() == type) {
        index++;
    }
    else {
        throw tokens.at(index);
    }
}

void Parser::parseDatalog() {
    //datalogProgram->SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    parseScheme();
    parseSchemeList();
    match(TokenType::FACTS);
    match(TokenType::COLON);
    parseFactList();
    match(TokenType::RULES);
    match(TokenType::COLON);
    parseRuleList();
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    parseQuery();
    parseQueryList();
    match(TokenType::ENDFILE);
    std::cout<<"Success!"<<std::endl;
}

void Parser::parseSchemeList() {
    if(notFollow(TokenType::FACTS)) {
        parseScheme();
        parseSchemeList();
    }
}

void Parser::parseFactList() {
    if(notFollow(TokenType::RULES)) {
        parseFact();
        parseFactList();
    }
}

void Parser::parseRuleList() {
    if(notFollow(TokenType::QUERIES)) {
        parseRule();
        parseRuleList();
    }
}

void Parser::parseQueryList() {
    if(notFollow(TokenType::ENDFILE)) {
        parseQuery();
        parseQueryList();
    }
}

void Parser::parseScheme() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parseFact() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::STRING);
    parseStringList();
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
}

void Parser::parseRule() {
    parseHeadPredicate();
    match(TokenType::COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(TokenType::PERIOD);
}

void Parser::parseQuery() {
    parsePredicate();
    match(TokenType::Q_MARK);
}

void Parser::parseHeadPredicate() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicate() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicateList() {
    if(notFollow(TokenType::PERIOD)) {
        match(TokenType::COMMA);
        parsePredicate();
        parsePredicateList();
    }
}

void Parser::parseParameterList() {
    if(notFollow(TokenType::RIGHT_PAREN)) {
        match(TokenType::COMMA);
        parseParameter();
        parseParameterList();
    }
}

void Parser::parseStringList() {
    if(notFollow(TokenType::RIGHT_PAREN)) {
        match(TokenType::COMMA);
        match(TokenType::STRING);
        parseStringList();
    }
}

void Parser::parseIDList() {
    if(notFollow(TokenType::RIGHT_PAREN)) {
        match(TokenType::COMMA);
        match(TokenType::ID);
        parseIDList();
    }
}

void Parser::parseParameter() {
    if(getNextTokenType() == TokenType::STRING) {
        match(TokenType::STRING);
    }
    else {
        match(TokenType::ID);
    }
}




