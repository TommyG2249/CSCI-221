#include <ncurses.h>
#include <utility>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

/* int test1() {
    
    // allocates memory and clears and initializes the screen
    initscr();

    // prints a const char*[] to the buffer
    printw("Hello, Ncurses");

    // refreshes the screen to what's in memory, needed after every time something new added to screen
    refresh();

    // waits for user input
    char i = getch();

    printw("%c", i);

    refresh();

    getch();

    // deallocates memory and terminates ncurses
    endwin();

    return 0;
}

int test2() {
    initscr();
    cbreak();
    noecho();

    int hy = 15;
    int hx = 30;
    int sy = 1;
    int sx = 1;

    WINDOW* win = newwin(hy, hx, sy, sx);
    keypad(win, TRUE);
    refresh();

    

    box(win, 0, 0);
    mvwprintw(win, 1, 1, "this is my box and its too long i think");
    wrefresh(win);

    getch();
    endwin();
    return 0;
} */

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

int main(int argc, char* argv[3]) {
    // check for correct usage
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <board width> <board height>" << endl;
        return 1;
    }

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
    for (int i = 0; i < boardY; i++) {
        for (int j = 0; j < boardX; j++) {
            boardItems[i][j] = " ~ ";
        }
    }

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
            case 10:
                loop = false;
                break;
        }
    }

    endwin();

    return 0;
}