#include "graph.h"

MarkedNode::MarkedNode(Node* a, int m, Node* p) : node(a), mark(m), prev(p) {}

bool PriorityQueue::empty() const {
    return nodes.empty();
}

void PriorityQueue::push(Node* n, int m, Node* p) {
    auto it = nodes.begin();
    MarkedNode mn(n, m, p);

    while (it != nodes.end() && m < it->mark) ++it;
    if (it == nodes.end()) nodes.push_back(mn);
    else nodes.insert(it, mn);
}

MarkedNode PriorityQueue::pop() {
    MarkedNode r = nodes.back();
    nodes.pop_back();
    return r;
}

Way::Way() : length(-1) {}

Way unroll(const std::map<Node*, MarkedNode>& v, Node* b, Node* c) {
    Way w;
    if (!v.count(c))
        return w;
    w.length = v.at(c).mark;
    while (c != b) {
        w.nodes.push_back(c);
        c = v.at(c).prev;
    }
    w.nodes.push_back(b);
    std::reverse(w.nodes.begin(), w.nodes.end());
    return w;
}

Dijkstra::Dijkstra(const Graph& g) : graph(g) {}

Way Dijkstra::shortestWay(Node* b, Node* e) {
    PriorityQueue pq;
    pq.push(b, 0, nullptr);
    std::map<Node*, MarkedNode> vis;

    while (!pq.empty()) {
        MarkedNode cur = pq.pop();
        vis[cur.node] = cur;
        if (cur.node == e) return unroll(vis, b, e);

        for (auto it = cur.node->nb_begin(); it != cur.node->nb_end(); ++it) {
            int weight = it->second + cur.mark;
            if (!vis.count(it->first))
                pq.push(it->first, weight, cur.node);
        }
    }
    return Way();
}