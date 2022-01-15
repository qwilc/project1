//
// Created by qgwil on 1/15/2022.
//

#include "Interpreter.h"

void Interpreter::EvaluateSchemes() {
    for(Predicate scheme : datalogProgram->getSchemes()) {
        std::vector<std::string> attributes;
        for(Parameter param : scheme.getParameters()) {
            attributes.push_back(param.toString());
        }
        Header* header = new Header(attributes);

        database->AddRelation(new Relation(scheme.getID(), header));
    }
}

void Interpreter::EvaluateFacts() {
    for(Predicate fact : datalogProgram->getFacts()) {
        std::string id = fact.getID();
        std::vector<std::string> values;
        for (Parameter param : fact.getParameters()) {
            values.push_back(param.toString());
        }
        database->GetRelations()[id]->AddTuple(Tuple(values));
    }
}

void Interpreter::EvaluateRules() {
    std::vector<Rule> rules = datalogProgram->getRules();
    std::map<int, std::set<int>> adjList;

    for(unsigned int i = 0; i < rules.size(); i++) {
        adjList[i];
        for(Predicate p : rules[i].GetBodyPredicates()) {
            for(unsigned int j = 0; j < rules.size(); j++) {
                if(rules[j].GetHeadPredicate().getID() == p.getID()) {
                    adjList[i].insert(j);
                }
            }
        }
    }

    Graph dependencyGraph(adjList);
    std::cout << dependencyGraph.toString();
    std::vector<std::set<int>> components = dependencyGraph.returnSCCs();

    std::cout << "Rule Evaluation\n";

    for(const std::set<int>& SCC : components) {

        bool isTrivial = true;
        if(SCC.size() > 1 || *adjList[*SCC.begin()].find(*SCC.begin()) != *adjList[*SCC.begin()].end()) {
            isTrivial = false;
        }

        bool wasChanged = true;
        unsigned int numPasses = 0;

        std::cout << "SCC: ";
        std::stringstream ruleString;
        bool addComma = false;
        for(int rule : SCC) {
            if(addComma) {
                ruleString << ",";
            }
            ruleString << "R" << rule;
            addComma = true;
        }
        std::cout << ruleString.str() << "\n";
        do {
            wasChanged = false;
            numPasses++;

            for(int ID : SCC) {
                Rule rule = rules[ID];
                std::cout << rule.toString() << std::endl;
                std::vector<Predicate> predicates = rule.GetBodyPredicates();
                Relation *joinedRelation = evaluatePredicate(predicates[0]);
                for (unsigned int i = 1; i < predicates.size(); i++) {
                    Relation *relation = evaluatePredicate(predicates[i]);
                    *joinedRelation = joinedRelation->Join(relation);
                }

                std::vector<unsigned int> projectVect;
                for (Parameter col : rule.GetHeadPredicate().getParameters()) {
                    std::vector<std::string> joinedHeader = joinedRelation->GetHeader()->GetAttributes();
                    unsigned int idx =
                            find(joinedHeader.begin(), joinedHeader.end(), col.toString()) - joinedHeader.begin();
                    projectVect.push_back(idx);
                }

                *joinedRelation = joinedRelation->Project(projectVect);

                std::string ruleID = rule.GetHeadPredicate().getID();
                Relation *matchingRelation = database->GetRelations()[ruleID];
                *joinedRelation = joinedRelation->Rename(matchingRelation->GetHeader()->GetAttributes());

                matchingRelation->Unite(joinedRelation, wasChanged);
            }
        } while(wasChanged && !isTrivial);
        std::cout << numPasses << " passes: " << ruleString.str() << "\n";
    }
    std::cout << "\n";
}

std::string Interpreter::EvaluateQueries() {
    std::stringstream output;
    output << "Query Evaluation\n";
    for(Predicate query : datalogProgram->getQueries()) {
        Relation* relation = evaluatePredicate(query);
        output << query.toString() << "? ";
        if(!relation->GetTuples().empty()) {
            output << "Yes(" << relation->GetTuples().size() << ")\n";
            output << relation->toString();
        }
        else {
            output << "No\n";
        }
    }

    return output.str();
}

Relation* Interpreter::evaluatePredicate(Predicate p) {
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

    std::vector<unsigned int> projectVector;
    for(const std::string& i : varVector) {
        projectVector.push_back(varMap[i]);
    }
    *newRelation = newRelation->Project(projectVector);
    *newRelation = newRelation->Rename(varVector);

    return newRelation;
}

Interpreter::Interpreter(DatalogProgram* datalogProgram, Database* database) {
this->datalogProgram = datalogProgram;
this->database = database;
}

void Interpreter::Interpret() {
    EvaluateSchemes();
    EvaluateFacts();
    EvaluateRules();
    std::cout << EvaluateQueries();
}