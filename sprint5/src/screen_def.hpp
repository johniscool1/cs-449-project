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
#include<FL/fl_ask.H>
#include <FL/Fl_Scroll.H>
#include <iostream>
#include <stdlib.h>
#include <FL/Fl_Choice.H>
#include <unistd.h>

#include "game_logic.hpp"
#include <libcob.h>
//window size defintion TODO: implement resizable window
#define GAMEBOARD_WINDOW_X 700
#define GAMEBOARD_WINDOW_Y 700

extern bool debug;
extern int CPUwaittime;

extern "C" {
  extern int createFile();
}



//Gameboard class for creating the gameboard
class GameBoard
{
 public:
   //store how big the gameboard is
  int rows;
  int cols;
  bool EndOfGame = false;

  //window used for gameboard
  Fl_Double_Window* GameBoardWin;


  //function to intialize the gameboard
  void initwin();

  bool SetBoardDimensions(int x, int y);

  //draw all the buttons for gameplay
  void DrawButtons(PlayerLogic* player1data, PlayerLogic* player2data, GameLogic* gameData);

  //buttons for the gameboard
  Fl_Toggle_Button *BoardButton;

  //CB for when a button on the gameboard is pressed
  //static void GameBoardButtonPressedCB(Fl_Widget*, void *data);

  void show();
  void hide();




};
void GameBoardButtonPressedCB(Fl_Widget*, void *data);
//data used to pass to callback from the main menu
struct MainMenuCBdata {
    Fl_Window* window;
    Fl_Counter* x;
    Fl_Counter* y;
    Fl_Round_Button* SimpleGamemodeRB;
    Fl_Round_Button* GeneralGamemodeRB;
    Fl_Choice* CPUselection;
    Fl_Choice* RECselection;
};







//draws the main menu
void game_main_menu();

//callback for pressing the play button
void playGameButtonCB(Fl_Widget*, void * data);

//calback for selecting game board size
void MMcounter_checkCB(Fl_Widget*, void* data);

//have to color the buttons differently due to CPU player
void ColorButton(Fl_Double_Window* win,int x, int y, Fl_Color ColorB, int piece);


//struct to hold counter button data
struct MMcounter_checkCBdata{
  Fl_Counter* counter;
};

int GetButtonXY(int x);

struct GameBoardButtonCBdata
{
 Fl_Toggle_Button* Button;
 PlayerLogic* Player1Data;
 PlayerLogic* Player2Data;
 int currentPlayer;
 GameLogic* GameData;
 int rows;
 int cols;
 Fl_Group* P1Group;
 Fl_Group* P2Group;
 Fl_Double_Window* GameScreen;
};

void CPUdual(void* v);
struct CPUdualCBdata
{
  Fl_Double_Window* win; PlayerLogic* Player1Data; PlayerLogic* Player2Data; GameLogic* GameData;
};

#endif
