//
// Created by Thomas Glennon on 4/27/26.
//

#ifndef MINEBOARD_H
#define MINEBOARD_H
#include <vector>
#include <string>
#include "cell.h"
using namespace std;


class mineBoard {
private:
    vector<vector<cell>> board;
    int mineQuant;
public:
    mineBoard(int x, int y, int desiredMines);

    void printBoard();

    string FinalBoard();

    int cellReveal(pair<int,int> cellCoords);

    int getMineQuant();

    cell& getCell(pair<int,int> coords);

    cell& getCell(int y, int x);

    int getXSize();

    int getYSize();
};


#endif //MINEBOARD_H