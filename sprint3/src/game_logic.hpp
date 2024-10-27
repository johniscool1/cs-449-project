#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_
#include <vector>
#include <stdio.h>
#include <algorithm>



#include <FL/Fl_Widget.H>
#include "FL/Fl_Round_Button.H"
#include "FL/Fl.H"
#include "FL/Fl_Box.H"
#include <FL/Fl_Group.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Choice.H>
#include "playerlogic.hpp"
using namespace std;
//class to store player states


//class to store game states
class GameLogic
{
public:
 int CurrentTurn = 1; //Player 1 goes first
 int turn;
 int GameMode = 1; //1 for simple 0 for general game. set to 1 for default selected
 int Last_Player_Scored = 0; // 0= no one scored, XY= player x, scored y times
 bool EndGame = false;
 int rows;
 int cols;

 struct filledSpace { //used in a vector, stores data about the space a player uses
     Fl_Toggle_Button* Button;
     int x; //location
     int y;
     int piece; //what piece was played
     int player; //what player placed it
     bool Scored; //has the space been scored on
 };

 vector <filledSpace> SpacesPlayed; //stores all the played spaces

 void RotatePlayerTurn(); //Decides whos turn it should be TODO: once the sequence finder is finished, re implement this to work with game rules

 void setGameMode(int x); //sets the gamemode

 void addMovetoList(int x, int y, int Piece, Fl_Toggle_Button* Button_Used); //add a space played to the SpacesPlayed vector

 int GetWinner(int p1score, int p2score); // if it returns 0, there was a tie, otherwise returns the winner

 int SequenceFinder(int rows, int cols, PlayerLogic* Player1Data, PlayerLogic* Player2Data); //find if a sequence was created using the size of the board and the SpacesPlayed vector
  /* This structure is only used with SequenceFinder and is identical to filledSpace with the exception of the Orignal index.
   * The original index stores the index of the played space in SpacesPlayed.
   * This struct us used when iterating throught played spaces based on x and y coordinates
   */
  struct tempFilledSpace
  {
   Fl_Toggle_Button* Button;
   int x;
   int y;
   int piece;
   int player;
   bool Scored;
   int originalIndex;
  };
  vector <tempFilledSpace> FoundSequences; // used to pass the buttons to the screen class

  virtual void CheckOutcome() = 0;
  virtual ~GameLogic() {}
};

class GeneralGameMode : public GameLogic
{
public:
  void CheckOutcome();
};
class SimpleGameMode : public GameLogic
{
public:
  void CheckOutcome();
};

//the following 2 structs are used to pass data to callbacks. Due to the callback having to be static, I cannot directly give them varaibles, instead use a struct and static cast it.

//used for RadioButtons to set the players current piece
struct SelectedPieceCBdata
{
 Fl_Button* SelectedButton;
 int piece;
 PlayerLogic* playerdata;

};
//used for when a button on the board is pressed


//callback for the radio buttons to set a players current piece
void changePlayerPieceCB(Fl_Widget*, void* data);

void HideAndResetToMainMenu(void* data);
#endif
