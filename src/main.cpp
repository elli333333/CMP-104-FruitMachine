/*
 * Fruit Machine V2 -- NOW WITH CURSES
 * 
 * OS Agnostic Curses based fruit machine using curses for CMP-104 end of module assesment.
 * This uses ncurses for *Nix and PDCurses (https://pdcurses.org/) for Win32 
 */

#include "PDCurses/curses.h"

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
    int mainX = 5, mainY = 4;

    /* Define Windows
     * Used for organising and displaying output
     */
    WINDOW * rules = newwin(3, col, 0, 0);
    WINDOW * mainBoard = newwin(9, 13, mainY, mainX);
    WINDOW * ColA = newwin(5, 3, mainY+2, mainX+2), *ColB = newwin(5, 3, mainY+2, mainX+5), *ColC = newwin(5, 3, mainY+2, mainX+8);
    
    /* Print to rules/instuctions Window */
    wprintw(rules, "Rules:");
    mvwprintw(rules, 1, 0, "Press 'Q' to exit.");
    mvwprintw(rules, 2, 0, "Press 'S' key to start.");
    wrefresh(rules);

    /* Print the game board */
    
    /* Draw Border */
    box(mainBoard, 0, 0);
    box(ColA, 0, 0);
    box(ColB, 0, 0);
    box(ColC, 0, 0);
    
    /* Print Initial output */
    wprintw(mainBoard, "");
    wprintw(ColA, "");
    wprintw(ColB, "");
    wprintw(ColC, "");

    // mvwprintw(mainBoard, 1, 1, "+");

    /* Refresh and draw */
    wrefresh(mainBoard);
    wrefresh(ColA);
    wrefresh(ColB);
    wrefresh(ColC);

    /* set buffer mode */
    nocbreak();
    halfdelay(1);

    bool running = true, is_Pressed = false;
    int key;
    while (running == true) {
        key = toupper(wgetch(mainBoard));
        if (key == 'Q') {
            dinit();
            return;
        }
        else if (wgetch(mainBoard) == ERR) {
            ;
        }
        else if (toupper(wgetch(mainBoard)) == 'S') {
            while(is_Pressed == false) {
                for (int i = 0; i < 3; i++) {
                    iIndices[i] = rand() % 9 + 1;
                }
                if (wgetch(mainBoard) != ERR) {
                    is_Pressed = true;
                }
                else {
                    mvwprintw(ColA, 1, 1, "H");
                    wrefresh(ColA);
                }
            }
        }
        else{
            ;
        }
        
    }
}
