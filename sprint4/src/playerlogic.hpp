#ifndef PLAYERLOGIC_H_
#define PLAYERLOGIC_H_

#include "game_logic.hpp"

class PlayerLogicBase
{
public:
 int SelectedPiece = 1; // s=1, o=0. Default selections is S so set to 1
 int points =0;
 void ChangeSelectedPiece(int Selection); //change what piece the player has selected on the gameboard
 void addPoint();
 //virtual void CPUPlay(GameLogic* Gamedata) = 0;
 //virtual ~PlayerLogicBase();
};

class PlayerLogic : public PlayerLogicBase
{
public:
  //void CPUPlay(GameLogic* Gamedata);
};
//subclasses to store player specific data

class CPULogic : public PlayerLogic{
public:
    //void CPUPlay(GameLogic* Gamedata);
    int CPUplayer;
 struct CPUtempFilledSpace
  {
   Fl_Toggle_Button* Button;
   int x;
   int y;
   int piece;
   int player;
   bool Scored;
   int originalIndex;
  };
};


//cpu player is child to playerlogic, Class Def is located in game_logic.hpp


#endif
