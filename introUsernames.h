#pragma once
#include <iostream>
#include <unistd.h> //for usleep function
#include "actors.h"
#include "toggleNCurses.h"
using namespace std;

//this is a .cc file for now, but later we'll make it a .h file to plug into main
//the purpose of this sequence is to get the party memeber names while also establishing a setting for the story
//if we need to add different classes for characters (ex, wizard or barbarian), we can have a "[USERNAME], please select a loadout" thing as well

//usleep measures in microseconds. 1 million microseconds = 1 second
//we can add more well-timed sleep commands between lines of dialogue later when we decide to go back and polish stuff
//Mencarelli says using std::flush can help with outputting half a life + usleep


//TODO vet the input eventually

void introSequence(Hero &a, Hero &b, Hero &c) {
	/*we're passing by reference (but not const reference)
	  because we want to change the name values of the hero objects.
	  */
	string p1name;
	string p2name;
	string p3name;

	cout << endl << endl << endl;
	sleep(1);
	cout << "///////////METAVERSE SIGN-IN///////////////////////////////////////////////////////////////////////////////////////////////\n" << endl;
	sleep(1);
	cout << "(i) Message of the Day: METAVERSE END-OF-LIFE SALE! EVERYTHING MUST GO! 15% OFF ALL PURCHASES FOR THE NEXT 0 days, 3 hou..." << endl;

	//usleep(1'500'000);

	//player 1 name input

	cout << "\nHello, GUEST and GUEST(1)!" << endl;
	cout << "You have selected the option: join friend" << endl;
	cout << "Please enter the name of the user you are attempting to join:\n" << endl;

	cout << "(Player 1 name): ";
	getline(cin, p1name);	

	//player 2 name input

	cout << "\nGUEST, please sign in to confim you are on " << p1name << "'s friend list.\n" << endl;

	cout << "(Player 2 name): ";
	getline(cin, p2name);	

	cout << "\nSigning in..." << endl;
	//sleep(1);

	cout << "\nSuccess! " << p2name << " is on " << p1name << "'s friend list." << endl;
	cout << "\nGUEST(1), would you like to also sign in before joining?" << endl;

	cout << "\n\t(1) Sign in (enter username)\n\t(2) Do not (remain as guest user)\n" << endl;

	string choiceGuest;
	getline(cin, choiceGuest);
	
	//turn_on_ncurses();
	//int ch = getch(); 
	//turn_off_ncurses();
	
	
	/*	TODO it would be great for UX (user experience)
		if we turned on quickread for prompts like this.
		sadly, those functions are in main.cc

		perhaps we could move those to their own header file?

	   */


	if (choiceGuest == "1") {

		cout << "\nGUEST(1), please sign in now." << endl;

		cout << "\n(Player 3 name): ";
		getline(cin, p3name);

		cout << "\nSigning in..." << endl;
		sleep(1);
		cout << "Success!" << endl;

	} else {
		p3name = "GUEST(1)";

		cout <<  "GUEST(1) will remain a guest user." << endl;
	}

	cout << "\n" << p2name << " and " << p3name << " are now joining " << p1name << "..." << endl;
	cout << "Good luck, and have fun!" << endl;

	a.set_name(p1name);
	b.set_name(p2name);
	c.set_name(p3name);


//if they input 1, then prompt for player 3's name just like before. If they input 2, set p3name to "GUEST(1)" which will remain their name for the rest of the game.

}


void outroSequence() {
	cout << "you win!" << endl;



}
