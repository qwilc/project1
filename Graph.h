//
// Created by qgwil on 11/25/2021.
//

#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H
#include <set>
#include <map>
#include <vector>
#include <sstream>

class Graph {
private:
    std::map<int, std::set<int>> adjList;
    std::vector<bool> visited; //TODO: Should be map<int, bool>?
public:
    Graph(std::map<int, std::set<int>> list, std::vector<bool> v) {
        adjList = list;
        visited = v;
    }

    Graph(std::map<int, std::set<int>> list) {
        adjList = list;
        visited = std::vector<bool>(list.size());
        for(unsigned int i = 0; i < visited.size(); i++) { //TODO: Is this best? Do I even need both constructors?
            visited[i] = false;
        }
    }

    std::string toString() {
        std::stringstream output;
        bool addComma = false;
        output << "Dependency Graph\n";
        for(auto rule : adjList) {
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

    std::vector<std::set<int>> returnSCCs() {
        Graph reverse = reverseGraph();
        std::vector<int> postorder = reverse.postorderDFS();
        return dfsForest(postorder);
    }

    Graph reverseGraph() {
        std::map<int, std::set<int>> reverseList;
        for(auto rule : adjList) {
            reverseList[rule.first];
            for(auto adjRule : rule.second) {
                reverseList[adjRule].insert(rule.first);
            }
        }
        return Graph(reverseList);
    }

    std::vector<int> postorderDFS() {
        std::vector<int> postorder;
        for(auto rule : adjList) {
            if(!visited[rule.first]) {
                postorderDFS(rule.first, postorder);
            }
        }
        return postorder;
    }

    void postorderDFS(int rule, std::vector<int>& postorder) {
        std::set<int> adjRules = adjList[rule];
        visited[rule] = true;
        for(auto adjRule : adjRules) {
            if(!visited[adjRule]) {
                postorderDFS(adjRule, postorder);
            }
        }
        postorder.push_back(rule);
    }

    std::vector<std::set<int>> dfsForest(std::vector<int> postorder) {
        std::vector<std::set<int>> forest;
        std::set<int> SCC;
        for(int i = postorder.size()-1; i>=0; i--) {
            if (!visited[postorder[i]]) {
                dfsTree(postorder[i], SCC);
                forest.push_back(SCC);
                SCC = {};
            }
        }
        return forest;
    }

    void dfsTree(int rule, std::set<int>& SCC) {
        std::set<int> adjRules = adjList[rule];
        visited[rule] = true;
        for(auto adjRule : adjRules) {
            if(!visited[adjRule]) {
                dfsTree(adjRule, SCC);
            }
        }
        SCC.insert(rule);
    }
};

#endif //PROJECT1_GRAPH_H
