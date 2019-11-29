/*
 * Fruit Machine V2 -- NOW WITH CURSES
 * 
 * OS Agnostic Curses based fruit machine using curses for CMP-104 end of module assesment.
 * This uses ncurses for *Nix and PDCurses (https://pdcurses.org/) for Win32 
 */

#include <curses.h>

#include <string>

#include <chrono> 
#include <thread> /* both libraries used in combination for sleep */

#include <stdlib.h>

using namespace std;

/* Prototypes */
void game_logic();

void sleep(int t) {
    /*
     * Wrapper function for stdlib sleep using thread and chrono
     * parameter 't' is time in milliseconds
     */
    std::this_thread::sleep_for (std::chrono::milliseconds(t));
}

void init(int t) {
    /*
     * Function calls all curses Initialiation functions,
     * Sets up the window, and finaly prints welcome message
     * takes int t - time(ms) to sleep after init
     */
    initscr();  /* starts curses */
    noecho();   /* suppresses character echos */
    cbreak();
    
    printw("Hello World!");
    refresh();

    sleep(t);

    clear();
    refresh();
}

void dinit() {
    /*
     * The opposite of init()
     * takes no args, clears the screen and exits curses
     */

    clear();
    refresh();
    endwin();
    return;
}


int main() {
    /*
     * Main function, simply calls init(), followed by checking to see if key c is pressed
     * if not exit program, if yes continue and run game_logic()
     */
    init(500);

    printw("Hello World!, Press 'C' to continue, Anything else to exit.");
    refresh();

    int key = toupper(getch());
    if (key == 'C') {
        game_logic();
        dinit();
        return 0;
    }
    else {
        dinit();
        return 0;
    }
}

void game_logic() {
    /*
     * Bulk of all logic for game,
     * Contains:
     *  -   infinite while loop in which all relevent functions are called
     *  -   symbol table used in display
     *  -   and code used to determine the size of the terminal
     */
    const char cSymbolTable[] = {       /* Define Symbol Table to be used for program */
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    };

    int iIndices[3];
    clear();
    refresh();

    /* Determine screen size */
    int row, col;
    getmaxyx(stdscr, row, col);
    int winRow = (row / 7) + 2, winCol = (col / 7);

    /* Define Windows
     * Used for organising and displaying output
     */
    WINDOW * rules = newwin(3, col, 0, 0);
    WINDOW * mainBoard = newwin(7, 13, winRow, winCol);
    
    /* Print to rules/instuctions Window */
    wprintw(rules, "Rules");
    mvwprintw(rules, 1, 0, "LOL");
    wrefresh(rules);

    /* Print main game board */
    box(mainBoard, 0, 0);           /* Draw Border */
    wprintw(mainBoard, "");         /* Print Initial output */
    //wrefresh(mainBoard);            /* Refresh and draw */
    
    int key;
    while (true) {
        for (int i = 0; i < 3; i++) {
            iIndices[i] = rand() % 9 + 1;
        }
        key = toupper(wgetch(mainBoard));
        if (key == 'Q') {
            dinit();
            return;
        }
        else {
            mvwprintw(mainBoard, 0, 0, "H");
            wrefresh(mainBoard);
        }
    }
}

