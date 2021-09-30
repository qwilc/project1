#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    std::string fileName = argv[1];
    std::ifstream inFile(fileName);
    if(!inFile.is_open()) {
        std::cout << "Error opening " << fileName << std::endl;
        return 1;
    }

    std::string inputStr;

    while(inFile.peek() != EOF) {
        inputStr += (inFile.get());
    }

    lexer->Run(inputStr);
    //std::cout << lexer->toString();

    Parser* parser = new Parser(lexer->getTokens());

    parser->parse();

    delete lexer;

    return 0;
}