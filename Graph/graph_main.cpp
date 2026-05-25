#include "graph.h"
#include <iostream>
#include <locale.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        Graph g;
        // Читаем граф из файла.
        auto nodes = loadGraphFromFile(g, "testgraph.txt");

        cout << "Граф загружен. Всего вершин: " << nodes.size() << "\n";

        int start = 0, finish = 48;
        if (nodes.find(start) == nodes.end() || nodes.find(finish) == nodes.end()) {
            cerr << "Ошибка: вершины " << start << " или " << finish << " нет в файле.\n";
            return 1;
        }

        // 1. Дейкстра
        Dijkstra dijkstra(g);
        Way path = dijkstra.shortestWay(nodes[start], nodes[finish]);
        cout << "\n=== Дейкстра (" << start << " -> " << finish << ") ===\n";
        if (path.length != -1) {
            cout << "Длина пути (кол-во ребер): " << path.length << "\nМаршрут: ";
            for (size_t i = 0; i < path.nodes.size(); ++i)
                cout << path.nodes[i]->getName() << (i + 1 < path.nodes.size() ? " -> " : "\n");
        }
        else {
            cout << "Путь не найден\n";
        }

        // 2. BFS
        BFS bfs(g);
        cout << "\n=== BFS (связность " << start << " -> " << finish << ") ===\n";
        cout << "Связаны? " << (bfs.connected(nodes[start], nodes[finish]) ? "ДА" : "НЕТ") << "\n";

        // 3. DFS
        DFS dfs(g);
        cout << "\n=== DFS (связность " << start << " -> " << finish << ") ===\n";
        cout << "Связаны? " << (dfs.connected(nodes[start], nodes[finish]) ? "ДА" : "НЕТ") << "\n";

        cleanupGraph(g); // Освобождаем память
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}