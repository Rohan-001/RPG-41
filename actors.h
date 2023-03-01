#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
using namespace std;

///////////////////////
// ACTORS BASE CLASS //
class Actor { 
	protected:
		int xLoc = 0, yLoc = 0;
		int speed = 10;
		int HP = 10;
		string name = "theatre kid"; //default value as a joke
		//would it make more sense to put HP here instead of in the subclasses?
	public:
		
		Actor(int new_x = 0, int new_y = 0) : xLoc(new_x), yLoc(new_y) {
			speed = rand() % 100;
		}
		
		virtual void speak () const { 
			cout << "I am an Actor with speed " << speed << endl;
		}

		int getHP() const {return HP;}
		void setHP(int newHP) {HP = newHP;}

		int get_speed() const {
			return speed;
		}
		string get_name() const {
			return name;
		}
		void set_name(string newName) {
			name = newName;
		}
};

/////////////////////////////////
// HEROES INHERIT FROM ACTORS //
class Hero : public Actor {
	protected: 
	public:
		void speak() const override {
			cout << "I am a Hero with speed " << speed << endl;
			cout << "I start with this much HP: " << HP << endl;
		}
};

// HERO SUBCLASSES INHERIT FROM HEROES //
class Rogue : public Hero {
	protected:
	public:
	void speak () const override {
		cout << "I am a Rogue with speed " << speed << endl;
		cout << "I start with this much HP: " << HP << endl;
	}
};

///////////////////////////////////
// ENEMIES INHERIT FROM ACTORS //
class Enemy : public Actor {
	protected: 
	public:
		void speak() const override {
			cout << "I am an Enemy with speed " << speed << endl;
			cout << "I start with this much HP: " << HP << endl;
		}
};

// ENEMY TYPES INHERIT FROM ENEMY //
class SecGuard : public Enemy {
	protected:
	public:
	void speak () const override {
		cout << "I am a Security Guard with speed " << speed << endl;
		cout << "I start with this much HP: " << HP << endl;
	}
};

//this functions lets each actor speak and say what they are
void speaker(shared_ptr<Actor> act) {
	act->speak();
}

//this function sorts the actors by speed
bool sortSpeed(const shared_ptr<Actor> &lhs, const shared_ptr<Actor> &rhs) {
	return lhs->get_speed() < rhs->get_speed(); 
}

/* 
	for passing around objects without slicing, there's certain kinds of tricks
	see: /public/inherit.cc for some good practices
	

	vector<shared_ptr<Actor>> vec;
	note that things have to be added to this vector in a particular way

	adding things to the above vector looks like this:
	vec.push_back(make_shared<Actor>(objectName))

	(assuming objectName is of a class that inherits Actor)


*/ 

