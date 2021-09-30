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
    std::string parserOutput;
    try {
        parserOutput = parser->parse().toString();
    }
    catch (Token * error) {
        std::cout<<"Failure!"<<std::endl<<"  "<<error->toString()<<std::endl;
    }
    std::cout << parserOutput << std::endl;

    /*Parameter* parameter = new Parameter(true, "parameter");
    Predicate* predicate0 = new Predicate("predicate0");
    Predicate* predicate1 = new Predicate("predicate1");
    Predicate* predicate2 = new Predicate("predicate2");
    Rule* rule = new Rule(predicate1);

    predicate0->addParameter(parameter);
    predicate1->addParameter(parameter);
    predicate2->addParameter(parameter);
    rule->addBodyPredicate(predicate0);
    rule->addBodyPredicate(predicate2);

    DatalogProgram* datalog = new DatalogProgram();

    datalog->addScheme(predicate0);
    datalog->addFact(predicate1);
    datalog->addQuery(predicate2);
    datalog->addRule(rule);
    datalog->addToDomain("hi");

    std::cout << datalog->toString() << std::endl;*/

    delete lexer;

    return 0;
}