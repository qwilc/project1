#include "Lexer.h"
#include "Parser.h"
#include "Database.h"
#include "Interpreter.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    Database* database = new Database();

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
    DatalogProgram datalogProgram;

    Parser* parser = new Parser(lexer->getTokens());
    try {
        datalogProgram = parser->parse();
    }
    catch (Token * error) {
        std::cout<<"Failure!"<<std::endl<<"  "<<error->toString()<<std::endl;
        return 0;
    }

    Interpreter interpreter(&datalogProgram, database);
    interpreter.Interpret();

    delete database;
    delete lexer;
    delete parser;

    return 0;
}