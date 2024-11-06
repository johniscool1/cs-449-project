#include "game_logic.hpp"
#include "screen_def.hpp"

using namespace std;

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
 vector <filledSpace> TempSpacesPlayed = SpacesPlayed;
 //keep track of who the current player was
 int TempCurrentTurn = CurrentTurn;
 FoundSequences.clear();

 SpacesPlayed.clear();
 filledSpace CPUmove;


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
        break;
      }
    }
  }


  if(CPUmove.x > rows || CPUmove.x < 0 || CPUmove.y > cols || CPUmove.x < 0)
  {
    printf("----------------------\n");
    printf("MAJOR ERROR, OUT OF BOUNDS\n");
    printf("%d, Y: %d\n", CPUmove.x, CPUmove.y);
    printAllSequences(FoundSequences);
    printf("----------------------\n");
    FoundSequences.clear();
  }
  if(FoundSequences.size() == 0 || CPUmove.x > rows || CPUmove.x < 0)
 {
   printf("Giving up, rand placement\n");
   SpacesPlayed.clear();
  SpacesPlayed = TempSpacesPlayed;
   bool exitLoop = false;
   srand (time(NULL));
   while(!exitLoop)
   {

    int randx = rand() % cols;  // Bitwise AND with max positive int
    int randy = rand() % rows;
    int randp = rand() % 2;
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



 //printf("Play here X: %d, Y: %d\n", CPUmove.x, CPUmove.y);
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


 FoundSequences.clear();
 CurrentTurn = TempCurrentTurn;
 SpacesPlayed = TempSpacesPlayed;

 //CPU makes move
 addMovetoList(CPUmove.x, CPUmove.y, CPUmove.piece, button);
 printf("---------DONE----------\n");
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
void GameLogic::printAllSequences(const vector<tempFilledSpace>& sequences) {
    printf("\n=== All Found Sequences (%zu total) ===\n", sequences.size());
    for (size_t i = 0; i < sequences.size(); i++) {
        printf("Sequence[%zu]: x=%d, y=%d, piece=%d\n",
               i, sequences[i].x, sequences[i].y, sequences[i].piece);
    }
    printf("=====================================\n");
}
