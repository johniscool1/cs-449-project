#ifndef SCREEN_DEF_H_
#define SCREEN_DEF_H_

#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Round_Button.H"
#include "FL/Fl_Check_Button.H"
#include "FL/Fl_Toggle_Button.H"
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Counter.H>

#include <iostream>
#include <stdlib.h>



#include "game_logic.hpp"


#define GAMEBOARD_WINDOW_X 700
#define GAMEBOARD_WINDOW_Y 700


//Gameboard class for creating the gameboard
class GameBoard
{
 public:
  int rows;
  int cols;

  Fl_Double_Window* GameBoardWin;

  GameBoard FullGameboardInit();

  void initwin();
  bool SetBoardDimensions(int x, int y);
  void DrawButtons();
  void DrawSettings();
  void show();

  Fl_Toggle_Button *BoardButton;
  static void GameBoardButtonPressed(Fl_Widget*, void *ButtonThatPressed);


};


struct CallbackDataMainMenu {
    Fl_Window* window;
    Fl_Counter* x;
    Fl_Counter* y;
};



//main menu
void game_main_menu();
void playGameButtonCB(Fl_Widget*, void * data);
#endif
