#include "game_logic.hpp"
#include "screen_def.hpp"

void GameBoardButtonPressedCB(Fl_Widget*, void* data)
{

 startOfButton:
 GameBoardButtonCBdata* ButtonPressedData = reinterpret_cast<GameBoardButtonCBdata*>(data);

 //variable to caluclate where the buttons are
 int ButtonX, ButtonY;
 //"grab" tjhe button to use it in this function
 Fl_Toggle_Button *ButtonThatWasPressed = (Fl_Toggle_Button*)ButtonPressedData->Button;
 ButtonX = ButtonThatWasPressed->x();
 ButtonY = ButtonThatWasPressed->y();
 //find the button
 ButtonX =  GetButtonXY(ButtonX);
 ButtonY = GetButtonXY(ButtonY);




 /*
  *
  * CPU player plays
  *
  */
 if((ButtonPressedData->GameData->CPUpresent && ButtonPressedData->GameData->CPUplayernum == ButtonPressedData->GameData->CurrentTurn) || ButtonPressedData->GameData->CPUplayernum == 3)
 {
  if(ButtonPressedData->GameData->CPUplayernum == 1)
  {
    ButtonPressedData->GameData->CPUseek(ButtonPressedData->GameScreen);
    //add artifical pause
    ButtonPressedData->P1Group->deactivate();
    Fl::wait();
    sleep(1);

  } else if (ButtonPressedData->GameData->CPUplayernum == 2)
  {
    Fl::wait();
    sleep(1);
    ButtonPressedData->GameData->CPUseek(ButtonPressedData->GameScreen);
    Fl::redraw();


  } else if (ButtonPressedData->GameData->CPUplayernum == 3)
  {
    Fl::wait();
    sleep(1);
    ButtonPressedData->GameData->CPUseek(ButtonPressedData->GameScreen);
    Fl::redraw();
  }

 } else {

     /*
      *
      *
      * regular player goes
      *
      *
      */

 //printf("Piece int: %d  ", ButtonPressedData->Player1Data.SelectedPiece);
 const char* piece;
 if (ButtonPressedData->GameData->CurrentTurn == 1)
 {
 switch (ButtonPressedData->Player1Data->SelectedPiece)
 {
   case 1:
    piece = "S";
    break;
   case 0:
    piece = "O";
    break;
 }
 //add button to are list of played spaces
 ButtonPressedData->GameData->addMovetoList(ButtonX, ButtonY, ButtonPressedData->Player1Data->SelectedPiece, ButtonThatWasPressed);
 //printf("Piece: %s\n", piece);
 }
 else
 {
 switch (ButtonPressedData->Player2Data->SelectedPiece)
 {
   case 1:
    piece = "S";
    break;
   case 0:
    piece = "O";
    break;
 }
 //add button to are list of played spaces
 ButtonPressedData->GameData->addMovetoList(ButtonX, ButtonY, ButtonPressedData->Player2Data->SelectedPiece, ButtonThatWasPressed);

 }

 ButtonThatWasPressed->label(piece);

 //keep button down
 ButtonThatWasPressed->deactivate();
 }


 /*
  *
  * The following runs every time
  *
  */


 //rotate CurrentTurn
 ButtonPressedData->GameData->RotatePlayerTurn();
 //deactivate and activate the radio buttons for players

  //See if sequence was created
 ButtonPressedData->GameData->SequenceFinder(ButtonPressedData->rows, ButtonPressedData->cols, ButtonPressedData->Player1Data, ButtonPressedData->Player2Data);



 ButtonPressedData->GameData->CheckOutcome();
 //Change the color of the buttons to indiacte they have been scored we also.
 //we also roate out the turn os that the player goes again
 if(ButtonPressedData->GameData->Last_Player_Scored > 10 && ButtonPressedData->GameData->Last_Player_Scored < 20) //player 1 scored
 {
    for(int i = 0; i < ButtonPressedData->GameData->FoundSequences.size(); i++)
    {
      //we check if the space has already been played and check if the square color
      if(ButtonPressedData->GameData->FoundSequences[i].Scored && ButtonPressedData->GameData->FoundSequences[i].player == ButtonPressedData->GameData->CurrentTurn) {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(purple_Button);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, purple_Button, ButtonPressedData->GameData->FoundSequences[i].piece);

      } else {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(FL_BLUE);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, FL_BLUE, ButtonPressedData->GameData->FoundSequences[i].piece);
      }
    ButtonPressedData->GameData->RotatePlayerTurn();
    }
   //ButtonThatWasPressed->down_color(FL_BLUE);
   ButtonPressedData->GameData->FoundSequences.clear();
   Fl::redraw();

 }
 else if (ButtonPressedData->GameData->Last_Player_Scored > 20 && ButtonPressedData->GameData->Last_Player_Scored < 30) //player 2 scored
 {

    //ButtonThatWasPressed->down_color(FL_RED);
   for(int i = 0; i < ButtonPressedData->GameData->FoundSequences.size(); i++)
    {
       if(ButtonPressedData->GameData->FoundSequences[i].Scored && ButtonPressedData->GameData->FoundSequences[i].player == ButtonPressedData->GameData->CurrentTurn) {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(purple_Button);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, purple_Button, ButtonPressedData->GameData->FoundSequences[i].piece);
      } else {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(FL_RED);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, FL_RED, ButtonPressedData->GameData->FoundSequences[i].piece);
      }
    ButtonPressedData->GameData->RotatePlayerTurn();
    }
    ButtonPressedData->GameData->FoundSequences.clear();
   Fl::redraw();
 }

 //check if the game has ended
 if(ButtonPressedData->GameData->EndGame && !debug)
 {
   int menuchoice;
   switch(ButtonPressedData->GameData->GameMode)
   {
     case 0: //simple gm
     {
        char message[120];
        if(ButtonPressedData->Player1Data->points > ButtonPressedData->Player2Data->points)
        {
           sprintf(message, "GAME OVER.\nPlayer %d WON!\n", ButtonPressedData->Player1Data->points);
        } else if (ButtonPressedData->Player2Data->points > ButtonPressedData->Player1Data->points)
        {
           sprintf(message, "GAME OVER.\nPlayer %d WON!\n", ButtonPressedData->Player1Data->points);
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
        if ( ButtonPressedData->Player1Data->points >  ButtonPressedData->Player2Data->points)
        {
        winner = 1;
        } else if ( ButtonPressedData->Player1Data->points <  ButtonPressedData->Player2Data->points)
        {
        winner = 2;
        } else //check if it was a tie
        {
        winner = 0;
        }

        if (winner != 0) {
        sprintf(message, "GAME OVER.\nPlayer %d WON!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.", winner,  ButtonPressedData->Player1Data->points,  ButtonPressedData->Player2Data->points);
        menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
        } else
        {
        sprintf(message, "GAME OVER.\nGame was a tie!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.",  ButtonPressedData->Player1Data->points,  ButtonPressedData->Player2Data->points);
        menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
        }
      }
     }
     switch (menuchoice)
     {
       case 0:
         //win->close();
         ButtonPressedData->GameScreen->hide();
         game_main_menu();
         //HideAndResetToMainMenu(GameBoardWin);
         //Fl::handle(FL_CLOSE, (Fl_Double_Window*) GameBoardWin);
         break;
       case 1:
         ButtonPressedData->GameScreen->hide();

     }
    }






        // deactive players controls
 if(!ButtonPressedData->GameData->CPUpresent) {
 switch(ButtonPressedData->GameData->CurrentTurn)
 {
   case 1:
    ButtonPressedData->P2Group->deactivate();
    ButtonPressedData->P1Group->activate();

    break;
   case 2:
    ButtonPressedData->P1Group->deactivate();
    ButtonPressedData->P2Group->activate();
    break;
 };
 } else {
   if(ButtonPressedData->GameData->CurrentTurn == ButtonPressedData->GameData->CPUplayernum && ButtonPressedData->GameData->CPUplayernum == 2){
     ButtonPressedData->P1Group->deactivate();
   } else if (ButtonPressedData->GameData->CurrentTurn != ButtonPressedData->GameData->CPUplayernum && ButtonPressedData->GameData->CPUplayernum == 2)
   {
     ButtonPressedData->P1Group->activate();
   } else if(ButtonPressedData->GameData->CurrentTurn == ButtonPressedData->GameData->CPUplayernum && ButtonPressedData->GameData->CPUplayernum == 1) {
     ButtonPressedData->P2Group->deactivate();
   } else if(ButtonPressedData->GameData->CurrentTurn != ButtonPressedData->GameData->CPUplayernum && ButtonPressedData->GameData->CPUplayernum == 1) {
     ButtonPressedData->P2Group->activate();
   }
  }



 if(ButtonPressedData->GameData->CPUpresent && ButtonPressedData->GameData->CPUplayernum == ButtonPressedData->GameData->CurrentTurn && !ButtonPressedData->GameData->EndGame)
 {
   //goes to the start of this function. Please dont take off point for this, I know its bad practice, but this was the easiest way to do this.
   goto startOfButton;
 }
 //check cpu player

}


void GameLogic::HandleButtonPlayed(PlayerLogic player1data, PlayerLogic Player2Data)
{
 //rotate CurrentTurn
 RotatePlayerTurn();
 //deactivate and activate the radio buttons for players

  //See if sequence was created
 SequenceFinder(ButtonPressedData->rows, ButtonPressedData->cols, Player1Data, Player2Data);



 ButtonPressedData->GameData->CheckOutcome();
 //Change the color of the buttons to indiacte they have been scored we also.
 //we also roate out the turn os that the player goes again
 if(ButtonPressedData->GameData->Last_Player_Scored > 10 && ButtonPressedData->GameData->Last_Player_Scored < 20) //player 1 scored
 {
    for(int i = 0; i < ButtonPressedData->GameData->FoundSequences.size(); i++)
    {
      //we check if the space has already been played and check if the square color
      if(ButtonPressedData->GameData->FoundSequences[i].Scored && ButtonPressedData->GameData->FoundSequences[i].player == ButtonPressedData->GameData->CurrentTurn) {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(purple_Button);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, purple_Button, ButtonPressedData->GameData->FoundSequences[i].piece);

      } else {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(FL_BLUE);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, FL_BLUE, ButtonPressedData->GameData->FoundSequences[i].piece);
      }
    ButtonPressedData->GameData->RotatePlayerTurn();
    }
   //ButtonThatWasPressed->down_color(FL_BLUE);
   ButtonPressedData->GameData->FoundSequences.clear();
   Fl::redraw();

 }
 else if (ButtonPressedData->GameData->Last_Player_Scored > 20 && ButtonPressedData->GameData->Last_Player_Scored < 30) //player 2 scored
 {

    //ButtonThatWasPressed->down_color(FL_RED);
   for(int i = 0; i < ButtonPressedData->GameData->FoundSequences.size(); i++)
    {
       if(ButtonPressedData->GameData->FoundSequences[i].Scored && ButtonPressedData->GameData->FoundSequences[i].player == ButtonPressedData->GameData->CurrentTurn) {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(purple_Button);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, purple_Button, ButtonPressedData->GameData->FoundSequences[i].piece);
      } else {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(FL_RED);
        ColorButton(ButtonPressedData->GameScreen, ButtonPressedData->GameData->FoundSequences[i].x, ButtonPressedData->GameData->FoundSequences[i].y, FL_RED, ButtonPressedData->GameData->FoundSequences[i].piece);
      }
    ButtonPressedData->GameData->RotatePlayerTurn();
    }
    ButtonPressedData->GameData->FoundSequences.clear();
   Fl::redraw();
 }

 //check if the game has ended
 if(ButtonPressedData->GameData->EndGame && !debug)
 {
   int menuchoice;
   switch(ButtonPressedData->GameData->GameMode)
   {
     case 0: //simple gm
     {
        char message[120];
        if(ButtonPressedData->Player1Data->points > ButtonPressedData->Player2Data->points)
        {
           sprintf(message, "GAME OVER.\nPlayer %d WON!\n", ButtonPressedData->Player1Data->points);
        } else if (ButtonPressedData->Player2Data->points > ButtonPressedData->Player1Data->points)
        {
           sprintf(message, "GAME OVER.\nPlayer %d WON!\n", ButtonPressedData->Player1Data->points);
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
        if ( ButtonPressedData->Player1Data->points >  ButtonPressedData->Player2Data->points)
        {
        winner = 1;
        } else if ( ButtonPressedData->Player1Data->points <  ButtonPressedData->Player2Data->points)
        {
        winner = 2;
        } else //check if it was a tie
        {
        winner = 0;
        }

        if (winner != 0) {
        sprintf(message, "GAME OVER.\nPlayer %d WON!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.", winner,  ButtonPressedData->Player1Data->points,  ButtonPressedData->Player2Data->points);
        menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
        } else
        {
        sprintf(message, "GAME OVER.\nGame was a tie!\nPlayer 1 Score: %d.\nPlayer 2 Score: %d.",  ButtonPressedData->Player1Data->points,  ButtonPressedData->Player2Data->points);
        menuchoice = fl_choice((const char*)message, "Play Again", "Quit", 0,0);
        }
      }
     }
     switch (menuchoice)
     {
       case 0:
         //win->close();
         ButtonPressedData->GameScreen->hide();
         game_main_menu();
         //HideAndResetToMainMenu(GameBoardWin);
         //Fl::handle(FL_CLOSE, (Fl_Double_Window*) GameBoardWin);
         break;
       case 1:
         ButtonPressedData->GameScreen->hide();

     }
    }
}
