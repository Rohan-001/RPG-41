//Put your name(s) here: Jose Cuevas, Ayden Messick, Rohan Otal
//What bullet points did you do: proper class design, soundtrack
//soundtrack at https://youtu.be/2Mn54KP2WWM
#include "map.h"
#include <unistd.h>
#include "actors.h"
#include "introUsernames.h"
#include <fstream>
#include "toggleNCurses.h"
#include "combat.h"

const int MAX_FPS = 90; //Cap frame rate

const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;


/*
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
}*/


int main() {
	bool gameWin = false; //set to true if reach exit
	
	ifstream load;
	
	int treasure_collected = 0;

	Hero p1;
	Hero p2;
	Hero p3;
	p1.setHP(11);
	p2.setHP(12);
	p3.setHP(13);

	load.open("save_data.txt");

	string treasureCount;
	getline(load,treasureCount);
	
	//TODO these only work with strings. will need to stoi all the names later
	string p1Name_load, p2Name_load, p3Name_load;
	string p1HP_load, p2HP_load, p3HP_load;


	//reads from file into variables declared above
	getline(load,p1Name_load);
	getline(load,p1HP_load);
	getline(load,p2Name_load);
	getline(load,p2HP_load);
	getline(load,p3Name_load);
	getline(load,p3HP_load);

	//FIXME this doesn't work!
	p1.set_name(p1Name_load);
	p2.set_name(p2Name_load);
	p3.set_name(p3Name_load);


	load.close();




	turn_on_ncurses();
	clear();
	turn_off_ncurses();

	introSequence(p1, p2, p3); //this is the /////ENTER METAVERSE ID:///// section
	sleep(3);

	turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON

	Map map;

	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world

	int old_x = -1, old_y = -1;

	string characterThoughts = "Hope we make it out of here in time...";
	default_random_engine randDialogue;

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

			characterThoughts = "I can see the exit beacon to the north!";
			
			// here we do y, x because in map, i = y, and j = x
			if (map.getMap_xy(y,x) == Map::TREASURE) {
				treasure_collected++;
			  	map.setMap_xy(y,x,Map::OPEN);

				uniform_int_distribution<int> randTreasure(1,3);
				switch(randTreasure(randDialogue)) {
					case 1:
						characterThoughts = "oh, it's just an NFT.";
						break;
					case 2:
						characterThoughts = "It's a subscription code! Oh, that service shut down a few days ago...";
						break;
					case 3:
						characterThoughts = "That's a funny meme. I think I'll take it.";
							break;

				}


			  }
			  else if (map.getMap_xy(y,x) == Map::WALL or map.getMap_xy(y,x) == Map::WATER) {
			  x = old_x;
			  y = old_y;
			  characterThoughts = "ah, yes. collision";
			  }
			else if (map.getMap_xy(y,x) == Map::MONSTER) {
				//COMBAT TIME
				turn_off_ncurses();
				doCombat();
				turn_on_ncurses();
				map.setMap_xy(y,x,Map::OPEN);
				characterThoughts = "that was a close one...";
			}
			else if (map.getMap_xy(y,x) == Map::EXIT) {
				gameWin = true;
				break;
			}

			map.draw(x, y);
			mvprintw(Map::DISPLAY + 1, 0, "X: %i Y: %i", x, y);
			/*basically, %i is a placeholder that gets replaced 
			  with the stuff you put after it.

			  see https://en.cppreference.com/w/c/io/fprintf for more info*/


			mvprintw(Map::DISPLAY + 2, 0, "[ITEMS COLLECTED: %i]",treasure_collected); 
			mvprintw(Map::DISPLAY + 3, 0, "[USER: %s / HP: %i ]",p1.get_name().c_str(), p1.getHP());
			mvprintw(Map::DISPLAY + 4, 0, "[USER: %s / HP: %i ]",p2.get_name().c_str(), p2.getHP());
			mvprintw(Map::DISPLAY + 5, 0, "[USER: %s / HP: %i ]",p3.get_name().c_str(), p3.getHP());
			mvprintw(Map::DISPLAY + 6, 0, "");
			clrtoeol(); //should clear the line
			mvprintw(Map::DISPLAY + 6, 0, "\"%s\"", characterThoughts.c_str());

			refresh();
		}
		old_x = x;
		old_y = y;
		usleep(1'000'000 / MAX_FPS);
		}
		turn_off_ncurses();
	
		if (gameWin) {
			outroSequence();
		}
		else {cout << "Game saved." << endl;}

		ofstream save;
		save.open("save_data.txt");

	
		save << "reading and writing save data to and from this file..." <<  endl;
		save << treasure_collected << endl;
		save << p1.get_name() << endl << p1.getHP() << endl;
		save << p2.get_name() << endl << p2.getHP() << endl;
		save << p3.get_name() << endl << p3.getHP() << endl;
		save.close();

}

	
