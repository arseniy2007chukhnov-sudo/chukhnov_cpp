#pragma once

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <assert.h>
#include <algorithm>

using namespace std;

class Node;

class Graph {
    std::set<Node*> nodes;
public:
    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end);
    void removeEdge(Node* begin, Node* end);

    auto begin() const { return nodes.begin(); }
    auto end() const { return nodes.end(); }
};

class Node {
    std::string name;
    std::set<Node*> neighbours;
    std::map<Node*, int> weights;

    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);

public:
    Node(const std::string& aname) : name(aname) {}

    const std::string& getName() const { return name; }

    void setWeight(Node* neighbour, int weight) {
        weights[neighbour] = weight;
    }

    int getWeight(Node* neighbour) const {
        auto it = weights.find(neighbour);
        return it != weights.end() ? it->second : 1;
    }

    auto nb_begin() const { return neighbours.begin(); }
    auto nb_end() const { return neighbours.end(); }

    friend class Graph;
};

typedef std::set<Node*>::const_iterator node_iterator;

class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

class DFS {
    const Graph& graph;
    std::set<Node*> visited;
    bool connected(Node* begin, Node* end, int depth);
public:
    DFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};
