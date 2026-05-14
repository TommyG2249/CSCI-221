#include <ncurses.h>
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include "mineBoard.h"
#include "cell.h"
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

void fillVector(vector<vector<string>>& vector, mineBoard board) {
    
    for (int i = 0; i < board.getHeight(); i++) {
        for (int j = 0; j < board.getWidth(); j++) {
            cell cellChoice = board.getCell(i, j);
            if (cellChoice.isFlagged()) {
                vector[i][j] = " F ";
            } else if (!cellChoice.isRevealed()) {
                vector[i][j] = " ~ ";
            } else if (cellChoice.isMine()) {
                vector[i][j] = " X ";
            } else {
                vector[i][j] = " " + to_string(cellChoice.getMines()) + " ";
            }
        }
    }
}

void setup_ncurses(bool cbreakBool, bool noechoBool) {
    initscr();
    if (cbreakBool) {
        cbreak();
    }
    if (noechoBool) {
        noecho();
    }
    if (has_colors()) {
        start_color();
    }
}

int main(int argc, char* argv[4]) {
    // check for correct usage
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <board width> <board height> <num mines>" << endl;
        return 1;
    }

    // create game variables
    time_t startTime = time(0);
    time_t endTime;
    double duration;

    int turns = 0;
    int minesFlagged = 0;

    bool finished = false;
    bool won = false;

    // set up ncurses with cbreak and noecho, and check for color support, and initialize keypad for stdscr
    setup_ncurses(true, true);
    keypad(stdscr, TRUE);

    // initialize terminal size and cursor
    pair<int,int> stdMax;
    pair<int,int> cs;
    
    // get terminal size and print it to the screen
    getmaxyx(stdscr, stdMax.first, stdMax.second);
    printw("%d, %d", stdMax.first, stdMax.second);
    refresh();

    // create dialogue box at the bottom of the screen, with a border and refresh it
    WINDOW* dialogue = newwin(4, stdMax.second-4, stdMax.first-6, 2);
    box(dialogue, 0, 0);
    wrefresh(dialogue);

    // initialize board size, and bin if too big for terminal, then create board window with border and refresh it
    bool yBinned = false;
    bool xBinned = false;

    int boardX = stoi(argv[1]);
    int boardY = stoi(argv[2]);

    if (boardX > stdMax.second-2) {
        printw("Board width too large, binning to %d", stdMax.second-2);
        refresh();
        boardX = stdMax.second-2;
        xBinned = true;
    }
    if (boardY > stdMax.first-8) {
        printw("Board height too large, binning to %d", stdMax.first-8);
        refresh();
        boardY = stdMax.first-8;
        yBinned = true;
    }

    WINDOW* board = newwin(boardY+2, boardX+2, 2, 2);
    keypad(board, TRUE);
    box(board, 0, 0);
    wrefresh(board);

    // get board size and print it to the screen, since the size entered to the program must be 2 smaller in each dimesnion than the size of the board window, to account for the border
    pair<int,int> boardMax;
    getmaxyx(board, boardMax.first, boardMax.second);

    // create 2d array of strings to represent the board, and fill it with ~
    vector<vector<string>> boardItems;
    boardItems.resize(boardY);
    for (int i = 0; i < boardY; i++) {
        boardItems[i].resize(boardX);
    }

    // create board and fill 2d array
    mineBoard boardObj(boardX, boardY, stoi(argv[3]));
    fillVector(boardItems, boardObj);

    int choice = 0;
    pair<int,int> highlight = {0,0};

    bool loop = true;
    while (loop) {
        // checks all cells in the board for if they are highlighted and prints to screen
        // if highlighted, turns on reverse attribute, prints the cell, then turns off reverse attribute so only the highlighted cell is reversed
        for (int i = 0; i < boardY; i++) {
            for (int j = 0; j < boardX; j++) {
                if (i == highlight.first && j == highlight.second) {
                    wattron(board, A_REVERSE);
                }
                // this is cast as a c string because ncurses handles char arrays
                mvwprintw(board, i+1, j+1, boardItems[i][j].c_str());
                wattroff(board, A_REVERSE);
            }
        }

        // choice capture and input handling
        choice = wgetch(board);
        switch (choice) {
            case KEY_UP:
                highlight.first--;
                if (highlight.first < 0) {
                    highlight.first = boardY - 1;
                }
                break;
            case KEY_DOWN:
                highlight.first++;
                if (highlight.first >= boardY) {
                    highlight.first = 0;
                }
                break;
            case KEY_LEFT:
                highlight.second--;
                if (highlight.second < 0) {
                    highlight.second = boardX - 1;
                }
                break;
            case KEY_RIGHT:
                highlight.second++;
                if (highlight.second >= boardX) {
                    highlight.second = 0;
                }
                break;
            case (int)'f':
                boardItems[highlight.first][highlight.second] = " F ";
                break;
            case 10:
                loop = false;
                break;
        }
    }

    endwin();

    return 0;
}