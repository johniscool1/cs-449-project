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



void PlayerLogic::ChangeSelectedPiece(char Selection)
{
 SelectedPiece = Selection;
}



static void changePlayer1Piece(Player1Logic Player1Data, char Selection)
{
 Player1Data.ChangeSelectedPiece(Selection);
}
static void changePlayer2Piece(Player2Logic Player2Data, char Selection)
{
 Player2Data.ChangeSelectedPiece(Selection);
}




