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

    printw("Hello World!, Press 'S' to continue, Anything else to exit.");
    refresh();

    int key = tolower(getch());
    if (key == 's') {
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

    int i_indices[9];
    clear();
    refresh();

    /* Determine screen size */
    int row, col;
    getmaxyx(stdscr, row, col);
    int main_x = 5;
    int main_y = 5;

    /* 
     * Define Windows
     * Used for organising and displaying output
     */
    WINDOW * rules = newwin(3, col, 0, 0);
    WINDOW * main_board = newwin(9, 13, main_y, main_x);
    WINDOW * col_a = newwin(5, 3, (main_y + 2), (main_x + 2));
    WINDOW * col_b = newwin(5, 3, (main_y + 2), (main_x + 5));
    WINDOW * col_c = newwin(5, 3, (main_y + 2), (main_x + 8));
    
    /* Print to rules/instuctions Window */
    wprintw(rules, "Rules:");
    mvwprintw(rules, 1, 0, "Press 'Q' to exit.");
    mvwprintw(rules, 2, 0, "Press 'S' key to start.");
    mvwprintw(rules, 3, 0, "Press a number or 'A', 'B' or 'C' key to stop the corrosponding column.");
    wrefresh(rules);

    /* Print the game board */
    
    /* Draw Border */
    box(main_board, 0, 0);
    box(col_a, 0, 0);
    box(col_b, 0, 0);
    box(col_c, 0, 0);
    
    /* Print Initial output */
    wprintw(main_board, "");
    wprintw(col_a, "");
    wprintw(col_b, "");
    wprintw(col_c, "");

    // mvwprintw(main_board, 1, 1, "+");

    /* Refresh and draw */
    wrefresh(main_board);
    wrefresh(col_a);
    wrefresh(col_b);
    wrefresh(col_c);

    /* set buffer mode */
    nocbreak();
    halfdelay(1);

    bool running = true;
    bool is_pressed = false;

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
                i_indices[i] = rand() % 9;
            }


            const char column_a_row_b = c_symbol_table[i_indices[1]];
            const char column_b_row_b = c_symbol_table[i_indices[4]];
            const char column_c_row_b = c_symbol_table[i_indices[7]];

            if (a_running) {
                mvwprintw(col_a, 1, 1, (c_symbol_table + i_indices[0]));
                mvwprintw(col_a, 1, 1, (c_symbol_table + i_indices[1]));
                mvwprintw(col_a, 1, 1, (c_symbol_table + i_indices[2]));
                wrefresh(col_a);
            }

            if (b_running) {
                mvwprintw(col_b, 1, 1, (c_symbol_table + i_indices[3]));
                mvwprintw(col_b, 1, 1, (c_symbol_table + i_indices[4]));
                mvwprintw(col_b, 1, 1, (c_symbol_table + i_indices[5]));
                wrefresh(col_b);
            }

            if (c_running) {
                mvwprintw(col_c, 1, 1, (c_symbol_table + i_indices[6]));
                mvwprintw(col_c, 1, 1, (c_symbol_table + i_indices[7]));
                mvwprintw(col_c, 1, 1, (c_symbol_table + i_indices[8]));
                wrefresh(col_c);
            }

            if (!a_running && !b_running && !c_running) {
                mvwprintw(stdscr,12, 1, "Game over!");
                
                if (column_a_row_b == column_b_row_b && column_b_row_b == column_c_row_b && column_a_row_b == column_c_row_b) {
                    mvwprintw(stdscr, 13, 1, "All match!");
                    mvwprintw(stdscr, 14, 1, "Congradulations");
                }
                else if (column_a_row_b == column_b_row_b || column_b_row_b == column_c_row_b || column_a_row_b == column_c_row_b) {
                    mvwprintw(stdscr, 13, 1, "Two match!");
                    mvwprintw(stdscr, 14, 1, "Well Done");
                }
                else if (column_a_row_b != column_b_row_b && column_b_row_b != column_c_row_b && column_a_row_b != column_c_row_b) {
                    mvwprintw(stdscr, 13, 1, "No matches");
                    mvwprintw(stdscr, 14, 1, "Commiserations");
                }
                
                mvwprintw(stdscr, 15, 1, (c_symbol_table + i_indices[0]));
                
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
