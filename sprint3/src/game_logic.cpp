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

void PlayerLogic::addPoint()
{
 points++;
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

int GameLogic::SequenceFinder(int rows, int cols, PlayerLogic* Player1Data, PlayerLogic* Player2Data)
{
 //look up and down
 vector <tempFilledSpace> TempVect;
 Last_Player_Scored = 0;


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


   if(TempVect[k].piece == 1 && !(TempVect[k].Scored) && TempVect.size() >= 3){
   //  printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() )
     {
     // printf("Found O at %d,%d", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size())
      {
       //printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
      // printf("Found a Sequence\n");
       //check if it has been scored already using a nand gate
       if (!(SpacesPlayed[TempVect[k].originalIndex].Scored && SpacesPlayed[TempVect[k-1].originalIndex].Scored && SpacesPlayed[TempVect[k-2].originalIndex].Scored))
       {
       //printf("Added point to Player %d\n", CurrentTurn);
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;
       printf("HERE: %d", CurrentTurn);
        //subtract 1 from score becuase we run this after the turn has changed
       switch (CurrentTurn - 1)
       {
         case 1:
          Player1Data->addPoint();
          if( Last_Player_Scored == 0)
          {
            Last_Player_Scored = 11;
          } else {
              Last_Player_Scored++;
          }
          break;
         case 0: // since we are subtracting one, player 2 is now 0
          Player2Data->addPoint();
          if( Last_Player_Scored == 0)
          {
            Last_Player_Scored = 21;
          } else {
            Last_Player_Scored++;
          }
          break;
       }
       //printf("\n-------------------------\n");
      }
      }
     }
    }
   }
  }
  TempVect.clear();
 }



 if (SpacesPlayed.size() == rows * cols)
 {
   char message[120];
   //printf("%s",message);
 //if all spaces have been played, end the game
   int winner;
   if (Player1Data->points > Player2Data->points)
   {
     winner = 1;
   } else if (Player1Data->points < Player2Data->points)
   {
     winner = 2;
   } else //check if it was a tie
   {
     winner = 0;
   }
   int menuchoice;
   if (winner != 0) {
     sprintf(message, "GAME OVER.\nPlayer %d WON!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.", winner, Player1Data->points, Player2Data->points);
     menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
   } else
  {
     sprintf(message, "GAME OVER.\nGame was a tie!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.", Player1Data->points, Player2Data->points);
     menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
  }
  return menuchoice;

 }
 return 3;
}

