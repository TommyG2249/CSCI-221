//
// Created by Thomas Glennon on 4/27/26.
//

#ifndef CELL_H
#define CELL_H


class cell {
private:
    bool mine;
    bool flagged;
    int mines;
    bool revealed;
public:
    cell();

    int reveal();

    void undoReveal();

    void flag();

    void undoFlag();

    void unflag();

    void makeMine();

    void undoMine();

    void updateMines(int update);

    bool isMine();

    bool isRevealed();

    bool isFlagged();

    int getMines();

    void debug();

    void debugArr(int arr[]);
};


#endif // CELL_H