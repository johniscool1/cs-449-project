#include "game_logic.hpp"
#include "screen_def.hpp"


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

void GameLogic::setGameMode(int x) // takes the simple gamemode radio button
{
  //1 for simple 0 for general game. set to 1 for default selected
 GameMode = x;
}

void changePlayerPieceCB(Fl_Widget*, void* data)
{
 SelectedPieceCBdata* CBdata = static_cast<SelectedPieceCBdata*>(data);
 //Fl_Button* menuSettings = static_cast<Fl_Button*>(PlayerSlectedPiece);
 CBdata->playerdata->SelectedPiece = CBdata->piece;
 //printf("Selected Piece: %d. Current piece: %d\n", CBdata->playerdata->SelectedPiece , CBdata->piece);
}


void GameLogic::addMovetoList(int x, int y, int Piece)
{
 filledSpace SpaceData;
 SpaceData.piece = Piece;
 SpaceData.x = x;
 SpaceData.y = y;
 SpaceData.Scored = false;
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


   if(TempVect[k].piece == 1 && !(TempVect[k].Scored) && TempVect.size() > 3){
     //printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() )
     {
      //printf("Found O at %d,%d", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size())
      {
       //printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
       //printf("Found a Sequence\n");
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;
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

