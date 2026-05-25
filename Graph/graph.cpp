#include "graph.h"

// === Node ===
Node::Node(const std::string& aname) : name(aname) {}
const std::string& Node::getName() const {
    return name;
}
neighbor_iterator Node::nb_begin() const {
    return neighbours.begin(); 
}
neighbor_iterator Node::nb_end() const {
    return neighbours.end(); 
}
void Node::addNeighbour(Node* n, int w) {
    if (n && n != this)
        neighbours[n] = w; 
}
void Node::removeNeighbour(Node* n) { 
    neighbours.erase(n);
}

// === Graph ===
void Graph::addNode(Node* n) {
    nodes.insert(n); 
}
node_iterator Graph::begin() const {
    return nodes.begin(); 
}
node_iterator Graph::end() const { 
    return nodes.end(); 
}
void Graph::removeNode(Node* n) {
    nodes.erase(n); 
    for (auto x : nodes) x->removeNeighbour(n);
}
void Graph::addEdge(Node* b, Node* e, int w) {
    if (nodes.count(b) && nodes.count(e)) { 
        b->addNeighbour(e, w);
        e->addNeighbour(b, w);
    }
}
void Graph::removeEdge(Node* b, Node* e) {
    if (b && e) {
        b->removeNeighbour(e);
        e->removeNeighbour(b);
    } 
}

std::map<int, Node*> loadGraphFromFile(Graph& g, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не удалось открыть файл: " + filename);

    std::map<int, Node*> nodeMap;
    std::string header;
    std::getline(file, header); // Пропускаем строку заголовка "Source\tTarget"

    int u, v;
    while (file >> u >> v) {
        if (!nodeMap.count(u)) { nodeMap[u] = new Node(std::to_string(u)); g.addNode(nodeMap[u]); }
        if (!nodeMap.count(v)) { nodeMap[v] = new Node(std::to_string(v)); g.addNode(nodeMap[v]); }
        g.addEdge(nodeMap[u], nodeMap[v], 1); // В файле нет весов, ставим 1
    }
    return nodeMap;
}

void cleanupGraph(Graph& g) {
    for (auto node : g) delete node;
}

// === BFS ===
BFS::BFS(const Graph& g) : graph(g) {}
bool BFS::connected(Node* begin, Node* end) {
    if (!begin || !end) return false;
    std::queue<Node*> q; q.push(begin);
    std::set<Node*> visited; visited.insert(begin);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur == end) return true;
        for (auto it = cur->nb_begin(); it != cur->nb_end(); ++it) {
            Node* nb = it->first;
            if (!visited.count(nb)) { visited.insert(nb); q.push(nb); }
        }
    } return false;
}

// === DFS ===
DFS::DFS(const Graph& g) : graph(g) {}
bool DFS::connected(Node* begin, Node* end) {
    visited.clear(); return connectedRecursive(begin, end);
}
bool DFS::connectedRecursive(Node* cur, Node* end) {
    if (cur == end) return true;
    visited.insert(cur);
    for (auto it = cur->nb_begin(); it != cur->nb_end(); ++it) {
        Node* nb = it->first;
        if (!visited.count(nb) && connectedRecursive(nb, end)) return true;
    } return false;
}


// === Dijkstra ===
MarkedNode::MarkedNode(Node* a, int m, Node* p) : node(a), mark(m), prev(p) {}
bool PriorityQueue::empty() const {
    return nodes.empty();
}
void PriorityQueue::push(Node* n, int m, Node* p) {
    auto it = std::lower_bound(nodes.begin(), nodes.end(), m, [](const MarkedNode& a, int v) { return a.mark < v; });
    nodes.insert(it, MarkedNode(n, m, p));
}
MarkedNode PriorityQueue::pop() { 
    MarkedNode r = nodes.front();
    nodes.erase(nodes.begin());
    return r;
}
Way::Way() : length(-1) {}
Way unroll(const std::map<Node*, MarkedNode>& v, Node* b, Node* c) {
    Way w; if (!v.count(c)) return w;
    w.length = v.at(c).mark;
    while (c != b) { w.nodes.push_back(c); c = v.at(c).prev; }
    w.nodes.push_back(b); std::reverse(w.nodes.begin(), w.nodes.end()); return w;
}
Dijkstra::Dijkstra(const Graph& g) : graph(g) {}
Way Dijkstra::shortestWay(Node* b, Node* e) {
    PriorityQueue pq; pq.push(b, 0, nullptr); 
    std::map<Node*, MarkedNode> vis;
    while (!pq.empty()) {
        MarkedNode cur = pq.pop();
        if (vis.count(cur.node) && vis[cur.node].mark < cur.mark) continue;
        vis[cur.node] = cur;
        if (cur.node == e) return unroll(vis, b, e);
        for (auto it = cur.node->nb_begin(); it != cur.node->nb_end(); ++it) {
            if (!vis.count(it->first)) pq.push(it->first, cur.mark + it->second, cur.node);
        }
    } return Way();
}
