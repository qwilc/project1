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
    //

public:
    Parser();
    void parse(std::vector<Token*> tokens);
};


#endif //PROJECT1_PARSER_H
