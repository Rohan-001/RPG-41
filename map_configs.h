#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>

using namespace std;

class map_configs {
// start out for now and iterate through and ask what could be changed
// for starters - - - 
//1.) # = boundary, any color is okay besides black
//2.) 8 = tree or rock 
// 3.) = ~ blocked object of some sort such as interactable, like a weapon/treasure

vector <string> toxic_peril = {
"##############################################",
"                                       8      ",
"     8 8 8 8                           8  E   ",
"               8888888888888 8 8 8 8 8        ",
" - - - - - - -                                ",
"-------------_ 8                              ",
"              8############# 8 8 8 8 8        ",
"                                      8       ",
"                                       8      ",
"               000000000000             8     ",
"    00000      |    ☢️     |             8     ",
"    | 0 |      |   ⚠️⚠️⚠️    |            8  88--",
"    | 0 |      | 💀💀💀💀 |           ~   |   ",
"    | 0 |     ~                           |___",
"    00000                                     ",
"##############################################"


}


};



