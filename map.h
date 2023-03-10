#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include "./levels.h"
#include <fstream>
using namespace std; //Boo hiss



class Map {
	vector<vector<char>> map;


	default_random_engine gen;
	public:
	//Write a getter and a setter to get/set the characters in the map
	char getMap_xy(int userX, int userY) {
		return map.at(userX).at(userY);
	}
	
	void setMap_xy(int userX, int userY, char tile) {
		map.at(userX).at(userY) = tile;
	}

	static const char HERO     = 'H';
	static const char MONSTER  = 'E';//E stands for enemy
	static const char WALL     = '#';
	static const char WATER    = '~';
	static const char OPEN     = '.';
	static const char TREASURE = '$';
	static const char EXIT     = 'N'; //N stands for Navpoint

	static const size_t SIZE = 100; //World is a 100x100 map
	static const size_t DISPLAY = 30; //Show a 30x30 area at a time
	//Randomly generate map
	void init_map() {
		uniform_int_distribution<int> d100(1,100);
		map.clear();
		map.resize(SIZE); //100 rows tall
		for (auto &v : map) v.resize(SIZE,'.'); //100 columns wide
		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				//Line the map with walls
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1) 
					map.at(i).at(j) = WALL;
				else if (i == SIZE/2 and j == SIZE/2) 
					map.at(i).at(j) = HERO;


				else if ((i == 1 || i == 2) && (j == (SIZE/2) - 1 || j == (SIZE/2) || j == (SIZE/2) + 1)) {
					map.at(i).at(j) = EXIT;

				}
				else {
					//5% chance of monster
					if (d100(gen) <= 5) {
						map.at(i).at(j) = MONSTER;
					}
					else if (d100(gen) <= 3) {
						map.at(i).at(j) = TREASURE;
					}
					else if (d100(gen) <= 10) { //10% each spot is wall
						map.at(i).at(j) = WALL;
					}
					else if (d100(gen) <= 40) { //40% chance of wall below other wall
						if (map.at(i-1).at(j) == WALL) {
							map.at(i).at(j) = WALL;
						}
					}
					else if (d100(gen) <= 10) { //10% chance of wall to L/R of other wall
						if (map.at(i).at(j-1) == WALL || map.at(i).at(j+1) == WALL) {
							map.at(i).at(j) = WALL;
						}
					}
					else if (d100(gen) <= 3) { //3% each spot is water
						map.at(i).at(j) = WATER;
					}
					else if (d100(gen) <= 40) { //40% chance of water near other water
						if (map.at(i-1).at(j) == WATER or map.at(i+1).at(j) == WATER or map.at(i).at(j-1) == WATER or map.at(i).at(j+1) == WATER)
							map.at(i).at(j) = WATER;
						/*\
						 for(int i = 0; i<size; i++){
							for(int j = 0; j< size; j++){
								cout <<tunnel_beach.at(i).at(j);
							}
						 }
						 or print function with the wall bounce incorporated with tiles i.e print_map()
						  */
					}
				}
			}
		}
	}


	//Draw the DISPLAY tiles around coordinate (x,y)
	void draw(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		//Bounds check to handle the edges
		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > SIZE-1) {
			start_x = start_x - (end_x - (SIZE-1));
			end_x = SIZE-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > SIZE-1) {
			start_y = start_y - (end_y - (SIZE-1));
			end_y = SIZE-1;
		}

		//Now draw the map using NCURSES
		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t j = start_x; j <= end_x; j++) {
				if (i == y && j == x) {
					attron(A_UNDERLINE | A_BOLD);
					mvaddch(i-start_y,j-start_x,'H');
					attroff(A_UNDERLINE | A_BOLD);
				}
				else {
					int color = 1;
					if (map.at(i).at(j) == WALL)
						color = 5;
					else if (map.at(i).at(j) == WATER)
						color = 2;
					else if (map.at(i).at(j) == HERO)
						color = 3;
					else if (map.at(i).at(j) == TREASURE)
						color = 4;
					else if (map.at(i).at(j) == MONSTER)
						color = 6;

					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x,map.at(i).at(j));
					attroff(COLOR_PAIR(color));
				}
			}
		}
	}
	
	void map_save() {
		ofstream save;
		save.open("map_data.txt");

		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				save << map.at(i).at(j);
			}
			save << endl;
		}
		save.close();

	}

	void map_load() {
		ifstream load;
		load.open("map_data.txt");

		for (size_t i = 0; i < SIZE; i++) {
            for (size_t j = 0; j < SIZE; j++) {
				load >> map.at(i).at(j);
			}
		}
		load.close();

	}



	Map() {
		init_map();
	}
};
