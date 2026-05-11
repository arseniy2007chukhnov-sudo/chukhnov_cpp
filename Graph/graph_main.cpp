#include "graph.h"
#include <locale.h>
int main() {
    setlocale(LC_ALL, "Russian");
    Graph g;

    Node a("A");
    Node b("B");
    Node c("C");
    Node d("D");
    Node e("E");

    g.addNode(&a);
    g.addNode(&b);
    g.addNode(&c);
    g.addNode(&d);
    g.addNode(&e);

    auto addBidirectionalEdge = [&](Node* u, Node* v, int w) {
        g.addEdge(u, v);
        u->setWeight(v, w);
        v->setWeight(u, w);
        };

    addBidirectionalEdge(&a, &b, 2);
    addBidirectionalEdge(&a, &c, 1);
    addBidirectionalEdge(&b, &d, 3);
    addBidirectionalEdge(&c, &d, 1);
    addBidirectionalEdge(&d, &e, 2);

    BFS bfs(g);
    assert(bfs.connected(&a, &e) == true);
    assert(bfs.connected(&a, &b) == true);
    assert(bfs.connected(&b, &c) == true);
    assert(bfs.connected(&e, &a) == true);
    std::cout << "BFS: Все тесты соединения пройдены.\n";

    DFS dfs(g);
    assert(dfs.connected(&a, &e) == true);
    assert(dfs.connected(&a, &b) == true);
    assert(dfs.connected(&b, &c) == true);
    assert(dfs.connected(&e, &a) == true);
    std::cout << "DFS: Все тесты соединения пройдены.\n";


    g.removeEdge(&a, &c);

    assert(bfs.connected(&a, &c) == true);
    assert(bfs.connected(&a, &e) == true);
    std::cout << "Убрано ребро a c\n";

    g.removeNode(&b);
    assert(bfs.connected(&a, &d) == false);
    assert(bfs.connected(&a, &c) == false);
    assert(bfs.connected(&a, &e) == false);
    std::cout << "Убрана вершина b\n";

    return 0;
}
