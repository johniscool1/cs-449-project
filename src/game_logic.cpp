#include "game_logic.hpp"


int GameLogic::ReturnCurrentPlayersTurn()
{
 return CurrentTurn;
}

void GameLogic::RotatePlayerTurn()
{
 switch(CurrentTurn) {
  case 1:
   CurrentTurn = 2;
   break;
  case 2:
   CurrentTurn = 1;
 }
}



void PlayerLogic::ChangeSelectedPiece(int Selection)
{

 SelectedPiece = Selection;
}



void changePlayer1Piece(Fl_Widget*, void* data)
{
 SelectedPieceCBdata* CBdata = static_cast<SelectedPieceCBdata*>(data);
 //Fl_Button* menuSettings = static_cast<Fl_Button*>(PlayerSlectedPiece);
 CBdata->playerdata.ChangeSelectedPiece(CBdata->piece);
}
static void changePlayer2Piece(Fl_Widget*, void* PlayerSlectedPiece)
{
 //Player2Data.ChangeSelectedPiece(PlayerSelectedPiece->value());
 return;
}




