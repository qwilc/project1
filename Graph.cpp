//
// Created by qgwil on 1/15/2022.
//

#include "Graph.h"

Graph::Graph(const std::map<int,std::set<int>>& list) {
    adjList = list;
    visited = std::vector<bool>(list.size());
    for(auto b : visited) {
        b = false;
    }
}

std::string Graph::toString() {
    std::stringstream output;
    bool addComma = false;
    output << "Dependency Graph\n";
    for(const auto& rule : adjList) {
        output << "R" << rule.first << ":";
        for(auto adjRule : rule.second) {
            if (addComma) {
                output << ",";
            }
            output << "R" << adjRule;
            addComma = true;
        }
        addComma = false;
        output << "\n";
    }
    output << "\n";
    return output.str();
}

std::vector<std::set<int>> Graph::returnSCCs() {
    Graph reverse = reverseGraph();
    std::vector<int> postorder = reverse.postorderDFS();
    return dfsForest(postorder);
}

Graph Graph::reverseGraph() {
    std::map<int, std::set<int>> reverseList;
    for(const auto& rule : adjList) {
        reverseList[rule.first];
        for(auto adjRule : rule.second) {
            reverseList[adjRule].insert(rule.first);
        }
    }
    return Graph(reverseList);
}

std::vector<int> Graph::postorderDFS() {
    std::vector<int> postorder;
    for(const auto& rule : adjList) {
        if(!visited[rule.first]) {
            postorderDFS(rule.first, postorder);
        }
    }
    return postorder;
}

void Graph::postorderDFS(int rule, std::vector<int>& postorder) {
    std::set<int> adjRules = adjList[rule];
    visited[rule] = true;
    for(auto adjRule : adjRules) {
        if(!visited[adjRule]) {
            postorderDFS(adjRule, postorder);
        }
    }
    postorder.push_back(rule);
}

std::vector<std::set<int>> Graph::dfsForest(std::vector<int> postorder) {
    std::vector<std::set<int>> forest;
    std::set<int> SCC;
    for(unsigned int i = postorder.size()-1; i>=0; i--) {
        if (!visited[postorder[i]]) {
            dfsTree(postorder[i], SCC);
            forest.push_back(SCC);
            SCC = {};
        }
    }
    return forest;
}

void Graph::dfsTree(int rule, std::set<int> &SCC) {
    std::set<int> adjRules = adjList[rule];
    visited[rule] = true;
    for(auto adjRule : adjRules) {
        if(!visited[adjRule]) {
            dfsTree(adjRule, SCC);
        }
    }
    SCC.insert(rule);
}