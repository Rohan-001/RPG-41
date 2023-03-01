#pragma once
#include <unistd.h>

const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish

//Turns on full screen text mode
void turn_on_ncurses() {
    initscr();//Start curses mode
    start_color(); //Enable Colors if possible
    //           foreground   background
    init_pair(1, COLOR_WHITE, COLOR_BLACK); //standard tile
    init_pair(2, COLOR_CYAN, COLOR_BLACK); //water
    init_pair(3, COLOR_GREEN, COLOR_BLACK); //hero starting point
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); //treasure
    init_pair(5, COLOR_WHITE, COLOR_WHITE);//wall
    init_pair(6, COLOR_RED, COLOR_BLACK);//enemy
    clear();
    noecho();
    cbreak();
    timeout(TIMEOUT); //Set a max delay for key entry
}

//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
    clear();
    endwin(); // End curses mode
    if (system("clear")) {}
}

