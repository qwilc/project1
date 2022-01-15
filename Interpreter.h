//
// Created by qgwil on 10/27/2021.
//

#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H

#include <algorithm>
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"


class Interpreter {
private:
    DatalogProgram* datalogProgram;
    Database* database;

    void EvaluateSchemes();

    void EvaluateFacts();

    void EvaluateRules();

    std::string EvaluateQueries();

    Relation* evaluatePredicate(Predicate p);

public:
    Interpreter(DatalogProgram* datalogProgram, Database* database);

    void Interpret();
};


#endif //PROJECT1_INTERPRETER_H
