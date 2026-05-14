#include <ncurses.h>
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include "mineBoard.h"
#include "cell.h"
#include <deque>
#include <fstream>
using namespace std;

// current bugs:
// - if you flag a cell, then reveal it, it will still count as flagged and can cause a win condition to trigger if you flag all the mines, then reveal them all, then

// color index:
// 1 goldish
// 2 blue
// 3 green
// 4 yellow
// 5 red
// 6 white on black
// 7 light grey on black

void fillVector(vector<vector<string>>& vector, mineBoard &board) {
    
    for (int i = 0; i < board.getYSize(); i++) {
        for (int j = 0; j < board.getXSize(); j++) {
            cell& cellChoice = board.getCell(i, j);
            if (cellChoice.isFlagged()) {
                vector[i][j] = "F";
            } else if (!cellChoice.isRevealed()) {
                vector[i][j] = "~";
            } else if (cellChoice.isMine()) {
                vector[i][j] = "X";
            } else {
                if (cellChoice.getMines() == 0) {
                    vector[i][j] = " ";
                } else {
                vector[i][j] = to_string(cellChoice.getMines());
                }
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
        
        // flag color
        init_color(16, 500, 500, 0);
        init_pair(1, 16, COLOR_BLACK);

        // one mine color
        init_pair(2, COLOR_BLUE, COLOR_BLACK);

        // two mine color
        init_color(17, 0, 700, 0);
        init_pair(3, 17, COLOR_BLACK);

        // three mine color
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);

        // four+ mine color
        init_pair(5, COLOR_RED, COLOR_BLACK);

        // dialogue color
        init_color(18, 600, 600, 600);
        // active dialogue color
        init_pair(6, COLOR_WHITE, COLOR_BLACK);
        // old dialogue color
        init_pair(7, 18, COLOR_BLACK);
    }
}

pair<int,int> boardLoop(mineBoard board, WINDOW* win, vector<vector<string>> &boardItems, char &action) {
    int choice = 0;
    pair<int,int> highlight = {0,0};
    bool loop = true;

    while (loop) {
        // checks all cells in the board for if they are highlighted and prints to screen
        // if highlighted, turns on reverse attribute, prints the cell, then turns off reverse attribute so only the highlighted cell is reversed
        for (int i = 0; i < board.getYSize(); i++) {
            for (int j = 0; j < board.getXSize(); j++) {
                if (i == highlight.first && j == highlight.second) {
                    wattron(win, A_REVERSE);
                }
                // this is cast as a c string because ncurses handles char arrays

                if (boardItems[i][j] == "F") {
                    wattron(win, COLOR_PAIR(1));
                }
                if (boardItems[i][j] == "1") {
                    wattron(win, COLOR_PAIR(2));
                }
                if (boardItems[i][j] == "2") {
                    wattron(win, COLOR_PAIR(3));
                }
                if (boardItems[i][j] == "3") {
                    wattron(win, COLOR_PAIR(4));
                }
                if (boardItems[i][j] == "4" || boardItems[i][j] == "5" || boardItems[i][j] == "6" || boardItems[i][j] == "7" || boardItems[i][j] == "8") {
                    wattron(win, COLOR_PAIR(5));
                }

                mvwprintw(win, i+1, j+1, boardItems[i][j].c_str());
                wattroff(win, COLOR_PAIR(1));
                wattroff(win, COLOR_PAIR(2));
                wattroff(win, COLOR_PAIR(3));
                wattroff(win, COLOR_PAIR(4));
                wattroff(win, COLOR_PAIR(5));
                wattroff(win, A_REVERSE);
            }
        }

        // choice capture and input handling
        choice = wgetch(win);
        switch (choice) {
            case KEY_UP:
                highlight.first--;
                if (highlight.first < 0) {
                    highlight.first = board.getYSize() - 1;
                }
                break;
            case KEY_DOWN:
                highlight.first++;
                if (highlight.first >= board.getYSize()) {
                    highlight.first = 0;
                }
                break;
            case KEY_LEFT:
                highlight.second--;
                if (highlight.second < 0) {
                    highlight.second = board.getXSize() - 1;
                }
                break;
            case KEY_RIGHT:
                highlight.second++;
                if (highlight.second >= board.getXSize()) {
                    highlight.second = 0;
                }
                break;
            case (int)'f':
            case (int)'F':
                action = 'f';
                loop = false;
                break;
            case (int)'r':
            case (int)'R':
                action = 'r';
                loop = false;
                break;
            case (int)'q':
            case (int)'Q':
                return {-1, -1};
                break;
            default:
                break;
        }
    }
    return highlight;
}

int boardChecker(mineBoard &board, pair<int,int> coords, char action, int &minesFlagged, int &turns, int &score) {
    pair<int,int> flipCoords = {coords.second, coords.first};
    cell& cellChoice = board.getCell(flipCoords);
    if (action == 'f') {
        if (cellChoice.isFlagged()) {
            if (cellChoice.isMine()) {
                minesFlagged--;
                score -= 10; // remove 10 points for unflagging a mine
            }
            cellChoice.unflag();
            turns++;
            return 10;
        }
        if (cellChoice.isRevealed()) {
            return 11;
        }
        if (cellChoice.isMine()) {
            minesFlagged++;
            cellChoice.flag();
            turns++;
            score += 10; // add 10 points for correctly flagging a mine
            return 12;
        }
        cellChoice.flag();
        turns++;
        return 13;
    }
    if (action == 'r') {
        if (cellChoice.isRevealed()) {
            return 1;
        }
        turns++;
        if (cellChoice.isMine()) {
            return 0;
        }
        score += board.cellReveal(flipCoords);
        return 2;
    }
    throw invalid_argument("invalid return in boardChecker");
}

WINDOW* createWindow(int height, int width, int starty, int startx) {
    WINDOW* local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0); 
    wrefresh(local_win); 
    return local_win;
}

void printDialogueColor(WINDOW* win, string message, deque<string> &messageQueue, int pair) {

    int xMax, yMax;
    getmaxyx(win, yMax, xMax);

    messageQueue.push_back(message);
    if (static_cast<int>(messageQueue.size()) > yMax - 2) {
        messageQueue.pop_front();
    }
    werase(win);
    box(win, 0, 0);
    for (int i = 0; i < static_cast<int>(messageQueue.size()); i++) {
        if (i == static_cast<int>(messageQueue.size()) - 1) {
            wattron(win, COLOR_PAIR(pair));
        } else {
            wattron(win, COLOR_PAIR(7));
        }
        mvwprintw(win, i+1, 1, messageQueue[i].c_str());
        wattroff(win, COLOR_PAIR(pair));
        wattroff(win, COLOR_PAIR(7));
    }
    wrefresh(win);
}

void printDialogue(WINDOW* win, string message, deque<string> &messageQueue) {

    int xMax, yMax;
    getmaxyx(win, yMax, xMax);

    messageQueue.push_back(message);
    if (static_cast<int>(messageQueue.size()) > yMax - 2) {
        messageQueue.pop_front();
    }
    werase(win);
    box(win, 0, 0);
    for (int i = 0; i < static_cast<int>(messageQueue.size()); i++) {
        if (i == static_cast<int>(messageQueue.size()) - 1) {
            wattron(win, COLOR_PAIR(6));
        } else {
            wattron(win, COLOR_PAIR(7));
        }
        mvwprintw(win, i+1, 1, messageQueue[i].c_str());
        wattroff(win, COLOR_PAIR(6));
        wattroff(win, COLOR_PAIR(7));
    }
    wrefresh(win);
}

bool getWinCoords(pair<int,int> screenSize, pair<int,int> inputSize, pair<int,int> &boardStart, pair<int,int> &boardSize, pair<int,int> &dialogueStart, pair<int,int> &dialogueSize) {
    int boardX = inputSize.second;
    int boardY = inputSize.first;
    bool binned = false;

    if (boardX > screenSize.second-4) {
        boardX = screenSize.second-4;
        binned = true;
    }
    if (boardY > screenSize.first-11) {
        boardY = screenSize.first-11;
        binned = true;
    }

    boardStart = {2, 2};
    boardSize = {boardY+2, boardX+2};
    dialogueStart = {boardSize.first + 2, 2};
    dialogueSize = {screenSize.first - dialogueStart.first - 2, screenSize.second - 4};
    return binned;
}

int main(int argc, char* argv[4]) {
    // check for correct usage
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <board width> <board height> <num mines>" << endl;
        return 1;
    }

    // set up ncurses
    setup_ncurses(true, true);

    // get terminal size, set up window coordinates, and create windows
    pair<int,int> screenSize, boardStart, boardSize, dialogueStart, dialogueSize, playerCoords;
    getmaxyx(stdscr, screenSize.first, screenSize.second);
    bool binned = getWinCoords(screenSize, {stoi(argv[2]), stoi(argv[1])}, boardStart, boardSize, dialogueStart, dialogueSize);
    WINDOW* board = createWindow(boardSize.first, boardSize.second, boardStart.first, boardStart.second);
    keypad(board, TRUE);
    WINDOW* dialogue = createWindow(dialogueSize.first, dialogueSize.second, dialogueStart.first, dialogueStart.second);
    
    // inicate if the board size was binned
    deque<string> messageQueue;
    messageQueue.push_back("Initializing game...");
    if (binned) {
        printDialogue(dialogue, "Board size too large for terminal, window binned " + to_string(boardSize.second) + " and " + to_string(boardSize.first) + " to fit.", messageQueue);
    } else {
        printDialogue(dialogue, "Game window size set to " + to_string(boardSize.second) + " and " + to_string(boardSize.first) + ". ", messageQueue);
    }
    printDialogue(dialogue, "Game board size set to " + to_string(boardSize.second-2) + " and " + to_string(boardSize.first-2) + ". ", messageQueue);

    // set up game vairbales
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
    char action;

    // create board and fill 2d array
    vector<vector<string>> boardItems;
    boardItems.resize(boardSize.first - 2);
    for (int i = 0; i < boardSize.first - 2; i++) {
        boardItems[i].resize(boardSize.second - 2);
    }

    mineBoard boardObj(boardSize.second - 2, boardSize.first - 2, stoi(argv[3]));
    fillVector(boardItems, boardObj);

    printDialogueColor(dialogue, "Welcome to Minesweeper! Use arrow keys to move, F to flag/unflag, R to reveal, and Q to quit.", messageQueue, 2);

    while (!finished) {
        playerCoords = boardLoop(boardObj, board, boardItems, action);
        if (playerCoords.first == -1 && playerCoords.second == -1) {
            printDialogueColor(dialogue, "Are you sure you want to quit? Press Q to confirm.", messageQueue, 5);
            char confirm = wgetch(dialogue);
            if (confirm == 'q') {
                endwin();
                return 0;
            }
        } else {
            int result = boardChecker(boardObj, playerCoords, action, minesFlagged, turns, score);
            fillVector(boardItems, boardObj);
            switch (result) {
                case 0:
                    finished = true;
                    break;
                case 1:
                    printDialogue(dialogue, "Cell at (" + to_string(playerCoords.second) + ", " + to_string(playerCoords.first) + ") already revealed!", messageQueue);
                    break;
                case 2:
                    printDialogue(dialogue, "Cell at (" + to_string(playerCoords.second) + ", " + to_string(playerCoords.first) + ") revealed.", messageQueue);
                    break;
                case 10:
                    printDialogue(dialogue, "Cell at (" + to_string(playerCoords.second) + ", " + to_string(playerCoords.first) + ") unflagged.", messageQueue);
                    break;
                case 11:
                    printDialogue(dialogue, "Cell at (" + to_string(playerCoords.second) + ", " + to_string(playerCoords.first) + ") cannot be flagged, it's already revealed.", messageQueue);
                    break;
                case 12:
                    printDialogue(dialogue, "Cell at (" + to_string(playerCoords.second) + ", " + to_string(playerCoords.first) + ") flagged.", messageQueue);
                    break;
                case 13:
                    printDialogue(dialogue, "Cell at (" + to_string(playerCoords.second) + ", " + to_string(playerCoords.first) + ") flagged.", messageQueue);
                    break;  
                default:
                    break;
            }
            if (minesFlagged == boardObj.getMineQuant()) {
                finished = true;
                won = true;
            }
        }
    }
    if (won) {
        time(&endTime);
        duration = difftime(endTime, startTime);
        printDialogueColor(dialogue, "You won! you took " + to_string(turns) + " turns to flag " + to_string(boardObj.getMineQuant()) + 
        " mines.\n Game duration: " + to_string(duration) + " seconds.\n Press any key to exit.", messageQueue, 3);
    } else {
        time(&endTime);
        duration = difftime(endTime, startTime);
        printDialogueColor(dialogue, "You lost! you took " + to_string(turns) + " turns to not flag " + to_string(boardObj.getMineQuant()) + 
        " mines.\n Game duration: " + to_string(duration) + " seconds.\n Press any key to exit.", messageQueue, 5);
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

    outfile << "Final Board State:\n" << boardObj.FinalBoard() << "\n";

    outfile.close();

    wgetch(dialogue);

    endwin();

    return 0;
}
