#include "screen_def.hpp"
#include "game_logic.hpp"
#include <iostream>
#include <stdlib.h>

#include "FL/Fl.H"
#include "FL/Fl_Window.H"

bool debug = false;
int CPUwaittime = 1;

int main()
{
 game_main_menu();
 return Fl::run();
}
