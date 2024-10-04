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

//window size defintion TODO: implement resizable window
#define GAMEBOARD_WINDOW_X 700
#define GAMEBOARD_WINDOW_Y 700

//Gameboard class for creating the gameboard
class GameBoard
{
 public:
   //store how big the gameboard is
  int rows;
  int cols;

  //window used for gameboard
  Fl_Double_Window* GameBoardWin;


  //GameBoard FullGameboardInit();
  //function to intialize the gameboard
  void initwin();

  //TODO: Needs to be reiplmented into main menu to check to make sure game board isnt to small or big
  bool SetBoardDimensions(int x, int y);

  //draw all the squares for gameplay
  void DrawButtons(Player1Logic* player1data, Player2Logic* player2data, GameLogic* gameData);

  void DrawSettings();

  void show();

  Fl_Toggle_Button *BoardButton;
  static void GameBoardButtonPressed(Fl_Widget*, void *data);


};

//data used to pass to callback
struct CallbackDataMainMenu {
    Fl_Window* window;
    Fl_Counter* x;
    Fl_Counter* y;
    Fl_Round_Button* SimpleGamemodeRB;
    Fl_Round_Button* GeneralGamemodeRB;
};



//main menu functions
void game_main_menu();
//callback for pressing the play button
void playGameButtonCB(Fl_Widget*, void * data);
#endif
