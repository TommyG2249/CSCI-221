// NCURSES DOC

// WILL NOT COMPILE, ONLY A .c FILE BECAUSE I LIKE THE COLOR STUFF ON VSCODE

/* ncurses is a tui library that turns your terminal into a text user application. 
It divides the terminal into rows and columns on terminal charactar width and height. 
Generally, the terminal character is twice as tall as wide. */

// allocates memory and clears and initializes the screen
initscr();

// deallocates memory and terminates ncurses
endwin();

// refreshes the screen to what's in memory, needed after every time something new added to screen EXCEPT FOR PRINT
refresh();

// de-buffers (all input, including command, function, option, etc is treated as a raw input) but maintains Cmd+C to close program
cbrake();

// de-buffers w no exception
raw();

// turns off input echo (when the screen prints what the user presses)
noecho();

// waits for user input and returns the user input. This is the main way to make the program wait for something
getch();

// prints a const char*[] to the buffer
printw("Hello, Ncurses");

// moves the cursor to int y and int x, cursor starts at 0,0 and moves every time something is printed
move(y, x);

// combines move and print, moves first
mvprintw(y, x, string);


// WINDOW METHODS
// creates a new window called win with size heightY and widthX at coordinates makeAtY and makeAtX
WINDOW* win = newwin(heightY, widthX, makeAtY, makeAtX);

// same as refresh, takes window as argument and refreshes the window
wrefresh(win);

// makes a border around the window, takes a window as param and also two ints
/* Each int represents a char number, 0 is default border, but 103, por ejemplo, will put g. 
First int is top and bottom, second is left and right */
box(win, 0, 0);

/* changes the border of a window, taking window as first param and then integers for the left, right, top, 
and bottom borders, then for top-left, top-right, bottom-left, and bottom-right corners. */
wborder(win, left, right, top, bottom, tlc, trc, blc, brc);

// moves in a window
wmove(win, y, x);

// prints to a window
wprintw(win, "%d" 55);

// moves first and prints to a window
mvwprintw(win, y, x, string);


// ATTRIBUTES

/* ATTRIBUTE TYPES
A_NORMAL
A_STANDOUT
A_REVERSE
A_BLINK
A_DIM
A_BOLD
A_PROTECT
A_INVIS
A_ALTCHARSET
A_CHARTEXT
*/

/* COLORS
COLOR_PAIR (id)
COLOR_BLACK 0
COLOR RED 1
COLOR_GREEN 2
COLOR_YELLOW 3
COLOR_BLUE 4
COLOR_MAGENTA 5
COLOR_CYAN 6
COLOR_WHITE 7
*/

// turns on an attribute, taking attribute type as param, commands coming after that output to screen output with the attribute
// also applies to colors
attron(A_X or COLOR_PAIR(id));

// turns off attr
attroff(A_X or COLOR_PAIR(id));

// for a specific window
wattron(win, A_X or COLOR_PAIR(id));

// for a specific window
wattroff(win, A_X or COLOR_PAIR(id));

// returns boolean for if the terminal has color output
has_colors();

// starts color output
start_color();

// initiates a pair of colors (all colors are foreground/background pairs) at the desired ID int val
init_pair(int id, COLOR_fore, COLOR_back);

// initiates a color to a color preset, accessed by the first param as either the int of the color slot or the color name
// next 3 params are red, green, and blue values, on a scale from 0-1000
init_color(COLOR_CYAN, 500, 500, 1000);

// CLAUDE TOLD ME this method checks if terminal can change color, then use COLORS const to determine how many color slots
// might be only 8, might be 255
can_change_color();


// CURSOR AND TERMINAL 

// gets the y and x coords of the cursor, takes window (stdscr is default) and two ints to write the coords
getyx(stdscr, yCursor, xCursor);

// gets the beginning coordinates of a window, takes same params as above
getbegyx(stdscr, yBeg, xBeg);

// gets the maximum values of window coords, basically length and width
getmaxyx(stdscr, yMax, xMax);

// BREAK FROM NORMAL DOC
/* it is best when creating windows in ncurses to start the program, get the terminal size, run all terminal checks, and from
there create windows based on the yMax and xMax variables, which will make the box sizes dynamic */

