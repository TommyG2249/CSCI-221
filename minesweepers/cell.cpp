//
// Created by Thomas Glennon on 4/27/26.
//

#include "cell.h"

#include <iostream>
using namespace std;

cell::cell() {
    flagged = false;
    mine = false;
    mines = 0;
    revealed = false;
}

void cell::flag() {
    if (!revealed) {
        flagged = true;
    }
}

// the undo methods are for debug purp
void cell::undoFlag() {
    flagged = false;
}

void cell::unflag() {
    if (!revealed && flagged) {
        flagged = false;
    }
}

int cell::reveal() {
    revealed = true;
    return mines;
}

void cell::undoReveal() {
    revealed = false;
}

void cell::makeMine() {
    mine = true;
    mines = -1;
}

void cell::undoMine() {
    mine = false;
    mines = 0;
}

void cell::updateMines(int update) {
    if (!mine) {
        mines = update;
    }
}

bool cell::isMine() {
    return mine;
}

bool cell::isRevealed() {
    return revealed;
}

bool cell::isFlagged() {
    return flagged;
}

int cell::getMines() {
    return mines;
}

void cell::debug() {
    cout << "Cell status: \n" << "Flagged: " << flagged << "\n"
    << "Mines: " << mines << "\n" << "Is mine: " << mine << "\n" << "Revealed: " << revealed << endl;
}

void cell::debugArr(int arr[]) {
    arr[0] = revealed;
    arr[1] = flagged;
    arr[2] = mine;
    arr[3] = mines;
}
