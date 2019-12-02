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
    const char c_symbol_table[] = {       /* Define Symbol Table to be used for program */
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

    const char * ptr_symbol_table;
    ptr_symbol_table = c_symbol_table;

    int i_Indices[9];
    clear();
    refresh();

    /* Determine screen size */
    int row, col;
    getmaxyx(stdscr, row, col);
    int winRow = (row / 7) + 2, winCol = (col / 7);
    int mainX = 5, mainY = 5;

    /* Define Windows
     * Used for organising and displaying output
     */
    WINDOW * rules = newwin(3, col, 0, 0);
    WINDOW * main_board = newwin(9, 13, mainY, mainX);
    WINDOW * ColA = newwin(5, 3, mainY+2, mainX+2), *ColB = newwin(5, 3, mainY+2, mainX+5), *ColC = newwin(5, 3, mainY+2, mainX+8);
    
    /* Print to rules/instuctions Window */
    wprintw(rules, "Rules:");
    mvwprintw(rules, 1, 0, "Press 'Q' to exit.");
    mvwprintw(rules, 2, 0, "Press 'S' key to start.");
    mvwprintw(rules, 3, 0, "Press a number or 'a', 'b' or 'c' key to stop the corrosponding column.");
    wrefresh(rules);

    /* Print the game board */
    
    /* Draw Border */
    box(main_board, 0, 0);
    box(ColA, 0, 0);
    box(ColB, 0, 0);
    box(ColC, 0, 0);
    
    /* Print Initial output */
    wprintw(main_board, "");
    wprintw(ColA, "");
    wprintw(ColB, "");
    wprintw(ColC, "");

    // mvwprintw(main_board, 1, 1, "+");

    /* Refresh and draw */
    wrefresh(main_board);
    wrefresh(ColA);
    wrefresh(ColB);
    wrefresh(ColC);

    /* set buffer mode */
    nocbreak();
    halfdelay(1);

    bool running = true;
    bool is_Pressed = false;

    bool a_running = true;
    bool b_running = true;
    bool c_running = true;

    int key = tolower(wgetch(main_board));

    if (key == 'q') {
        dinit();
        return;
    }
    else {
        while (running) {
            key = tolower(wgetch(main_board));

            switch (key) {
            case '1':
            case 'a':
                a_running = false;
                break;

            case '2':
            case 'b':
                b_running = false;
                break;

            case '3':
            case 'c':
                c_running = false;
                break;

            case 'q':
                a_running = false;
                b_running = false;
                c_running = false;

            default:
                break;
            }

            for (int i = 0; i < 9; i++) {
                i_Indices[i] = rand() % 9;
            }


            const char Column_a_Row_b = c_symbol_table[i_Indices[1]];
            const char Column_b_Row_b = c_symbol_table[i_Indices[4]];
            const char Column_c_Row_b = c_symbol_table[i_Indices[7]];

            if (a_running) {
                mvwprintw(ColA, 1, 1, (c_symbol_table + i_Indices[0]));
                mvwprintw(ColA, 1, 1, (c_symbol_table + i_Indices[1]));
                mvwprintw(ColA, 1, 1, (c_symbol_table + i_Indices[2]));
                wrefresh(ColA);
            }

            if (b_running) {
                mvwprintw(ColB, 1, 1, (c_symbol_table + i_Indices[3]));
                mvwprintw(ColB, 1, 1, (c_symbol_table + i_Indices[4]));
                mvwprintw(ColB, 1, 1, (c_symbol_table + i_Indices[5]));
                wrefresh(ColB);
            }

            if (c_running) {
                mvwprintw(ColC, 1, 1, (c_symbol_table + i_Indices[6]));
                mvwprintw(ColC, 1, 1, (c_symbol_table + i_Indices[7]));
                mvwprintw(ColC, 1, 1, (c_symbol_table + i_Indices[8]));
                wrefresh(ColC);
            }

            if (!a_running && !b_running && !c_running) {
                mvwprintw(stdscr,12, 1, "Game over!");
                
                if (Column_a_Row_b == Column_b_Row_b && Column_b_Row_b == Column_c_Row_b && Column_a_Row_b == Column_c_Row_b) {
                    mvwprintw(stdscr, 13, 1, "All match!");
                    mvwprintw(stdscr, 14, 1, "Congradulations");
                }
                else if (Column_a_Row_b == Column_b_Row_b || Column_b_Row_b == Column_c_Row_b || Column_a_Row_b == Column_c_Row_b) {
                    mvwprintw(stdscr, 13, 1, "Two match!");
                    mvwprintw(stdscr, 14, 1, "Well Done");
                }
                else if (Column_a_Row_b != Column_b_Row_b && Column_b_Row_b != Column_c_Row_b && Column_a_Row_b != Column_c_Row_b) {
                    mvwprintw(stdscr, 13, 1, "No matches");
                    mvwprintw(stdscr, 14, 1, "Commiserations");
                }
                
                mvwprintw(stdscr, 15, 1, (c_symbol_table + i_Indices[0]));
                
                nocbreak();
                cbreak();
                wrefresh(stdscr);
                getch();
                dinit();
                return;
            }
        }

    }

}
