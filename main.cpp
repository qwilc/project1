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

    //TEST CODE TODO: Remove when done with all this

    /*std::vector<std::vector<std::string>> tuples {
            //{"abc", "def", "hij"},
            //{"klm", "nop", "qrs"},
            //{"abc", "abc", "abc"},
            {"abc", "abc", "def"},
            {"def", "abc", "abc"},
            {"abc", "def", "abc"},
            //{"qrs", "abc", "qrs"}
    };

    std::vector<std::string> head_val = {"0", "1", "2"};
    std::vector<std::string> head_val2 = {"3", "4", "0"};
    std::string name = "Test1";
    std::string name2 = "Test2";
    Header* header = new Header(head_val);
    Header* header2 = new Header(head_val2);
    Relation* relation = new Relation(name, header);
    Relation* relation2 = new Relation(name2, header2);

    database->AddRelation(relation);
    database->AddRelation(relation2);

    for(auto & tuple : tuples) {
        database->GetRelations()[name]->AddTuple(tuple);
        database->GetRelations()[name2]->AddTuple(tuple);
    }
    database->GetRelations()[name2]->AddTuple(Tuple({"A","B","C"}));

    relation->GetHeader();
    Relation relation3 = relation->Join(relation2);
    relation3.GetHeader()->Print();
    for(Tuple t : relation->GetTuples()) {
        t.Print();
        std::cout << std::endl;
    }*/

    Interpreter interpreter(&datalogProgram, database);
    interpreter.Interpret();

    delete lexer;
    delete parser;

    return 0;
}