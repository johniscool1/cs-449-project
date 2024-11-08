#include "game_logic.hpp"
#include "screen_def.hpp"

using namespace std;

//DEBUG





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

void PlayerLogicBase::addPoint()
{
 points++;
}


void PlayerLogicBase::ChangeSelectedPiece(int Selection)
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


void GameLogic::addMovetoList(int x, int y, int Piece, Fl_Toggle_Button* Button_Used)
{
 filledSpace SpaceData;
 SpaceData.piece = Piece;
 SpaceData.x = x;
 SpaceData.y = y;
 SpaceData.Scored = false;
 SpaceData.Button = Button_Used;
 SpaceData.player = CurrentTurn;
 SpacesPlayed.push_back(SpaceData);
}





int GameLogic::SequenceFinder(int rows, int cols, PlayerLogic* Player1Data, PlayerLogic* Player2Data)
{
 //look N to S

 Last_Player_Scored = 0;


 //look through Columns
 for(int j = 0; j < cols; j++) {
   //printf("looking at column %d", j);
  //look through the vector to find specific row
   vector <tempFilledSpace> TempVect;
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
     TempSpaceData.Button = SpacesPlayed[i].Button;
     TempVect.push_back(TempSpaceData);
   }
  }
  //sort the vector from low to high to ensure we have the spaces ordered right
  sort(TempVect.begin(), TempVect.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.y < b.y;
  });
  //Find Sequences
  //cout << "Size " << TempVect.size() << endl;
  for(int f = 0; f < TempVect.size(); f++)
  {

    int k = f;
   if(TempVect[k].piece == 1 && TempVect.size() >= 3){
     //printf("Found S at %d,%d\n", TempVect[k].x + 1, TempVect[k].y + 1);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() && TempVect[k].y == TempVect[k-1].y + 1)
     {
      //printf("Found O at %d,%d", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size()&& TempVect[k].y == TempVect[k-1].y + 1)
      {
      //printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
        //printf("Found a Sequence n to s\n");
       //check if it has been scored already using a nand gate
      //cout << "1 " << SpacesPlayed[TempVect[k].originalIndex].Scored << " 2 " << SpacesPlayed[TempVect[k-1].originalIndex].Scored << " 3 " << SpacesPlayed[TempVect[k-2].originalIndex].Scored << endl;
       if (!(SpacesPlayed[TempVect[k].originalIndex].Scored && SpacesPlayed[TempVect[k-1].originalIndex].Scored && SpacesPlayed[TempVect[k-2].originalIndex].Scored))
       {
       //printf("Added point to Player %d\n", CurrentTurn);
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;

       //add the sequences to this vector to later indiacte who scored
       FoundSequences.push_back(TempVect[k]);
       FoundSequences.push_back(TempVect[k-1]);
       FoundSequences.push_back(TempVect[k-2]);

       //subtract 1 from score becuase we run this after the turn has changeds
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
  TempVect.clear();
  }





  //look east to west
  //vector <tempFilledSpace> TempVect;
 //Last_Player_Scored = 0;
for(int j = 0; j < rows; j++) {
  vector <tempFilledSpace> TempVect;
   //printf("looking at row %d\n", j);
  //look through the vector to find specific row
  for(int i = 0; i < SpacesPlayed.size(); i++)
  {
   if(SpacesPlayed[i].y == j)
   {
     //create temp var
     tempFilledSpace TempSpaceData;
     TempSpaceData.x = SpacesPlayed[i].x;
     TempSpaceData.y = SpacesPlayed[i].y;
     TempSpaceData.piece = SpacesPlayed[i].piece;
     TempSpaceData.player = SpacesPlayed[i].player;
     TempSpaceData.Scored = SpacesPlayed[i].Scored;
     TempSpaceData.Button = SpacesPlayed[i].Button;
     TempSpaceData.originalIndex = i;
     TempVect.push_back(TempSpaceData);
   }
  }
  //sort the vector from low to high to ensure we have the spaces ordered right
  sort(TempVect.begin(), TempVect.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.x < b.x;
  });
  //cout << "Size " << TempVect.size() << endl;
  for(int d = 0; d < TempVect.size(); d++)
  {
    int k = d;

   if(TempVect[k].piece == 1 && TempVect.size() >= 3){
     //printf("Found S at %d,%d\n", TempVect[k].x +1, TempVect[k].y+1);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() && TempVect[k].x == TempVect[k-1].x + 1)
     {
      //printf("Found O at %d,%d", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size() && TempVect[k].x == TempVect[k-1].x + 1)
      {
       //printf("Found S at %d,%d", TempVect[k].x, TempVect[k].y);
       //printf("Found a Sequence e to w\n");
       //check if it has been scored already using a nand gate
       if (!(SpacesPlayed[TempVect[k].originalIndex].Scored && SpacesPlayed[TempVect[k-1].originalIndex].Scored && SpacesPlayed[TempVect[k-2].originalIndex].Scored))
       {
       //printf("Added point to Player %d\n", CurrentTurn);
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;
       //add the sequences to this vector to later indiacte who scored
       FoundSequences.push_back(TempVect[k]);
       FoundSequences.push_back(TempVect[k-1]);
       FoundSequences.push_back(TempVect[k-2]);
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
    TempVect.clear();
  }


/*
 *******************************************************************
 * CHECK PARRELLELS
 ********************************************************************

 */





//check SW to NE


  for(int i = 0; i < cols; i++)
  {
    vector <tempFilledSpace> TempVect;
    int counter = i;
    for (int j = 0; j < rows; j++){
      //cout << "X: " << j << "Y: " << counter << endl;
      for(int l = 0; l < SpacesPlayed.size(); l++)
     {
   if(SpacesPlayed[l].y == counter && SpacesPlayed[l].x == j)
   {
     //create temp var
     //cout << "ADDED " << SpacesPlayed[k].x << SpacesPlayed[k].y <<  endl;
     tempFilledSpace TempSpaceData;
     TempSpaceData.x = SpacesPlayed[l].x;
     TempSpaceData.y = SpacesPlayed[l].y;
     TempSpaceData.piece = SpacesPlayed[l].piece;
     TempSpaceData.player = SpacesPlayed[l].player;
     TempSpaceData.Scored = SpacesPlayed[l].Scored;
     TempSpaceData.Button = SpacesPlayed[l].Button;
     TempSpaceData.originalIndex = l;
     TempVect.push_back(TempSpaceData);
   }

    }
    counter = counter -1;
  }
  sort(TempVect.begin(), TempVect.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.x < b.x;
  });

  for(int d = 0; d < TempVect.size(); d++)
  {
   int k = d;
   if(TempVect[k].piece == 1 && TempVect.size() >= 3){
     //printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() && TempVect[k].x -1 == TempVect[k-1].x)
     {
      //printf("Found O at %d,%d\n", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size() && TempVect[k].x -1 == TempVect[k-1].x)
      {
      // printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
      // printf("Found a Sequence\n");
       //check if it has been scored already using a nand gate
       if (!(SpacesPlayed[TempVect[k].originalIndex].Scored && SpacesPlayed[TempVect[k-1].originalIndex].Scored && SpacesPlayed[TempVect[k-2].originalIndex].Scored))
       {
       //printf("Added point to Player %d\n", CurrentTurn);
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;
       //add the sequences to this vector to later indiacte who scored
       FoundSequences.push_back(TempVect[k]);
       FoundSequences.push_back(TempVect[k-1]);
       FoundSequences.push_back(TempVect[k-2]);
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
  TempVect.clear();
  }


  //check After the middle



  for(int i = 1; i < cols; i++)
  {
    vector <tempFilledSpace> TempVect;
    int counter = i;
    for(int j = rows; j > 0; j--)
    {
      //cout << "X: " << counter << "Y: " << j << endl;
      for(int l = 0; l < SpacesPlayed.size(); l++)
     {
        if(SpacesPlayed[l].y == counter && SpacesPlayed[l].x == j)
        {
          //create temp var
          //cout << "ADDED " << SpacesPlayed[k].x << SpacesPlayed[k].y <<  endl;
          tempFilledSpace TempSpaceData;
          TempSpaceData.x = SpacesPlayed[l].x;
          TempSpaceData.y = SpacesPlayed[l].y;
          TempSpaceData.piece = SpacesPlayed[l].piece;
          TempSpaceData.player = SpacesPlayed[l].player;
          TempSpaceData.Scored = SpacesPlayed[l].Scored;
          TempSpaceData.Button = SpacesPlayed[l].Button;
          TempSpaceData.originalIndex = l;
          TempVect.push_back(TempSpaceData);
        }

    }
      counter++;
    }
    sort(TempVect.begin(), TempVect.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.x < b.x;
  });
  for(int d = 0; d < TempVect.size(); d++)
  {
   int k = d;
   if(TempVect[k].piece == 1 && TempVect.size() >= 3){
     //printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() && TempVect[k].x -1 == TempVect[k-1].x)
     {
      //printf("Found O at %d,%d\n", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size() && TempVect[k].x -1 == TempVect[k-1].x)
      {
     // printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
      //printf("Found a Sequence\n");
       //check if it has been scored already using a nand gate
       if (!(SpacesPlayed[TempVect[k].originalIndex].Scored && SpacesPlayed[TempVect[k-1].originalIndex].Scored && SpacesPlayed[TempVect[k-2].originalIndex].Scored))
       {
       //printf("Added point to Player %d\n", CurrentTurn);
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;
       //add the sequences to this vector to later indiacte who scored
       FoundSequences.push_back(TempVect[k]);
       FoundSequences.push_back(TempVect[k-1]);
       FoundSequences.push_back(TempVect[k-2]);
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
  TempVect.clear();
  }




 //check SE to NW

  for(int i = 0; i < cols; i++)
  {
    vector <tempFilledSpace> TempVect;
    int counter = i;
    for (int j = 0; j < rows; j++){
      //cout << "X: " << counter << "Y: " << j << endl;
      for(int l = 0; l < SpacesPlayed.size(); l++)
     {
   if(SpacesPlayed[l].y == j && SpacesPlayed[l].x == counter)
   {
     //create temp var
     //cout << "ADDED " << SpacesPlayed[k].x << SpacesPlayed[k].y <<  endl;
     tempFilledSpace TempSpaceData;
     TempSpaceData.x = SpacesPlayed[l].x;
     TempSpaceData.y = SpacesPlayed[l].y;
     TempSpaceData.piece = SpacesPlayed[l].piece;
     TempSpaceData.player = SpacesPlayed[l].player;
     TempSpaceData.Scored = SpacesPlayed[l].Scored;
     TempSpaceData.Button = SpacesPlayed[l].Button;
     TempSpaceData.originalIndex = l;
     TempVect.push_back(TempSpaceData);
   }

    }
    counter = counter +1;
  }
  sort(TempVect.begin(), TempVect.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.x < b.x;
  });
  for(int d = 0; d < TempVect.size(); d++)
  {
    int k = d;
   if(TempVect[k].piece == 1 && TempVect.size() >= 3){
     //printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() && TempVect[k].y -1 == TempVect[k-1].y)
     {
      //printf("Found O at %d,%d\n", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size() && TempVect[k].y -1 == TempVect[k-1].y)
      {
      // printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
       //printf("Found a Sequence\n");
       //check if it has been scored already using a nand gate
       if (!(SpacesPlayed[TempVect[k].originalIndex].Scored && SpacesPlayed[TempVect[k-1].originalIndex].Scored && SpacesPlayed[TempVect[k-2].originalIndex].Scored))
       {
       //printf("Added point to Player %d\n", CurrentTurn);
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;
       //add the sequences to this vector to later indiacte who scored
       FoundSequences.push_back(TempVect[k]);
       FoundSequences.push_back(TempVect[k-1]);
       FoundSequences.push_back(TempVect[k-2]);
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
  TempVect.clear();

 }


 //check after the middle


 for(int i = cols; i > 0; i--)
  {
    vector <tempFilledSpace> TempVect;
    int counter = i;
    for (int j = rows; j > 0; j--){
      //cout << "X: " << counter << "Y: " << j << endl;
      for(int l = 0; l < SpacesPlayed.size(); l++)
     {
   if(SpacesPlayed[l].y == j && SpacesPlayed[l].x == counter)
   {
     //create temp var
     //cout << "ADDED " << SpacesPlayed[k].x << SpacesPlayed[k].y <<  endl;
     tempFilledSpace TempSpaceData;
     TempSpaceData.x = SpacesPlayed[l].x;
     TempSpaceData.y = SpacesPlayed[l].y;
     TempSpaceData.piece = SpacesPlayed[l].piece;
     TempSpaceData.player = SpacesPlayed[l].player;
     TempSpaceData.Scored = SpacesPlayed[l].Scored;
     TempSpaceData.Button = SpacesPlayed[l].Button;
     TempSpaceData.originalIndex = l;
     TempVect.push_back(TempSpaceData);
   }

    }
    counter = counter - 1;
  }
  sort(TempVect.begin(), TempVect.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.x < b.x;
  });
  for(int d = 0; d < TempVect.size(); d++)
  {
    int k = d;
   if(TempVect[k].piece == 1 && TempVect.size() >= 3){
     //printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
     k++;
     if(TempVect[k].piece == 0 && k < TempVect.size() && TempVect[k].y -1 == TempVect[k-1].y)
     {
      //printf("Found O at %d,%d\n", TempVect[k].x, TempVect[k].y);
      k++;
      if(TempVect[k].piece == 1 && k < TempVect.size() && TempVect[k].y -1 == TempVect[k-1].y)
      {
      // printf("Found S at %d,%d\n", TempVect[k].x, TempVect[k].y);
       //printf("Found a Sequence\n");
       //check if it has been scored already using a nand gate
       if (!(SpacesPlayed[TempVect[k].originalIndex].Scored && SpacesPlayed[TempVect[k-1].originalIndex].Scored && SpacesPlayed[TempVect[k-2].originalIndex].Scored))
       {
       //printf("Added point to Player %d\n", CurrentTurn);
       //Mark the spaces as being scored already
       SpacesPlayed[TempVect[k].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-1].originalIndex].Scored = true;
       SpacesPlayed[TempVect[k-2].originalIndex].Scored = true;
       //add the sequences to this vector to later indiacte who scored
       FoundSequences.push_back(TempVect[k]);
       FoundSequences.push_back(TempVect[k-1]);
       FoundSequences.push_back(TempVect[k-2]);
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
  TempVect.clear();

 }


 return 0;
}




void GeneralGameMode::CheckOutcome()
{
  if(SpacesPlayed.size() == rows * cols)
  {
    EndGame = true;
  }
}

void SimpleGameMode::CheckOutcome()
{
  if(FoundSequences.size() != 0 || SpacesPlayed.size() == rows * cols)
  {
    EndGame = true;
  }
}

void HideAndResetToMainMenu(void* data)
{
  Fl_Double_Window* win = static_cast<Fl_Double_Window*>(data);
  win->hide();
}


/*
 *
 * START OF CPU LOGIC
 *
 */




void GameLogic::CPUseek(Fl_Double_Window* win)
{
  /*
   *
   * Look For last letter in sequence
   *
   */

 printf("Seeking\n");
 //create temp copy of FoundSequences to return it to later
 const vector <filledSpace> TempSpacesPlayed = SpacesPlayed;
 //keep track of who the current player was
 int TempCurrentTurn = CurrentTurn;
 FoundSequences.clear();

 SpacesPlayed.clear();
 filledSpace CPUmove;
 CPUmove.x = -1;
 CPUmove.y = -1;


 //fill temp board with s to look for ez sequences
 printf("Seeking EZ s\n");
 CurrentTurn = 1;
 for(int i=0; i < cols; i++)
 {
   for(int j=0; j < rows; j++)
   {

       addMovetoList(i, j, 1, NULL);
       }

    }

 for(int k=0; k < TempSpacesPlayed.size(); k++)
      {
        for(int j = 0; j < SpacesPlayed.size(); j++){
        if(SpacesPlayed[j].x == TempSpacesPlayed[k].x && SpacesPlayed[j].y == TempSpacesPlayed[k].y)
        {
          SpacesPlayed[j].piece = TempSpacesPlayed[k].piece;
          SpacesPlayed[j].Scored = TempSpacesPlayed[k].Scored;
          SpacesPlayed[j].player = 2;
        }
        }
      }

 PlayerLogic* Player1tempdata = new PlayerLogic;
 PlayerLogic* Player2tempdata = new PlayerLogic;

 SequenceFinder(rows, cols, Player1tempdata, Player2tempdata);



/*
 if(FoundSequences.size() > 0)
 {
     sort(FoundSequences.begin(), FoundSequences.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.x < b.x;
  });
     for(int i=0; i < FoundSequences.size();i++){
       if(!FoundSequences[i].Scored  && FoundSequences[i].player == 1)
       {
        counter++;
        CPUmove.x = FoundSequences[i].x;
        CPUmove.y = FoundSequences[i].y;
        CPUmove.piece = 1;
        printf("X: %d Y: %d \n", CPUmove.x, CPUmove.y);
      }
    }
 }
*/


 if(FoundSequences.size() == 0) {

 //keep track of who the current player was

 //std::copy(SpacesPlayed.begin(), SpacesPlayed.end(), TempSpacesPlayed.begin());
 //TempSpacesPlayed = SpacesPlayed;
 // Fl_Toggle_Button* Button;
 //   int x;
 //   int y;
 //   int piece;
 //   int player;
 //   bool Scored;
 //   int originalIndex;



 SpacesPlayed.clear();


 printf("Seeking EZ o\n");
 //fill temp board with o to look for ez sequences
 CurrentTurn = 1;
 SpacesPlayed.clear();
 for(int i=0; i < cols; i++)
 {
   for(int j=0; j < rows; j++)
   {

       addMovetoList(i, j, 0, NULL);
       }

    }

 for(int k=0; k < TempSpacesPlayed.size(); k++)
      {
        for(int j = 0; j < SpacesPlayed.size(); j++){
        if(SpacesPlayed[j].x == TempSpacesPlayed[k].x && SpacesPlayed[j].y == TempSpacesPlayed[k].y)
        {
          SpacesPlayed[j].piece = TempSpacesPlayed[k].piece;
          SpacesPlayed[j].Scored = TempSpacesPlayed[k].Scored;
          SpacesPlayed[j].player = 2;
        }
        }
      }

 PlayerLogic* Player1tempdata = new PlayerLogic;
 PlayerLogic* Player2tempdata = new PlayerLogic;

 SequenceFinder(rows, cols, Player1tempdata, Player2tempdata);



/*
 if(FoundSequences.size() > 0)
 {
     sort(FoundSequences.begin(), FoundSequences.end(), [](const tempFilledSpace& a, const tempFilledSpace& b)
  {
    return a.x < b.x;
  });
     for(int i=0; i < FoundSequences.size();i++){
       if(!FoundSequences[i].Scored  && FoundSequences[i].player == 1)
       {
        counter++;
        CPUmove.x = FoundSequences[i].x;
        CPUmove.y = FoundSequences[i].y;
        CPUmove.piece = 0;
      }
    }
 }
 */
 //if the counter is mroe than one, we can play

  //return values to what they were before calling the function

 SpacesPlayed.clear();
 CurrentTurn = TempCurrentTurn;
 SpacesPlayed = TempSpacesPlayed;

 }




 //check found sequences for the one we'll score with
  if(FoundSequences.size() != 0)
  {
    //printf("Seeking score");
    vector<tempFilledSpace> TempSeqFound;
    TempSeqFound = FoundSequences;
    //remove spaces that have already been played

    for(int i =0; i < TempSeqFound.size(); i ++)
    {
      for(int j =0; j< TempSpacesPlayed.size(); j++)
      {
        if(TempSeqFound[i].x == TempSpacesPlayed[j].x && TempSeqFound[i].y == TempSpacesPlayed[j].y)
        {
          TempSeqFound.erase(TempSeqFound.begin() + i);
        }
      }
    }
    for(int i =0; i < TempSeqFound.size(); i++)
    {
      FoundSequences.clear();
      SpacesPlayed.clear();
      SpacesPlayed = TempSpacesPlayed;
      addMovetoList(TempSeqFound[i].x, TempSeqFound[i].y, TempSeqFound[i].piece, NULL);
      //printf("SEEKER %d: %d, %d\n", i, TempSeqFound[i].x, TempSeqFound[i].y);

      if(CheckIfScore(rows, cols))
      {
        CPUmove.x = TempSeqFound[i].x;
        CPUmove.y = TempSeqFound[i].y;
        CPUmove.piece = TempSeqFound[i].piece;
        //printf("Choose: %d, Y: %d\n", CPUmove.x, CPUmove.y);
        }
      }

    FoundSequences = TempSeqFound;

  }

  if((CPUmove.x > rows || CPUmove.x < 0 || CPUmove.y > cols || CPUmove.x < 0) && CPUmove.x != -1)
  {
    printf("----------------------\n");
    printf("MAJOR ERROR, OUT OF BOUNDS\n");
    printf("%d, Y: %d\n", CPUmove.x, CPUmove.y);
    printAllSequences();
    printf("----------------------\n");
    FoundSequences.clear();
  }
  if(FoundSequences.size() == 0 || CPUmove.x > rows || CPUmove.x < 0 || (CPUmove.x == -1 && CPUmove.y == -1))
 {
   printf("Giving up, rand placement\n");
   SpacesPlayed.clear();
  SpacesPlayed = TempSpacesPlayed;
   bool exitLoop = false;
   RandomGenerator RandNum;
   if(TempSpacesPlayed.size() != 0) {
    while(!exitLoop)
    {

    int randx = RandNum.getRandomNumber(0,cols-1);
    int randy = RandNum.getRandomNumber(0,rows-1);
    int randp = RandNum.getRandomNumber(0,1);
     for(int i =0; i < SpacesPlayed.size(); i++)
     {
       //cout << i << endl;

       if(SpacesPlayed[i].x != randx && SpacesPlayed[i].y != randy)
       {
        //printf("Rand look here X: %d, Y: %d\n", CPUmove.x, CPUmove.y);
         CPUmove.x = randx;
         CPUmove.y = randy;
         CPUmove.piece = randp;
         exitLoop = true;
         break;
       }
     }


    }
   } else {
    int randx = RandNum.getRandomNumber(0,cols-1);
    int randy = RandNum.getRandomNumber(0,rows-1);
    int randp = RandNum.getRandomNumber(0,1);

         CPUmove.x = randx;
         CPUmove.y = randy;
         CPUmove.piece = randp;

       }
 }
 //printf("Rand look here X: %d, Y: %d\n", CPUmove.x, CPUmove.y);






 //



 FoundSequences.clear();
 SpacesPlayed.clear();
 CurrentTurn = TempCurrentTurn;
 SpacesPlayed = TempSpacesPlayed;
 //printAllSequences();
 for(int i=0; i < SpacesPlayed.size(); i++)
 {
   if(SpacesPlayed[i].x == CPUmove.x && SpacesPlayed[i].y == CPUmove.y)
   {
     bool exitLoop = false;
     RandomGenerator RandNum;
    while(!exitLoop)
    {

    int randx = RandNum.getRandomNumber(0,cols-1);
    int randy = RandNum.getRandomNumber(0,rows-1);
    int randp = RandNum.getRandomNumber(0,1);
     for(int i =0; i < SpacesPlayed.size(); i++)
     {
       //cout << i << endl;

       if(SpacesPlayed[i].x != randx && SpacesPlayed[i].y != randy)
       {
        //printf("Rand look here X: %d, Y: %d\n", CPUmove.x, CPUmove.y);
         CPUmove.x = randx;
         CPUmove.y = randy;
         CPUmove.piece = randp;
         exitLoop = true;
         break;
       }
     }

   }
  }
 }
 //look for the button
  Fl_Toggle_Button* button = FindButton(win, CPUmove.x, CPUmove.y);
  button->down_color(FL_GREEN);
  switch(CPUmove.piece) {
    case 0:
    button->label("O");
    break;
    case 1:
    button->label("S");
    break;
  }
  //keep button down
  button->deactivate();
 //CPU makes move
 addMovetoList(CPUmove.x, CPUmove.y, CPUmove.piece, button);
 printf("Play here X: %d, Y: %d\n", CPUmove.x, CPUmove.y);
 printf("---------DONE----------\n");
 FILE *seqFile = fopen("debug.txt", "a");
 fprintf(seqFile, "%d, %d\n", CPUmove.x, CPUmove.y);
 fclose(seqFile);

 CPUlastXplayed = CPUmove.x;
 CPUlastYplayed = CPUmove.y;
 delete Player1tempdata;
 delete Player2tempdata;
 Player1tempdata = nullptr;
 Player2tempdata = nullptr;

}

Fl_Toggle_Button* GameLogic::FindButton(Fl_Double_Window* win, int x, int y)
{
  x = x * 42 + 100;
  y = y * 42 + 100;

  //look at all the widgets in the window, looking for the one that matches the x and y corrdinates fot he game board
  for(int i = 0; i < win->children(); i ++)
  {
    Fl_Widget *widget = win->child(i);
    if(Fl_Toggle_Button *button = dynamic_cast<Fl_Toggle_Button *> (widget))
    {
      if(button->x() == x && button->y() == y)
      {
        return button;
      }
    }

  }
  return NULL;
}


bool GameLogic::CheckIfScore(int rows, int cols)
{
   PlayerLogic* Player1tempdata = new PlayerLogic;
   PlayerLogic* Player2tempdata = new PlayerLogic;
   SequenceFinder(rows, cols, Player1tempdata, Player2tempdata);
   if(Player2tempdata->points > Player1tempdata->points)
   {
     return true;
   } else {
     return false;
  }



}
void GameLogic::printAllSequences() {
    printf("\n=== All Found Sequences (%zu total) ===\n", SpacesPlayed.size());
    for (int i = 0; i < SpacesPlayed.size(); i++) {
        printf("Sequence[%d: x=%d, y=%d, piece=%d\n", i, SpacesPlayed[i].x, SpacesPlayed[i].y, SpacesPlayed[i].piece);
    }
    printf("=====================================\n");
}



Fl_Color purple_Button = fl_rgb_color(128, 0, 128);

void GameLogic::HandleButtonPlayed(PlayerLogic* Player1Data, PlayerLogic* Player2Data, Fl_Double_Window* win)
{
 //rotate CurrentTurn
 RotatePlayerTurn();
 //deactivate and activate the radio buttons for players

  //See if sequence was created
 SequenceFinder(rows, cols, Player1Data, Player2Data);



 CheckOutcome();
 //Change the color of the buttons to indiacte they have been scored we also.
 //we also roate out the turn os that the player goes again
 if(Last_Player_Scored > 10 && Last_Player_Scored < 20) //player 1 scored
 {
    for(int i = 0; i < FoundSequences.size(); i++)
    {
      //we check if the space has already been played and check if the square color
      if(FoundSequences[i].Scored && FoundSequences[i].player == CurrentTurn) {
        FoundSequences[i].Button->down_color(purple_Button);
        ColorButton(win, FoundSequences[i].x, FoundSequences[i].y, purple_Button, FoundSequences[i].piece);

      } else {
        FoundSequences[i].Button->down_color(FL_BLUE);
        ColorButton(win, FoundSequences[i].x, FoundSequences[i].y, FL_BLUE, FoundSequences[i].piece);
      }
    RotatePlayerTurn();
    }
   //ButtonThatWasPressed->down_color(FL_BLUE);
   FoundSequences.clear();
   Fl::redraw();

 }
 else if (Last_Player_Scored > 20 && Last_Player_Scored < 30) //player 2 scored
 {

    //ButtonThatWasPressed->down_color(FL_RED);
   for(int i = 0; i < FoundSequences.size(); i++)
    {
       if(FoundSequences[i].Scored && FoundSequences[i].player == CurrentTurn) {
        FoundSequences[i].Button->down_color(purple_Button);
        ColorButton(win, FoundSequences[i].x, FoundSequences[i].y, purple_Button, FoundSequences[i].piece);
      } else {
        FoundSequences[i].Button->down_color(FL_RED);
        ColorButton(win, FoundSequences[i].x, FoundSequences[i].y, FL_RED, FoundSequences[i].piece);
      }
    RotatePlayerTurn();
    }
    FoundSequences.clear();
   Fl::redraw();
 }

 //check if the game has ended
 if(EndGame && !debug)
 {
   int menuchoice;
   switch(GameMode)
   {
     case 0: //simple gm
     {
        char message[120];
        if(Player1Data->points > Player2Data->points)
        {
           sprintf(message, "GAME OVER.\nPlayer %d WON!\n", Player1Data->points);
        } else if (Player2Data->points > Player1Data->points)
        {
           sprintf(message, "GAME OVER.\nPlayer %d WON!\n", Player1Data->points);
        } else {
           sprintf(message, "GAME OVER.\nIt Was a Tie!\n");
        }
        menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
        break;

    }
     case 1:  //general gm
     {
        char message[120];
        //printf("%s",message);
        //if all spaces have been played, end the game
        int winner;
        if ( Player1Data->points >  Player2Data->points)
        {
        winner = 1;
        } else if ( Player1Data->points <  Player2Data->points)
        {
        winner = 2;
        } else //check if it was a tie
        {
        winner = 0;
        }

        if (winner != 0) {
        sprintf(message, "GAME OVER.\nPlayer %d WON!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.", winner,  Player1Data->points,  Player2Data->points);
        menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
        } else
        {
        sprintf(message, "GAME OVER.\nGame was a tie!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.",  Player1Data->points,  Player2Data->points);
        menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
        }
      }
     }
     switch (menuchoice)
     {
       case 0:
         //win->close();
         win->hide();
         game_main_menu();
         //HideAndResetToMainMenu(GameBoardWin);
         //Fl::handle(FL_CLOSE, (Fl_Double_Window*) GameBoardWin);
         break;
       case 1:
         win->hide();

     }
    }
}

