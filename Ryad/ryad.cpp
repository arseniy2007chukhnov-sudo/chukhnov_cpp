#include <iostream>
#include "ryad.h"

using namespace std;

Field::Field(bool isRedFirst)
{
    clear(isRedFirst);
}

void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

bool Field::makeTurn(int column)
{
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;

    int i = column - 1;

    for (int j = 0; j < FIELD_HEIGHT; j++)
        if (cells[i][j] == EMPTY)
        {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner();
            isRedTurn = !isRedTurn;
            return true;
        }

    return false;
}

bool Field::isWon(bool red) const
{
    return winner == (red ? RED : YELLOW);
}

Cell Field::getCell(int i, int j) const
{
    return cells[i][j];
}

bool Field::isRedTurnNow() const
{
    return isRedTurn;
}

bool Field::isOver() const
{
    if (winner != EMPTY)
        return true;

    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            if (cells[i][j] == EMPTY)
                return false;

    return true;
}

const int DIR_NUMBER = 4;
const int di[] = { 1, 0, 1, 1 };
const int dj[] = { 0, 1, -1, 1 };
const int WIN_LENGTH = 4;

void Field::checkWinner()
{
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            Cell start = cells[i][j];
            if (start == EMPTY)
                continue;

            for (int dir = 0; dir < DIR_NUMBER; dir++)
            {
                int length = 0, iline = i, jline = j;

                while (++length < WIN_LENGTH)
                {
                    iline += di[dir];
                    jline += dj[dir];

                    if (iline < 0 || iline >= FIELD_WIDTH ||
                        jline < 0 || jline >= FIELD_HEIGHT)
                        break;

                    if (cells[iline][jline] != start)
                        break;
                }

                if (length == WIN_LENGTH)
                {
                    winner = start;
                    return;
                }
            }
        }
}

void Field::print() const
{
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--)
    {
        for (int i = 0; i < FIELD_WIDTH; i++)
        {
            char c = '.';
            if (cells[i][j] == RED) c = 'R';
            if (cells[i][j] == YELLOW) c = 'Y';
            cout << c << " ";
        }
        cout << endl;
    }
    cout << "1 2 3 4 5 6 7" << endl;
}

void Field::printResult() const
{
    if (winner == RED)
        cout << "Победил красный" << endl;
    else if (winner == YELLOW)
        cout << "Победил жёлтый" << endl;
    else
        cout << "Ничья" << endl;
}
