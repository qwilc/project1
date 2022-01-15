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
    std::vector<bool> visited;
public:
    Graph(const std::map<int,std::set<int>>& list);

    std::string toString();

    std::vector<std::set<int>> returnSCCs();

    Graph reverseGraph();

    std::vector<int> postorderDFS();

    void postorderDFS(int rule, std::vector<int>& postorder);

    std::vector<std::set<int>> dfsForest(std::vector<int> postorder);

    void dfsTree(int rule, std::set<int> &SCC);
};

#endif //PROJECT1_GRAPH_H
