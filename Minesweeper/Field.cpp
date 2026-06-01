#include "Minesweeper.h"
#include <random>
#include <algorithm>
#include <stdexcept>


Field::Field(int m, int n, int b) : rows(m), cols(n), bombs(b) {
	if (m <= 0 || n <= 0)
		throw std::invalid_argument("Field size should be positive");
	if (b <= 0 || b >= m * n)
		throw std::invalid_argument("Impossible bomb count");

	cells.resize(rows, std::vector<Cell*>(cols, nullptr));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = new Sf_cell();

	placeBombs();
}

Field::~Field() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			delete cells[i][j];
}

bool Field::inBounds(int m, int n) const {
	return (m >= 0 && m < rows && n < cols && n >= 0);
}

void Field::placeBombs() {
	std::vector<Position> positions;

	positions.reserve(rows * cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			positions.push_back({ i, j });
	
	std::mt19937 rng(std::random_device{}());
	std::shuffle(positions.begin(), positions.end(), rng);

	for (int i = 0; i < bombs; i++) {
		int r = positions[i].row;
		int c = positions[i].col;
		delete cells[r][c];
		cells[r][c] = new Bomb();
	}
	calculateNeighbourBombs();
}

void Field::calculateNeighbourBombs() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (!cells[i][j]->isBomb)
				cells[i][j]->neighbourBombs = countNeighbourBombs(i, j);
}

int Field::countNeighbourBombs(int m, int n) const {
	const int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int count = 0;
	for (int d = 0; d < 8; d++) {
		int nr = m + dr[d], nc = n + dc[d];
		if (inBounds(nr, nc) && cells[nr][nc]->isBomb)
			count++;
	}
	return count;
}

void Field::floodReveal(int m, int n) const {
	if (!inBounds(m, n) || cells[m][n]->isRevealed || cells[m][n]->isBomb)
		return;
	cells[m][n]->activate();
	if (cells[m][n]->neighbourBombs == 0) {
		const int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
		const int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
		for (int d = 0; d < 8; d++)
			floodReveal(m + dr[d], n + dc[d]);
	}
}

bool Field::checkWin() const {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (!cells[i][j]->isBomb && !cells[i][j]->isRevealed)
				return false;
	return true;
}

Position Field::findSafeCell(int exM, int exN) const {
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			if (!cells[i][j]->isBomb && (i != exM || j != exN))
				return { i, j };
	throw std::logic_error("No safe cells, field is incorrect");
}

TurnResult Field::makeTurn(int m, int n) {
	if (!inBounds(m, n))
		return trImpossible;
	if (cells[m][n]->isRevealed)
		return trImpossible;
	if (cells[m][n]->isFlagged)
		return trImpossible;

	if (firstMove) {
		firstMove = false;
		if (cells[m][n]->isBomb) {
			const int dr[] = { -1,-1,-1, 0, 0, 1, 1, 1 };
			const int dc[] = { -1, 0, 1,-1, 1,-1, 0, 1 };
			delete cells[m][n];
			cells[m][n] = new Sf_cell();

			for (int d = 0; d < 8; ++d) {
				int nr = m + dr[d], nc = n + dc[d];
				if (inBounds(nr, nc))
					cells[nr][nc]->neighbourBombs--;
			}
			Position pos = findSafeCell(m, n);
			delete cells[pos.row][pos.col];
			cells[pos.row][pos.col] = new Bomb();

			for (int d = 0; d < 8; ++d) {
				int nr = pos.row + dr[d], nc = pos.col + dc[d];
				if (inBounds(nr, nc))
					cells[nr][nc]->neighbourBombs++;
			}
			cells[m][n]->neighbourBombs = countNeighbourBombs(m, n);
			floodReveal(m, n);
			return checkWin() ? trWin : trBomb;
		}
		floodReveal(m, n);
		return checkWin() ? trWin : trOk;
	}

	if (cells[m][n]->isBomb) {
		cells[m][n]->activate();
		return trOver;
	}
	floodReveal(m, n);
	return checkWin() ? trWin : trOk;
}

void Field::placeFlag(int m, int n) {
	if (!inBounds(m, n) || cells[m][n]->isRevealed)
		return;
	if (!cells[m][n]->isFlagged) {
		cells[m][n]->isFlagged = true;
		flags++;
	}
	else {
		cells[m][n]->isFlagged = false;
		flags--;
	}
}

const Cell* Field::getCell(int m, int n) const {
	if (!inBounds(m, n))
		return nullptr;
	return cells[m][n];
}
