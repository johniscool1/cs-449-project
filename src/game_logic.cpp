#include "game_logic.hpp"
#include "screen_def.hpp"

int GameLogic::ReturnCurrentPlayersTurn()
{
 return CurrentTurn;
}

//TODO: needs to check more logic like if the palyer scord, they get to go again
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
 printf("%d", Selection);
}



void changePlayerPiece(Fl_Widget*, void* data)
{
 SelectedPieceCBdata* CBdata = static_cast<SelectedPieceCBdata*>(data);
 //Fl_Button* menuSettings = static_cast<Fl_Button*>(PlayerSlectedPiece);
 CBdata->playerdata->SelectedPiece = CBdata->piece;
 printf("Selected Piece: %d. Current piece: %d\n", CBdata->playerdata->SelectedPiece , CBdata->piece);
}

/*
void changePlayer2Piece(Fl_Widget*, void* data)
{
 SelectedPieceCBdata* CBdata = static_cast<SelectedPieceCBdata*>(data);
 //Fl_Button* menuSettings = static_cast<Fl_Button*>(PlayerSlectedPiece);
 CBdata->playerdata->SelectedPiece = CBdata->piece;
}
*/


void GameLogic::addMovetoList(int x, int y, int Piece)
{
 filledSpace SpaceData;
 SpaceData.piece = Piece;
 SpaceData.x = x;
 SpaceData.y = y;
 SpaceData.Scored = False;
 SpacesPlayed.push_back(SpaceData);

}

void GameLogic::SequenceFinder(int rows, int cols)
{
 //look up and down
 vector <tempFilledSpace> TempVect;



 //look through rows
 for(int j = 0; j < cols; j++) {
   //printf("looking at column %d", j);
  //look through the vector to find specific row
  for(int i = 0; i < SpacesPlayed.size(); i++)
  {
   if(SpacesPlayed[i].x == j)
   {
     //create temp var
     tempFilledSpace TempSpaceData;
     TempSpaceData.x = SpacesPlayed[i].x;
     TempSpaceData.y = SpacesPlayed[i].y;
     TempSpaceData.piece = SpacesPlayed[i].piece;
     TempSpaceData.player = SpacesPlayed[i].player;
     TempSpaceData.Scored = SpacesPlayed[i].Scored;
     TempSpaceData.originalIndex = i;
     TempVect.push_back(TempSpaceData);
   }

  //Find Sequences
  for(int k = 0; k < TempVect.size(); k++)
  {


   if(TempVect[k].piece == 1 && !(TempVect[k].Scored)){
     //printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size())
     {
      //printf("Found O at %d,%d", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size())
      {
       //printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
       //printf("Found a Sequence\n");
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = True;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = True;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = True;
       printf("Player %d scorred \n", CurrentTurn);
       //printf("\n-------------------------\n");
      }
     }
    }
   }
  }
  TempVect.clear();
 }
}

