#pragma once
#include <vector>
enum TurnResult {
	trImpossible, // Ход невозможен
	trBomb, // Первый ход на мину
	trOk, // Обычный ход
	trWin, // Победа
	trOver // Проигрыш
};
struct Position {
	int row, col;
};
class Cell {
public:
	bool isBomb = false;
	bool isFlagged = false;
	bool isRevealed = false;
	int neighbourBombs = 0;

	virtual void activate() { isRevealed = true; }
	virtual ~Cell() = default;
};

class Bomb : public Cell {
public:
	Bomb(){ isBomb = true; }
	void activate() override { isRevealed = true; }
};

class Sf_cell : public Cell {
public:
	Sf_cell() { isBomb = false; }
	void activate() override { isRevealed = true; }
};

class Field {
	std::vector <std::vector<Cell*>> cells;
	int rows, cols, bombs;
	int flags = 0;
	bool firstMove = true;

	void placeBombs();
	void calculateNeighbourBombs();
	int  countNeighbourBombs(int m, int n) const;
	void floodReveal(int m, int n) const;
	bool checkWin() const;
	bool inBounds(int m, int n) const;
	Position findSafeCell(int exM, int exN) const;
	
public:
	Field(int m, int n, int b);
	~Field();

	TurnResult makeTurn(int m, int n);
	void placeFlag(int m, int n);

	int getRows()  const { return rows; }
	int getCols()  const { return cols; }
	int getBombs() const { return bombs; }
	int getFlags() const { return flags; }

	const Cell* getCell(int m, int n) const;

};

class MinesweeperGame {
	Field& f;
	bool isGameOver = false;
	bool isWon = false;
	void printField() const;
public:
	MinesweeperGame(Field& f);
	void play();
};



