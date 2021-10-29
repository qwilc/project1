#include "Lexer.h"
#include "Parser.h"
#include "Database.h"
#include "Interpreter.h"
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
    DatalogProgram datalogProgram;

    Parser* parser = new Parser(lexer->getTokens());
    try {
        datalogProgram = parser->parse();
    }
    catch (Token * error) {
        std::cout<<"Failure!"<<std::endl<<"  "<<error->toString()<<std::endl;
        return 0;
    }

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

    //TEST CODE TODO: Remove when done with all this

    std::vector<std::vector<std::string>> tuples {
            {"abc", "def", "hij"},
            {"klm", "nop", "qrs"},
            {"abc", "abc", "abc"},
            {"abc", "abc", "def"},
            {"def", "abc", "abc"},
            {"abc", "def", "abc"},
            {"qrs", "abc", "qrs"}
    };

    std::vector<std::string> head_val = {"0", "1", "2"};
    std::string name = "ID";
    Header* header = new Header(head_val);
    Relation* relation = new Relation(name, header);
    Database* database = new Database();

    database->AddRelation(relation);

    for(auto & tuple : tuples) {
        database->GetRelations()[name]->AddTuple(tuple);
    }

    /*Parameter* param1 = new Parameter(true, "abc");
    Parameter* param2 = new Parameter(false, "X");
    Parameter* param3 = new Parameter(false, "X");
    Predicate* predicate0 = new Predicate();
    Predicate* predicate1 = new Predicate("predicate1");
    Predicate* predicate2 = new Predicate("predicate2");

    predicate0->addParameter(*param1);
    predicate0->addParameter(*param2);
    predicate0->addParameter(*param3);

    predicate0->setID(name);*/

    Interpreter interpreter(&datalogProgram, database);
    //Relation* testRel = interpreter.evaluatePredicate(*predicate0);
    interpreter.Interpret();

    /*for(std::pair<std::string, Relation*> r : database->GetRelations()) {
        std::cout << r.second->toString();
    }*/

    /*std::cout<<database->GetRelations().at(0)->GetName()<<std::endl;
    database->GetRelations().at(0)->GetHeader()->Print();
    for(Tuple* tup : database->GetRelations().at(0)->GetTuples()) {
        tup->Print();
    }*/

    delete lexer;

    return 0;
}