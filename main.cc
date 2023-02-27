//Put your name(s) here: Jose Cuevas, Ayden Messick, Rohan Otal
//What bullet points did you do:
#include "map.h"
#include <unistd.h>
#include "actors.h"
#include "introUsernames.h"

const int MAX_FPS = 90; //Cap frame rate
const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

//Turns on full screen text mode
void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1, COLOR_WHITE, COLOR_BLACK); //Set up some color pairs
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
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


int main() {
	Hero p1;
	Hero p2;
	Hero p3;

	//these three lines are reduntant, because we're going to let the user set the names anyways!
	p1.set_name("HiroProtagonist");
	p2.set_name("Da5id");
	p3.set_name("GUEST(1)"); //this is the canon player 3 name
	
	//we could probably do the whole "enter username" part right here!"
	turn_on_ncurses();
	clear();
	turn_off_ncurses();

	introSequence(p1, p2, p3);
	sleep(3);

	turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
	/*use turn_off_ncurses() in conjuction with turn_on_ncurses()
	 if you want to cin/cout anything.*/

	Map map;

	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world

	int old_x = -1, old_y = -1;
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == RIGHT || ch == 'd') {
			x++;
			if (x >= Map::SIZE) x = Map::SIZE - 1; //Clamp value
		} else if (ch == LEFT || ch == 'a') {
			x--;
			if (x < 0) x = 0;
		} else if (ch == UP || ch == 'w') {
			y--;
			if (y < 0) y = 0;
		} else if (ch == DOWN || ch == 's') {
			y++;
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		} else if (ch == ERR) { //No keystroke
			; //Do nothing
		}
		//Stop flickering by only redrawing on a change
		if (x != old_x or y != old_y) {

			// here we do y, x because in map, i = y, and j = x
			if (map.getMap_xy(y,x) == Map::TREASURE) {
			  map.setMap_xy(y,x,Map::OPEN);
			  }
			  else if (map.getMap_xy(y,x) == Map::WALL or map.getMap_xy(y,x) == Map::WATER) {
			  x = old_x;
			  y = old_y;
			  }		 
			  /*Do something like this, idk
			  if (map.get(x,y) == Map::TREASURE) {
			  map.set(x,y,Map::OPEN);
			  money++;
			  } else if (map.get(x,y) == Map::WALL) {
			  x = old_x;
			  y = old_y;
			  }
			  */
			//clear(); //Put this in if the screen is getting corrupted
			map.draw(x, y);
			mvprintw(Map::DISPLAY + 1, 0, "X: %i Y: %i", x, y);
			/*basically, %i is a placeholder that gets replaced 
			  with the stuff you put after it.

			  see https://en.cppreference.com/w/c/io/fprintf for more info*/


			mvprintw(Map::DISPLAY + 2, 0, "[USER: %s / HP: %i ]",p1.get_name().c_str(), p1.getHP());
			mvprintw(Map::DISPLAY + 3, 0, "[USER: %s / HP: %i ]",p2.get_name().c_str(), p2.getHP());
			mvprintw(Map::DISPLAY + 4, 0, "[USER: %s / HP: %i ]",p3.get_name().c_str(), p3.getHP());
					


			refresh();
		}
		old_x = x;
		old_y = y;
		usleep(1'000'000 / MAX_FPS);
		}
		turn_off_ncurses();
	}
