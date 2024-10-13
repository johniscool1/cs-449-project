#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_
#include <vector>

#include <FL/Fl_Widget.H>
#include "FL/Fl_Round_Button.H"
#include "FL/Fl.H"
#include "FL/Fl_Box.H"
#include <FL/Fl_Group.H>
#include <FL/Fl_Toggle_Button.H>

using namespace std;

//class to store game states
class GameLogic
{
public:
 int CurrentTurn = 1; //Player 1 goes first
 int turn;
 int GameMode = 1; //1 for simple 0 for general game. set to 1 for default selected
 struct filledSpace { //used in a vector, stores data about the space a player uses
     int x; //location
     int y;
     int piece; //what piece was played
     int player; //what player placed it
     bool Scored; //has the space been scored on
 };

 vector <filledSpace> SpacesPlayed; //stores all the played spaces

 void RotatePlayerTurn(); //Decides whos turn it should be TODO: once the sequence finder is finished, re implement this to work with game rules

 void setGameMode(int x); //sets the gamemode

 void addMovetoList(int x, int y, int Piece); //add a space played to the SpacesPlayed vector

 void SequenceFinder(int rows, int cols); //find if a sequence was created using the size of the board and the SpacesPlayed vector
  /* This structure is only used with SequenceFinder and is identical to filledSpace with the exception of the Orignal index.
   * The original index stores the index of the played space in SpacesPlayed.
   * This struct us used when iterating throught played spaces
   */
  struct tempFilledSpace
  {
   int x;
   int y;
   int piece;
   int player;
   bool Scored;
   int originalIndex;
  };

};

//class to store player states
class PlayerLogic
{
public:
 int SelectedPiece = 1; // s=1, o=0. Default selections is S so set to 1
 int points =0;
 void ChangeSelectedPiece(int Selection); //change what piece the player has selected on the gameboard


};

//subclasses to store player specific data
class Player1Logic : public PlayerLogic{
public:
 void DrawPlayer1Selection();
 //Fl_Group* Player1Controls;
};
class Player2Logic : public PlayerLogic{
public:
 void DrawPlayer2Selection();
 //Fl_Group* Player2Controls;
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
struct GameBoardButtonCBdata
{
 Fl_Toggle_Button* Button;
 Player1Logic* Player1Data;
 Player2Logic* Player2Data;
 int currentPlayer;
 GameLogic* GameData;
 int rows;
 int cols;
 Fl_Group* P1Group;
 Fl_Group* P2Group;
};

//callback for the radio buttons to set a players current piece
void changePlayerPieceCB(Fl_Widget*, void* data);
#endif
