/*
    Author: Tommy Glennon and Amelia Haraldson
    Date: 5/5/2026
    Citation: https://docs.vultr.com/cpp/standard-library/ctime/time 

*/
#include "cell.h"
#include "mineBoard.h"
#include <iostream>
#include <climits>
#include <ctime>

using namespace std;

int intInputWrapper(string message) {
    cout << message << endl;
    int result;
    while (!(cin >> result)) {
        cout << "Invalid input. Please enter an integer: ";
        cin.clear(); 
        cin.ignore(INT_MAX, '\n');
    }
    return result;
}

pair<int,int> promptCellChoice(mineBoard& board) {
    pair<int,int> usrCoords;
    usrCoords.first = intInputWrapper("row number");
    usrCoords.second = intInputWrapper("column number");
    while (usrCoords.first < 0 || usrCoords.first >= board.getXSize() || usrCoords.second < 0 || usrCoords.second >= board.getYSize()) {
        cout << "out of range" << endl;
        usrCoords.first = intInputWrapper("row number");
        usrCoords.second = intInputWrapper("column number");
    }
    return usrCoords;
}

void menu(mineBoard& board) {
    cout << "game start" << endl;

    // create time variables for the start and end of the game, and calculate the duration at the end
    time_t startTime = time(0);
    time_t endTime;
    double duration;

    int turns = 0;
    int minesFlagged = 0;

    bool finished = false;
    bool won = false;

    int usrChoice;

    board.printBoard();

    string choices = "[1] Reveal a cell\n[2] Flag a cell\n[3] Unflag a cell\n[0] Quit";

    while (!finished) {
        board.printBoard();
        usrChoice = intInputWrapper(choices);
        switch(usrChoice) {
            case 1: {
                pair<int,int> usrCoords = promptCellChoice(board);
                cell& cellChoice = board.getCell(usrCoords);
                if (cellChoice.isMine()) finished = true;
                board.cellReveal(usrCoords);
                turns++;
                break;
            }
            case 2: {
                cell& cellChoice = board.getCell(promptCellChoice(board));
                if (cellChoice.isFlagged()) {
                    cout << "cell alr flagged" << endl;
                    break;
                }
                if (cellChoice.isRevealed()) {
                    cout << "cant flag a revealed cell" << endl;
                    break;
                }
                if (cellChoice.isMine()) {
                    minesFlagged++;
                }
                cellChoice.flag();
                turns++;
                break;
            }
            case 3: {
                cell& cellChoice = board.getCell(promptCellChoice(board));
                if (!cellChoice.isFlagged()) {
                    cout << "cell not flagged" << endl;
                    break;
                }
                if (cellChoice.isMine()) {
                    minesFlagged--;
                }
                cellChoice.unflag();
                turns++;
                break;
            }
            default:
                return;
        } // switch

        if (minesFlagged == board.getMineQuant()) {
            won = true;
            finished = true;
        } // if

    } // while

    if (won) {
        time(&endTime);
        duration = difftime(endTime, startTime);
        cout << "You won! you took " << turns << " turns to flag " << board.getMineQuant() << " mines." << endl;
        cout << "Game duration: " << duration << " seconds." << endl;
    } else {
        time(&endTime);
        duration = difftime(endTime, startTime);
        cout << "You lost! you took " << turns << " turns to not flag " << board.getMineQuant() << " mines." << endl;
        cout << "Game duration: " << duration << " seconds." << endl;
    }

}

int main() {
    int xaxis = intInputWrapper("board x axis: ");
    int yaxis = intInputWrapper("board y axis: ");
    int mineNumber = intInputWrapper("mine number: ");
    mineBoard game(xaxis, yaxis, mineNumber);
    menu(game);

    return 0;
}