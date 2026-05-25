#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <stdexcept>

class Node;
using neighbor_iterator = std::map<Node*, int>::const_iterator;
using node_iterator = std::set<Node*>::const_iterator;

class Node {
    std::string name;
    std::map<Node*, int> neighbours;

    void addNeighbour(Node* neighbour, int weight);
    void removeNeighbour(Node* neighbour);
public:
    explicit Node(const std::string& aname);
    const std::string& getName() const;
    neighbor_iterator nb_begin() const;
    neighbor_iterator nb_end() const;

    friend class Graph;
    friend class Dijkstra;
    friend class BFS;
    friend class DFS;
};

class Graph {
    std::set<Node*> nodes;
public:
    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end, int weight);
    void removeEdge(Node* begin, Node* end);
    node_iterator begin() const;
    node_iterator end() const;
};

std::map<int, Node*> loadGraphFromFile(Graph& g, const std::string& filename);
void cleanupGraph(Graph& g);

class BFS {
    const Graph& graph;
public:
    explicit BFS(const Graph& agraph);
    bool connected(Node* begin, Node* end);
};

class DFS {
    const Graph& graph;
    std::set<Node*> visited;
    bool connectedRecursive(Node* curr, Node* end);
public:
    explicit DFS(const Graph& agraph);
    bool connected(Node* begin, Node* end);
};

// Дейкстра 
struct MarkedNode { 
    Node* node;
    int mark;
    Node* prev; 
    MarkedNode(Node* a = 0, int m = 0, Node* p = 0);
};

class PriorityQueue { 
    std::vector<MarkedNode> nodes;
public:
    MarkedNode pop();
    void push(Node*, int, Node*);
    bool empty() const;
};

struct Way { std::vector<Node*> nodes; int length; Way(); };
Way unroll(const std::map<Node*, MarkedNode>&, Node*, Node*);
class Dijkstra { const Graph& graph;
public: 
    explicit Dijkstra(const Graph&);
    Way shortestWay(Node*, Node*);
};
