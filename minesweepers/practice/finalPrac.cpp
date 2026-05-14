/*
    Authors: Tommy Glennon and Amelia Haraldson
    Date: 5/5/2026
    Purpose: practice file for main function

*/


#include "cell.h"
#include "mineBoard.h"
#include <iostream>
#include <climits>
#include <ctime>
#include <string>
#include <fstream>

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

    // initialize score to zero
    int score = 0;


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
                score += board.cellReveal(usrCoords);
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
                    score += 10; // add 10 points for correctly flagging a mine
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

    // calculate end time and duration
    time(&endTime);
    duration = difftime(endTime, startTime);

    if (won) {
        cout << "You won! you took " << turns << " turns to flag " << board.getMineQuant() << " mines." << endl;
        cout << "Game duration: " << duration << " seconds." << endl;
        cout << "Your score is: " << score << endl;
    } else {
        cout << "You lost! you took " << turns << " turns to not flag " << board.getMineQuant() << " mines." << endl;
        cout << "Game duration: " << duration << " seconds." << endl;
        cout << "Your score is: " << score << endl;
    }

    // write results to a file
    ofstream outfile("game_results.txt");

    outfile << "Minesweeper Game Results\n";
    outfile << "-----------------------\n";
    outfile << "Score: " << score << "\n";
    outfile << "Turns Taken: " << turns << "\n";
    outfile << "Mines Flagged: " << minesFlagged << "\n";
    outfile << "Game Duration: " << duration << " seconds\n";

    if (won) {
        outfile << "Outcome: Won\n";
    } else {
        outfile << "Outcome: Lost\n";
    }

    outfile << "Final Board State:\n" << board.FinalBoard() << "\n";

    outfile.close();

}

int main() {
    int xaxis = intInputWrapper("board x axis: ");
    int yaxis = intInputWrapper("board y axis: ");
    int mineNumber = intInputWrapper("mine number: ");
    mineBoard game(xaxis, yaxis, mineNumber);
    menu(game);

    return 0;
}