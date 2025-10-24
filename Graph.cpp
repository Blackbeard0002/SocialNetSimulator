#include "Graph.h"
#include <algorithm> // For std::find

Graph::Graph() : numVertices(0) {}

void Graph::addVertex(int v) {
    if (adj.find(v) == adj.end()) {
        adj[v] = std::vector<int>();
        numVertices++;
    }
}

void Graph::addEdge(int v1, int v2) {
    addVertex(v1);
    addVertex(v2);
    if(std::find(adj[v1].begin(), adj[v1].end(), v2) == adj[v1].end()) {
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }
}

std::vector<int> Graph::getFriends(int v) {
    if (adj.find(v) != adj.end()) {
        return adj[v];
    }
    return std::vector<int>();
}

int Graph::bfs(int startNode, int endNode) {
    if (startNode == endNode) return 0;

    if (adj.find(startNode) == adj.end() || adj.find(endNode) == adj.end()) {
        return -1;
    }

    std::queue<std::pair<int, int>> q; 
    std::vector<int> visited(numVertices, 0);

    q.push({startNode, 0});
    visited[startNode] = 1;

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();
        int currNode = current.first;
        int dist = current.second;

        for (int neighbor : adj[currNode]) {
            if (neighbor == endNode) {
                return dist + 1;
            }
            if (visited[neighbor] == 0) {
                visited[neighbor] = 1;
                q.push({neighbor, dist + 1});
            }
        }
    }

    return -1;
}
