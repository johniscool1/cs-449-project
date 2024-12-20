
#include "screen_def.hpp"

using namespace std;

Fl_Color purple_Button = fl_rgb_color(128, 0, 128);

//intialize the game board
void GameBoard::initwin() {
    GameBoardWin = new Fl_Double_Window(GAMEBOARD_WINDOW_X, GAMEBOARD_WINDOW_Y, "SOS GAME");
}

//show the game board
void GameBoard::show()
{
 GameBoardWin->show();
}

void GameBoard::hide()
{
 GameBoardWin->hide();
}
//Set the Board Dimensions, checks if it is out of range. TODO: check if too large
bool GameBoard::SetBoardDimensions(int x, int y)
{
 if( x <= 2 || y <= 2)
 {
  return false;
 }
 else
 {
  rows = x;
  cols = y;
  return true;
 }
}


//draw the buttons for the game board
void GameBoard::DrawButtons(Player1Logic* player1data, Player2Logic* player2data, GameLogic* gameData)
{
  //draw the player controls: radio buttons for S and O
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);


 Player1Controls->begin();
 Fl_Box *P1TB = new Fl_Box(20, 80, 20, 10, "Player 1");
 P1TB->labelcolor(FL_BLUE);
 Fl_Round_Button *P1SRadio = new Fl_Round_Button(10,100, 20, 10, "S");
 Fl_Round_Button *P1ORadio = new Fl_Round_Button(10,120, 20, 10, "O");
 P1SRadio->type(FL_RADIO_BUTTON);
 P1ORadio->type(FL_RADIO_BUTTON);

 //set callbacks to set the selected piece for the player
 SelectedPieceCBdata* P1RBSdata = new SelectedPieceCBdata{P1SRadio, 1, player1data};
 SelectedPieceCBdata* P1RBOdata = new SelectedPieceCBdata{P1ORadio, 0, player1data};
 //set default to S selected
 P1SRadio->value(1);

 P1SRadio->callback(changePlayerPieceCB, P1RBSdata);
 P1ORadio->callback(changePlayerPieceCB, P1RBOdata);
 //P1SRadio->callback(DrawPlayer1Selection, "O");

 Player1Controls->end();
 //Same as player 1 bu player 2

 Fl_Group* Player2Controls = new Fl_Group(620,80, 50, 100);
 Player2Controls->begin();
 Fl_Box *P2TB = new Fl_Box(620, 80, 20, 10, "Player 2");
 P2TB->labelcolor(FL_RED);
 Fl_Round_Button *P2SRadio = new Fl_Round_Button(630,100, 20, 10, "S");
 Fl_Round_Button *P2ORadio = new Fl_Round_Button(630,120, 20, 10, "O");
 P2SRadio->type(FL_RADIO_BUTTON);
 P2ORadio->type(FL_RADIO_BUTTON);

 //set callbacks to set the selected piece for the player
 SelectedPieceCBdata* P2RBSdata = new SelectedPieceCBdata{P2SRadio, 1, player2data};
 SelectedPieceCBdata* P2RBOdata = new SelectedPieceCBdata{P2ORadio, 0, player2data};
 //set default to S selected
 P2SRadio->setonly();

 P2SRadio->callback(changePlayerPieceCB, P2RBSdata);
 P2ORadio->callback(changePlayerPieceCB, P2RBOdata);
 //P1SRadio->callback(DrawPlayer1Selection, "O");

 Player2Controls->end();

 Player2Controls->deactivate();

 int ButtonDrawX = 0;
 int ButtonDrawY = 0;




 //draw in both x and y direction
 for(int i = 0; i < rows; i++)
 {
  for(int j = 0; j < cols; j++)
  {

   ButtonDrawX = i * 42 + 100;
   ButtonDrawY = j * 42 + 100;
   BoardButton = new Fl_Toggle_Button(ButtonDrawX, ButtonDrawY, 40, 40, "");
   GameBoardButtonCBdata* cbGameButtonData = new GameBoardButtonCBdata{BoardButton, player1data, player2data, gameData->CurrentTurn, gameData, rows, cols, Player1Controls, Player2Controls, GameBoardWin};

   //set button callback
   BoardButton->callback(GameBoardButtonPressedCB, cbGameButtonData);
   //make the buttons parent windows to the board
   BoardButton->parent(GameBoardWin);
  }
 }





 GameBoardWin->redraw();
}





void playGameButtonCB(Fl_Widget*, void* data)
{
 //get data needed
 MainMenuCBdata* menuSettings = static_cast<MainMenuCBdata*>(data);
 //create new windpw
 Fl_Window* win = static_cast<Fl_Double_Window*>(menuSettings->window); // Cast void* to Fl_Window*
 win->hide();
 int xVal = static_cast<int>(menuSettings->x->value());
 int yVal = static_cast<int>(menuSettings->y->value());
 //create all the variables we need
 GameLogic* GameData;
 if(menuSettings->GeneralGamemodeRB->value() == 0)
 {
   GameData = new SimpleGameMode;
 } else {
   GameData = new GeneralGameMode;
 }

 //GameLogic* GameData = new GameLogic;
 GameBoard* sosGameBoard = new GameBoard;
 Player1Logic* player1Data = new Player1Logic;
 Player2Logic* player2Data = new Player2Logic;
 //set gamemode
 GameData->setGameMode(menuSettings->GeneralGamemodeRB->value());

 //intialize window
 sosGameBoard->initwin();
 sosGameBoard->SetBoardDimensions(xVal,yVal);
 GameData->cols = xVal;
 GameData->rows = yVal;
 sosGameBoard->DrawButtons(player1Data, player2Data, GameData);
 //sosGameBoard.DrawSettings();
 sosGameBoard->GameBoardWin->show();


}

int GetButtonXY(int x)
{
  return (x - 100) / 42;
}

static void playAgain(Fl_Double_Window GameScreen)
{
  GameScreen.hide();
  game_main_menu();

}



//callback for when a button is pressed
void GameBoardButtonPressedCB(Fl_Widget*, void* data)
{

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
      } else {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(FL_BLUE);
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
      } else {
        ButtonPressedData->GameData->FoundSequences[i].Button->down_color(FL_RED);
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


}





/*
 * Start of main menu procedures
 */
void game_main_menu()
{
 Fl_Double_Window* GMainMenu = new Fl_Double_Window(700, 700, "SOS GAME");
 Fl_Box* MM_text_box_title = new Fl_Box(50,40, 600, 200, "SOS GAME");
 MM_text_box_title->labelsize(100);

 //counters for gameboard size
 Fl_Counter *UserInputX = new Fl_Counter(200 , 200 , 70, 20);
 UserInputX->type(FL_SIMPLE_COUNTER);
 UserInputX->step(1);
 UserInputX->value(3);
 new Fl_Box(200,222, 70, 20, "Width");

 Fl_Counter *UserInputY = new Fl_Counter(350 , 200 , 70, 20);
 UserInputY->type(FL_SIMPLE_COUNTER);
 UserInputY->step(1);
 UserInputY->value(3);
 new Fl_Box(350,222, 70, 20, "Height");

 //set counter callback to check data UserInput
 MMcounter_checkCBdata* CounterCheckDataX = new MMcounter_checkCBdata{UserInputX};
 MMcounter_checkCBdata* CounterCheckDataY = new MMcounter_checkCBdata{UserInputY};


 UserInputX->callback(MMcounter_checkCB, CounterCheckDataX);
 UserInputY->callback(MMcounter_checkCB, CounterCheckDataY);

 //Gamemode selctionradio buttons
 Fl_Round_Button* SimpleGameModeRB = new Fl_Round_Button(200, 300, 70, 20, "Simple Gamemode");
 SimpleGameModeRB->type(FL_RADIO_BUTTON);

 Fl_Round_Button* GeneralGameModeRB = new Fl_Round_Button(410, 300, 70, 20, "General Gamemode");
 GeneralGameModeRB->type(FL_RADIO_BUTTON);
 //set defualt choosen gamemode
 SimpleGameModeRB->value(1);




 //play button
 Fl_Button *playButton = new Fl_Button(200, 350,300, 50, "Play");
 MainMenuCBdata* cbGameMenuData = new MainMenuCBdata{GMainMenu, UserInputX, UserInputY, SimpleGameModeRB, GeneralGameModeRB};
 playButton->callback(playGameButtonCB, cbGameMenuData);
 //Fl_Button *resButton = new Fl_Button(200, 310,300, 50, "Set Resultion");
 Fl_Button *quitButton = new Fl_Button(200, 400,300, 50, "Quit");


 GMainMenu->end();
 GMainMenu->show();


}


void MMcounter_checkCB(Fl_Widget*, void* data)
{
 //get the counter
 MMcounter_checkCBdata* Cbdata = static_cast<MMcounter_checkCBdata*>(data);
 //int counterVal = Cbdata->counter->value();
 //printf("%d\n", counterVal);
 Fl::wait();


 if(Cbdata->counter->value() < 3.0)
 {
   if(!debug)
   {
   fl_alert("GameBoard must be more than 3 x 3");
   }
   Cbdata->counter->value(3);
 }
}
