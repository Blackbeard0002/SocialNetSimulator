#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <queue>
#include <vector>

/**
 * An Undirected Graph implementation using an adjacency map.
 */
class Graph {
private:
    std::unordered_map<int, std::vector<int>> adj;
    int numVertices;

public:
    Graph();

    void addVertex(int v);
    void addEdge(int v1, int v2);
    std::vector<int> getFriends(int v);
    int bfs(int startNode, int endNode);

    int getNumVertices() const {
        return numVertices;
    }
};

#endif 
