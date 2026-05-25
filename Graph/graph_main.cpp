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

        cout << "Граф загружен"<< endl;

        int start = 0, finish = nodes.size() + 1;
        if (nodes.find(start) == nodes.end() || nodes.find(finish) == nodes.end()) {
            cerr << "Ошибка: вершины " << start << " или " << finish << " нет в файле." << endl;
            return 1;
        }

        // 1. Дейкстра
        Dijkstra dijkstra(g);
        Way path = dijkstra.shortestWay(nodes[23], nodes[45]);
        cout << "\n=== Дейкстра (" << 23 << " -> " << 45 << ") ===" << endl;
        if (path.length != -1) {
            cout << "Длина пути (кол-во ребер): " << path.length << "\nМаршрут: ";
            for (size_t i = 0; i < path.nodes.size(); ++i)
                cout << path.nodes[i]->getName() << (i + 1 < path.nodes.size() ? " -> " : "\n");
        }
        else {
            cout << "Путь не найден" << endl;
        }

        // 2. BFS
        BFS bfs(g);
        cout << "\nBFS (связность " << 23 << " -> " << 45 << ")" << endl;
        cout << "Связаны? " << (bfs.connected(nodes[23], nodes[45]) ? "ДА" : "НЕТ") << "\n";

        // 3. DFS
        DFS dfs(g);
        cout << "\nDFS (связность " << 23 << " -> " << 45 << ")" << endl;
        cout << "Связаны? " << (dfs.connected(nodes[23], nodes[45]) ? "ДА" : "НЕТ") << "\n";

        cleanupGraph(g); // Освобождаем память
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}