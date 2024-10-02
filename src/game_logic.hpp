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

class GameLogic
{
public:
 int CurrentTurn = 1;
 int turn;
 struct filledSpace {
     int x;
     int y;
     int piece;
     int player;
     bool Scored;
 };
 //map<pair<int, int>, int> SpacesPlayed;
 vector <filledSpace> SpacesPlayed;
 //void InitGameLogic();
 int ReturnCurrentPlayersTurn();
 void RotatePlayerTurn();

 void addMovetoList(int x, int y, int Piece);

 void SequenceFinder(int rows, int cols);

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
class PlayerLogic
{
public:
 int SelectedPiece = 1; // s=1, o=0
 int points;
 void ChangeSelectedPiece(int Selection);



};

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



void changePlayer1Piece(Fl_Widget*, void* data);
static void changePlayer2Piece(Fl_Widget*, Player1Logic Player1Data, char Selection);
#endif
