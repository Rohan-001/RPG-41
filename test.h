#pragma once
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

///////////////////////
// ACTORS BASE CLASS //
class Actor { 
	protected:
		int xLoc = 0, yLoc = 0;
		int speed = 10;
	public:
		
		Actor(int new_x = 0, int new_y = 0) : xLoc(new_x), yLoc(new_y) {
			speed = rand() % 100;
		}
		
		virtual void speak () const { 
			cout << "I am an Actor with speed " << speed << endl;
		}
		int get_speed() const {
			return speed;
		}
};

/////////////////////////////////
// HEROES SUBCLASS FROM ACTORS //
class Hero : public Actor {
	protected: 
		int HP = 10;
	public:
		void speak() const override {
			cout << "I am a Hero with speed " << speed << endl;
			cout << "I start with this much HP: " << HP << endl;
		}
};

// ROLES SUBCLASS FROM HEROES //
struct Rogue : public Hero {
	void speak () const override {
		cout << "I am a Rogue with speed " << speed << endl;
		cout << "I start with this much HP: " << HP << endl;
	}
};

///////////////////////////////////
// MONSTER SUBCLASS FROM ACTORS //
class Monster : public Actor {
	protected: 
		int HP = 10;
	public:
		void speak() const override {
			cout << "I am a Hero with speed " << speed << endl;
			cout << "I start with this much HP: " << HP << endl;
		}
};

// MONSTER ROLES SUBCLASS FROM MONSTER //
struct SecGuard : public Monster {
	void speak () const override {
		cout << "I am a Rogue with speed " << speed << endl;
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

