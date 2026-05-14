//
// Created by Thomas Glennon on 4/27/26.
//

#include "mineBoard.h"
#include "cell.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool contains(const vector<pair<int, int>> &array, pair<int, int> data) {
    bool contains = false;
    for (int i = 0; i < static_cast<int>(array.size()); i++) {
        if (array[i] == data) {
            contains = true;
        }
    }
    return contains;
}

mineBoard::mineBoard(int x, int y, int desiredMines) {
    // win contidition
    mineQuant = desiredMines;

    // seed rand()
    srand(time(0));

    // board sizing
    board.resize(y);
    for (int i = 0; i < y; i++) {
        board[i].resize(x);
    }

    // set mines
    pair<int,int> mineCoords = {0,0};
    vector<pair<int, int>> currentMineCoords;
    for (int i = 0; i < desiredMines; i++) {
        mineCoords.second = rand() % x;
        mineCoords.first = rand() % y;
        while (contains(currentMineCoords, mineCoords)) {
            mineCoords.second = rand() % x;
            mineCoords.first = rand() % y;
        }
        board[mineCoords.first][mineCoords.second].makeMine();
        currentMineCoords.push_back(mineCoords);
    }

    // set mine counts for non-mine cells
    int mineCount;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            mineCount = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < y && nj >= 0 && nj < x) {
                        if (board[ni][nj].isMine()) mineCount++;
                    }
                }
            }
            board[i][j].updateMines(mineCount);
        }
    }
}

void mineBoard::printBoard() {
    cout << "Printing board..." << endl;
    cout << "|_| is an unrevealed cell. |x| is a mine cell. |f| is a flagged cell. "
            "All other cells will contain numbers indicating how many mines surround them. \n" << endl;
    cout << "   ";
    for (int k = 0; k < static_cast<int>(board[0].size()); k++) {
                cout << k << " ";
            }
            cout << endl;
    for (int i = 0; i < static_cast<int>(board.size()); i++) {
        cout << i << " ";
        for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
            if (board[i][j].isFlagged()) {
                cout << "|f";
            } else if (!board[i][j].isRevealed()) {
                cout << "|_";
            } else if (board[i][j].isMine()) {
                cout << "|x";
            } else {
                cout << "|" << board[i][j].getMines();
            }
        }
        cout << "|" << endl;
    }
}

string mineBoard::FinalBoard() {
   string result = "";

    result += "   ";
    for (int k = 0; k < static_cast<int>(board[0].size()); k++) {
                result += to_string(k) + " ";
            }
            result += "\n";
    for (int i = 0; i < static_cast<int>(board.size()); i++) {
        result += to_string(i) + " ";
        for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
            if (board[i][j].isFlagged()) {
                result += "|f";
            } else if (!board[i][j].isRevealed()) {
                result += "|_";
            } else if (board[i][j].isMine()) {
                result += "|x";
            } else {
                if (board[i][j].getMines() == 0) {
                    result += "| ";
                } else {
                    result += "|" + to_string(board[i][j].getMines());
                }
            }
        }
        result += "|\n";
    }
    return result;
}


int mineBoard::cellReveal(pair<int,int> cellCoords) {
    cell& usrCell = board[cellCoords.second][cellCoords.first];

    // create revealed count to see how many cells are revealed in this turn, and return it at the end of the function to add to the score
    int revealedCount = 0;

    if (usrCell.isMine()) {
        return revealedCount;
    }
    if (usrCell.isRevealed()) {
        return revealedCount;
    }

    usrCell.reveal();
    revealedCount++;

    if (usrCell.getMines() > 0) {
        return revealedCount;
    }

    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            pair<int,int> newCellCoords = {cellCoords.first + di, cellCoords.second + dj};
            if (newCellCoords.first < 0 || newCellCoords.first >= static_cast<int>(board[0].size()) || newCellCoords.second < 0 || newCellCoords.second >= static_cast<int>(board.size())) {
                continue;
            }
            revealedCount += cellReveal(newCellCoords);
        }
    }
    return revealedCount;
}

int mineBoard::getMineQuant() {
    return mineQuant;
}

cell& mineBoard::getCell(pair<int,int> coords) {
    return board[coords.second][coords.first];
}

cell& mineBoard::getCell(int y, int x) {
    return board[y][x];
}

int mineBoard::getXSize() {
    return board[0].size();
}

int mineBoard::getYSize() {
    return board.size();
}
