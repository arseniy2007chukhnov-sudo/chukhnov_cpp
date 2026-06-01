#include <iostream>
#include "Minesweeper.h"
using namespace std;
int main()
{
    int m, n, b;

    cout << "===== Minesweeper =====" << endl;
    cout << "Enter number of rows, columns and bombs: ";
    cin >> m >>n >> b;

    try {
        Field field(m, n, b);
        MinesweeperGame game(field);
        game.play();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
