#include "Minesweeper.h"
#include <iostream>
using namespace std;

MinesweeperGame::MinesweeperGame(Field& f) : f(f) {}

void MinesweeperGame::printField() const {
	cout << "\n   ";
	for (int i = 0; i < f.getCols(); i++)
		cout << (i % 10) << " ";
	cout << "\n";

	for (int i = 0; i < f.getRows(); i++) {
		cout << (i < 10 ? " " : "") << i << " ";
		for (int j = 0; j < f.getCols(); j++) {
			const Cell* cell = f.getCell(i, j);
			if (!cell->isRevealed) {
				cout << (cell->isFlagged ? "F " : ". ");
			}
			else if (cell->isBomb) {
				cout << "* ";
			}
			else {
				int n = cell->neighbourBombs;
				if (n == 0)
					cout << "  ";
				else
					cout << n << " ";
			}
		}
		cout << "\n";
	}
	cout << "Bombs: " << f.getBombs() << "  Flags: " << f.getFlags() << "\n" << endl;
}

void MinesweeperGame::play() {
	cout << "===== Minesweeper ===== \n";
	cout << "Commands: O|row|col - open, F|row|col - flag, Q - exit\n" << endl;

	while (!isGameOver && !isWon) {
		printField();

		char command;
		int m, n;
		cout << "Turn: ";
		cin >> command;

		if (command == 'Q' || command == 'q')
			break;

		cin >> m >> n;

		if (command == 'F' || command == 'f') {
			f.placeFlag(m, n);
			continue;
		}
		
		if (command != 'O' && command != 'o') {
			cout << "Unknown command" << endl;
			continue;
		}
		switch (f.makeTurn(m, n)) {
			case trImpossible:
				cout << "Impossible turn!" << endl;
				break;
			case trBomb:
				cout << "First turn on a mine! it was replaced" << endl;
				break;
			case trOk:
				break;
			case trWin:
				printField();
				cout << "You win!" << endl;
				isWon = true;
				break;
			case trOver:
				printField();
				cout << "Bang! You lose!" << endl;
				isGameOver = true;
				break;
		}
	}
}