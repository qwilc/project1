//
// Created by qgwil on 10/27/2021.
//

#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H

#include <algorithm>
#include "DatalogProgram.h"
#include "Database.h"


class Interpreter {
public:
    DatalogProgram* datalogProgram;
    Database* database;

    void EvaluateSchemes() {
        for(Predicate scheme : datalogProgram->getSchemes()) {
            std::vector<std::string> attributes;
            for(Parameter param : scheme.getParameters()) {
                attributes.push_back(param.toString());
            }
            Header* header = new Header(attributes);

            database->AddRelation(new Relation(scheme.getID(), header));
        }
    }

    void EvaluateFacts() {
        for(Predicate fact : datalogProgram->getFacts()) {
            std::string id = fact.getID();
            std::vector<std::string> values;
            for (Parameter param : fact.getParameters()) {
                values.push_back(param.toString());
            }
            database->GetRelations()[id]->AddTuple(Tuple(values));
        }
    }

    std::string EvaluateQueries() {
        std::stringstream output;
        for(Predicate query : datalogProgram->getQueries()) {
            Relation* relation = evaluatePredicate(query);
            output << query.toString() << "? ";
            if(relation->GetTuples().size() != 0) {
                output << "Yes(" << relation->GetTuples().size() << ")";
                output << relation->toString();
            }
            else {
                output << "No\n";
            }
        }

        return output.str();
    }

    Relation* evaluatePredicate(Predicate p) {
        std::string id = p.getID();
        Relation* newRelation = new Relation(id, database->GetRelations()[id]->GetHeader());
        newRelation->SetTuples(database->GetRelations()[id]->GetTuples());
        std::map<std::string, int> varMap;
        std::vector<std::string> varVector;

        for (unsigned int i = 0; i < p.getParameters().size(); i++) {
            if(p.getParameters()[i].isString()) {
                *newRelation = newRelation->Select(i, p.getParameters()[i].toString());
            } else
            {
                std::vector<std::string>::iterator it;
                it = find(varVector.begin(), varVector.end(), p.getParameters()[i].toString());
                if(it == varVector.end()) {
                    varMap.insert({p.getParameters()[i].toString(), i});
                    varVector.push_back(p.getParameters()[i].toString());
                }
                else {
                    *newRelation = newRelation->Select(i, it - varVector.begin());
                }
            }
        }

        std::vector<int> projectVector;
        for(const std::string& i : varVector) {
            projectVector.push_back(varMap[i]);
        }
        *newRelation = newRelation->Project(projectVector);
        *newRelation = newRelation->Rename(varVector);

        return newRelation;
    }

public:
    Interpreter(DatalogProgram* datalogProgram, Database* database) {
        this->datalogProgram = datalogProgram;
        this->database = database;
    }

    void Interpret() {
        EvaluateSchemes();
        EvaluateFacts();
        std::cout << EvaluateQueries();
    }
};


#endif //PROJECT1_INTERPRETER_H
