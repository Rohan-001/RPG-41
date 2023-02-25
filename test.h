#pragma once
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

//FIXME this code is not compiling!

///////////////////////
// ACTORS BASE CLASS //
class ACTORS { 
	protected:
		int xLoc = 0, yLoc = 0;
		int speed = 10;
	public: 
		Actors(int new_x = 0, int new_y = 0) : xLoc(new_x), yLoc(new_y) {
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
class HEROES : public ACTORS {
	protected: 
		int HP = 10;
	public:
		void speak() const override {
			cout << "I am a Hero with speed " << speed << endl;
			cout << "I start with this much HP: " << HP << endl;
		}
};

// ROLES SUBCLASS FROM HEROES //
struct Rogue : public HEROES {
	void speak () const override {
		cout << "I am a Rogue with speed " << speed << endl;
		cout << "I start with this much HP: " << HP << endl;
	}
};

///////////////////////////////////
// MONSTER SUBCLASS FROM ACTORS //
class MONSTER : public ACTORS {
	protected: 
		int HP = 10;
	public:
		void speak() const override {
			cout << "I am a Hero with speed " << speed << endl;
			cout << "I start with this much HP: " << HP << endl;
		}
};

// MONSTER ROLES SUBCLASS FROM MONSTER //
struct SecGuard :public MONSTER {
	void speak () const override {
		cout << "I am a Rogue with speed " << speed << endl;
		cout << "I start with this much HP: " << HP << endl;
	}
};

//this functions lets each actor speak and say what they are
void speaker(shared_ptr<ACTORS> act) {
	act->speak();
}

//this function sorts the actors by speed
bool sortSpeed(const shared_ptr<ACTORS> &lhs, const shared_ptr<ACTORS> &rhs) {
	return lhs->speed < rhs->speed;
}

/* 
  in main we need to have these lines of codes to create the shared ptr vector
  something like 

  vector<shared_ptr<ACTORS>> vec;

  ACTOR a;
  a.speed 

*/ 

