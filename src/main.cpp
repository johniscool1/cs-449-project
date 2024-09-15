#include "screen_def.hpp"
#include "game_logic.hpp"
#include <iostream>
#include <stdlib.h>

#include "FL/Fl.H"
#include "FL/Fl_Window.H"


int main()
{
/*
 GameBoard sosGameBoard;
 sosGameBoard.init();
 sosGameBoard.SetBoardDimensions(3,3);
 sosGameBoard.DrawButtons();
 sosGameBoard.show();
 return Fl::run();
*/
/*
 Fl_Double_Window* MainMenu = new Fl_Double_Window(700, 700, "SOS GAME");
 Fl_Box* MM_text_box_title = new Fl_Box(100,40, 600, 200, "SOS GAME");
 MM_text_box_title->labelsize(100);
 MainMenu->end();
 MainMenu->show();

*/

 game_main_menu();


 return Fl::run();
}
