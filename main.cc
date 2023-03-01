//Put your name(s) here: Jose Cuevas, Ayden Messick, Rohan Otal
//What bullet points did you do: proper class design, soundtrack, map traversal, saving/loading, style(?)
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

//turn_on_ncurses() and turn_off_ncurses() have been moved to their own file.



int main() {
	bool gameWin = false; //set to true if reach exit

	string newOrLoad;

	while (newOrLoad != "1" && newOrLoad != "2") {
		cout << "\t(1) NEW GAME\n\t(2) LOAD GAME" << endl;
		getline(cin, newOrLoad);
	}
	


	int treasure_collected = 0;

	Hero p1;
	Hero p2;
	Hero p3;
	p1.setHP(11);
	p2.setHP(12);
	p3.setHP(13);

	turn_on_ncurses();
	clear();
	turn_off_ncurses();

	int x = 0;
	int y = 0;
	

	if (newOrLoad == "2") {
		//load game
		ifstream load;
		load.open("save_data.txt");

		//load treasure
		string treasure_load;
		getline(load,treasure_load);
		treasure_collected = stoi(treasure_load);


		//load health and names
    	string p1Name_load, p2Name_load, p3Name_load;
    	string p1HP_load, p2HP_load, p3HP_load;

   		getline(load,p1Name_load);
   		getline(load,p1HP_load);
   		getline(load,p2Name_load);
   		getline(load,p2HP_load);
   		getline(load,p3Name_load);
   		getline(load,p3HP_load);
	
    	p1.set_name(p1Name_load);
    	p2.set_name(p2Name_load);
    	p3.set_name(p3Name_load);

		p1.setHP(stoi(p1HP_load));
		p2.setHP(stoi(p2HP_load));
		p3.setHP(stoi(p3HP_load));
		
		//load x and y positions
		string x_load, y_load;
		load >> x >> y;

		
		load.close();
	}
	else {
		//new game
		introSequence(p1,p2,p3); /////ENTER METAVERSE ID///////
		sleep(3);
	}



	turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON

	Map map;

	if (newOrLoad == "1") {
	x = Map::SIZE / 2;
	y = Map::SIZE / 2;
	}


	if (newOrLoad == "2") {
		map.map_load();

	}

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
				p1.setHP(p1.getHP() - 1);
				p2.setHP(p2.getHP() - 1);
				p3.setHP(p3.getHP() - 1);
				characterThoughts = "Whew, that was a close one...";
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

	
		//save << "reading and writing save data to and from this file..." <<  endl;
		save << treasure_collected << endl;
		save << p1.get_name() << endl << p1.getHP() << endl;
		save << p2.get_name() << endl << p2.getHP() << endl;
		save << p3.get_name() << endl << p3.getHP() << endl;
		save << x << " " << y << endl;
		save.close();
		
		map.map_save();
}

	
