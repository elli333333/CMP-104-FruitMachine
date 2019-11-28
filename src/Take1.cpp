/*
 * This builds on both Linux (GCC 9.2.0) and MSVC (MSVC2019)
 * And it works (mostly, printf character substitution is broken),
 * however this got scrapped early in favour of a better option (this is awful)
 */ 


#include <iostream>
#include <stdio.h>

/*
 * Preprocessor directives to determine os type
 * sets int 'sys_type' to 0 if os type = WIN32 (also captures WIN64)
 * if not set 'sys_type' to 1 and assume POSIX
 * 'sys_type' used later for system calls
 */
#if defined(_WIN32)
    #define sys_type 0
#else
    #define sys_type 1
#endif

void console_clear(int sys) {
    /*
    * clears screen using system calls,
    * takes int as argument: 
    *                         0 =  Windows Style system clear call
    *                         1 = POSIX Style system clear call
    * Apparently this is bad, sod it. (see http://www.cplusplus.com/articles/j3wTURfi/)
    */ 
    if (sys == 0) {
        system("CLS");
    }
    else if (sys == 1) {
        system("clear");
    }
}

void console_write(char r1c1, char r1c2, char r1c3, char r2c1, char r2c2, char r2c3, char r3c1, char r3c2, char r3c3) {
    /*
     * Using printf, format strings and ASCII drawing characters
    */
    //printf("Hello World! \n");
    printf("┌─────────┐ \n");
    printf("│┌─┐┌─┐┌─┐│ \n");
    printf("││%c││%c││%c││ \n", r1c1, r1c2, r1c3);
    printf("││%c││%c││%c││ \n", r2c1, r2c2, r2c3);
    printf("││%c││%c││%c││ \n", r3c1, r3c2, r3c3);
    printf("│└─┘└─┘└─┘│\n");
    printf("└─────────┘ \n");



}

int main() {
    char r1c1, r1c2, r1c3, r2c1, r2c2, r2c3, r3c1, r3c2, r3c3;
    console_write(r1c1, r1c2, r1c3, r2c1, r2c2, r2c3, r3c1, r3c2, r3c3);
    std::cin.ignore();
    console_clear(sys_type);
    return 0;
}