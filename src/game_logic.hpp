#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include <map>
#include <utility>

#include <FL/Fl_Widget.H>
#include "FL/Fl_Round_Button.H"
#include "FL/Fl.H"
#include "FL/Fl_Box.H"
#include <FL/Fl_Group.H>

using namespace std;

class GameLogic
{
public:
 int CurrentTurn = 1;
 int turn;
 map<pair<int, int>, char> SpacesPlayed;

 //void InitGameLogic();
 int ReturnCurrentPlayersTurn();
 void RotatePlayerTurn();


};

class PlayerLogic
{
public:
 char SelectedPiece;
 int points;

 void ChangeSelectedPiece(char Selection);

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



static void changePlayer1Piece(Player1Logic Player1Data, char Selection);
static void changePlayer2Piece(Fl_Widget*, Player1Logic Player1Data, char Selection);
#endif
