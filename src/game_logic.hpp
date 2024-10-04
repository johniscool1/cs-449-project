#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

//#include <map>
//#include <utility>
#include <vector>

#include <FL/Fl_Widget.H>
#include "FL/Fl_Round_Button.H"
#include "FL/Fl.H"
#include "FL/Fl_Box.H"
#include <FL/Fl_Group.H>
#include <FL/Fl_Toggle_Button.H>

//#include "screen_def.hpp"


using namespace std;
//class to store game states
class GameLogic
{
public:
 int CurrentTurn = 1; //Player 1 goes first
 int turn;
 struct filledSpace { //used in a vector, stores data about the space a player uses
     int x; //location
     int y;
     int piece; //what piece was played
     int player; //what player placed it
     bool Scored; //has the space been scored on
 };

 vector <filledSpace> SpacesPlayed; //stores all the played spaces
 //void InitGameLogic();
 int ReturnCurrentPlayersTurn(); //Depreicated, I dont think its used anywhere
 void RotatePlayerTurn(); //TODO

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
 Fl_Group* Player1Controls;
};
class Player2Logic : public PlayerLogic{
public:
 void DrawPlayer2Selection();
 Fl_Group* Player2Controls;
};

//the following 2 structs are used to pass data to callbacks
struct SelectedPieceCBdata
{
 Fl_Button* SelectedButton;
 int piece;
 Player1Logic* playerdata;

};
struct GameBoardButtonPressedData
{
 Fl_Toggle_Button* Button;
 Player1Logic* Player1Data;
 Player2Logic* Player2Data;
 int currentPlayer;
 GameLogic* GameData;
 int rows;
 int cols;
};


//TODO: Depreicate the following 2 functions and combine into 1 for both classes in PlayerLogic
void changePlayer1Piece(Fl_Widget*, void* data);
static void changePlayer2Piece(Fl_Widget*, Player1Logic Player1Data, char Selection);
#endif
