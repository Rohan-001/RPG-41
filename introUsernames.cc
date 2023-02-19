#include <iostream>
using namespace std;

//this is a .cc file for now, but later we'll make it a .h file to plug into main
//the purpose of this sequence is to get the party memeber names while also establishing a setting for the story
//if we need to add different classes for characters (ex, wizard or barbarian), we can have a "[USERNAME], please select a loadout" thing as well

int main() {

	string p1name;
	string p2name;
	string p3name;

	cout << endl << endl << endl;
	cout << "/////////METAVERSE SIGN-IN////////////////\n" << endl;
	cout << "\tHello, GUEST! You have selected the option: join friend" << endl;
	cout << "\tPlease enter the name of the user you are attempting to join:\n" << endl;

	cout << "(Player 1 name):\t";

	cin >> p1name;

	cout << "\nError: GUEST, please sign in to confim you are on " << p1name << "'s friend list.\n" << endl;
	cout << "(Player 2 name):\t";
	cin >> p2name;

	cout << "Checking";
	for (int i = 0; i < 3; i++) {
		//insert a sleep function right here for like 300ms
		cout << ".";

	}
	cout << endl << "Success! " << p2name << " is on " << p1name << "'s friend list!" << endl;
	cout << "GUEST(1), would you like to also sign in before joining?" << endl;

	cout << "\n\t(1) Sign in (enter username)\n\t(2) Do not (remain as guest user)\n" << endl;

	//TODO cin user choice. This is one of the "get putton input" things, so we might want to turn on quick read for a little
	//if they input 1, then prompt for player 3's name just like before. If they input 2, set p3name to "GUEST(1)" which will remain their name for the rest of the game.


}
