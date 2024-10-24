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


  //function to intialize the gameboard
  void initwin();

  bool SetBoardDimensions(int x, int y);

  //draw all the buttons for gameplay
  void DrawButtons(Player1Logic* player1data, Player2Logic* player2data, GameLogic* gameData);

  //buttons for the gameboard
  Fl_Toggle_Button *BoardButton;

  //CB for when a button on the gameboard is pressed
  static void GameBoardButtonPressedCB(Fl_Widget*, void *data);

  void show();
  void close();




};

//data used to pass to callback from the main menu
struct MainMenuCBdata {
    Fl_Window* window;
    Fl_Counter* x;
    Fl_Counter* y;
    Fl_Round_Button* SimpleGamemodeRB;
    Fl_Round_Button* GeneralGamemodeRB;
};

class Draw_lineP1 : public Fl_Widget {
public:
    Draw_lineP1(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
    }
    void draw() {
        fl_color(FL_BLUE);
        int x1 = x(),       y1 = y();
        int x2 = w()-1, y2 = h();


        fl_line(x1, y1, x2, y2);

    }
};

class MyBox : public Fl_Widget {
public:
    MyBox(int X, int Y, int W, int H, Fl_Color color) : Fl_Widget(X, Y, W, H), vcolor(color) {}

    void draw() override {
        // Draw a simple box with the specified color
        fl_draw_box(FL_FLAT_BOX, x(), y(), w(), h(), vcolor);
    }

private:
    Fl_Color vcolor; // Variable color
};


//draws the main menu
void game_main_menu();

//callback for pressing the play button
void playGameButtonCB(Fl_Widget*, void * data);

//calback for selecting game board size
void MMcounter_checkCB(Fl_Widget*, void* data);

//struct to hold counter button data
struct MMcounter_checkCBdata{
  Fl_Counter* counter;
};

int GetButtonXY(int x);


#endif
