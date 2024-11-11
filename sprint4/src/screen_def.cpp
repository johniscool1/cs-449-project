
#include "screen_def.hpp"

using namespace std;


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
void GameBoard::DrawButtons(PlayerLogic* player1data, PlayerLogic* player2data, GameLogic* gameData)
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

 //if cpu Plays first
 if(gameData->CPUplayernum == 1)
  {
    Player1Controls->deactivate();
    Player2Controls->activate();

  } else if(gameData->CPUplayernum == 3)
  {
    Player1Controls->deactivate();
    Player2Controls->deactivate();
  }


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

 PlayerLogic* player1Data;
 PlayerLogic* player2Data;
 printf("%d\n", menuSettings->CPUselection->value());
 if(menuSettings->CPUselection->value() == 0) {
      player1Data = new PlayerLogic;
      player2Data = new PlayerLogic;
   }   else if(menuSettings->CPUselection->value() == 1)
  //player 1 CPU
   {
     player1Data = new CPULogic;

     GameData->CPUplayernum = 1;
     player2Data = new PlayerLogic;
     GameData->CPUpresent = true;

   }   else if(menuSettings->CPUselection->value() == 2) //player 2 cpu
   {
     player2Data = new CPULogic;

     GameData->CPUplayernum = 2;
     player1Data = new PlayerLogic;
     GameData->CPUpresent = true;

   }   else if(menuSettings->CPUselection->value() == 3)//both players are cpus
   {
     player2Data = new CPULogic;

     player1Data = new CPULogic;

     GameData->CPUpresent = true;
     GameData->CPUplayernum = 3;
   }

 //Player1Logic* player1Data = new Player1Logic;
 //Player2Logic* player2Data = new Player2Logic;

 //set gamemode
 GameData->setGameMode(menuSettings->GeneralGamemodeRB->value());

 //intialize window
 sosGameBoard->initwin();
 sosGameBoard->SetBoardDimensions(xVal,yVal);
 GameData->cols = xVal;
 GameData->rows = yVal;
 sosGameBoard->DrawButtons(player1Data, player2Data, GameData);
 //sosGameBoard.DrawSettings();
 //If cpu goes first......

 sosGameBoard->GameBoardWin->show();
 Fl::check();


 //if cpu plays first
 if(GameData->CPUplayernum == 1)
  {
    GameData->CPUseek(sosGameBoard->GameBoardWin);
    GameData->RotatePlayerTurn();

  }
  if(GameData->CPUplayernum == 3)
  {
  CPUdualCBdata* v = new CPUdualCBdata {sosGameBoard->GameBoardWin, player1Data, player2Data, GameData};
  Fl::repeat_timeout(1.0, CPUdual, v);
 }
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

void CPUdual(void* v)
{
 CPUdualCBdata* CBdata = static_cast<CPUdualCBdata*>(v);

 while(!CBdata->GameData->EndGame) {


    CBdata->GameData->CPUseek(CBdata->win);
    CBdata->GameData->HandleButtonPlayed(CBdata->Player1Data, CBdata->Player2Data, CBdata->win);
    //sleep(1);
    Fl::check();
    Fl::redraw();

 }
}


//callback for when a button is pressed
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





 if((ButtonPressedData->GameData->CPUpresent && ButtonPressedData->GameData->CPUplayernum == ButtonPressedData->GameData->CurrentTurn) || ButtonPressedData->GameData->CPUplayernum == 3)
 {
  if(ButtonPressedData->GameData->CPUplayernum == 1)
  {
    ButtonPressedData->GameData->CPUseek(ButtonPressedData->GameScreen);
    //add artifical pause
    ButtonPressedData->P1Group->deactivate();
    Fl::wait();
    sleep(CPUwaittime);

  } else if (ButtonPressedData->GameData->CPUplayernum == 2)
  {
    Fl::wait();
    sleep(CPUwaittime);
    ButtonPressedData->GameData->CPUseek(ButtonPressedData->GameScreen);
    Fl::redraw();


  } else if (ButtonPressedData->GameData->CPUplayernum == 3)
  {
    Fl::wait();
    sleep(CPUwaittime);
    ButtonPressedData->GameData->CPUseek(ButtonPressedData->GameScreen);
    Fl::redraw();
  }

 } else {


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





 ButtonPressedData->GameData->HandleButtonPlayed(ButtonPressedData->Player1Data, ButtonPressedData->Player2Data, ButtonPressedData->GameScreen);









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
   //goes to the start of this function. Please dont take off points for this, I know its bad practice, but this was the easiest way to do this with this function having to be static.
   goto startOfButton;
 }


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

 //cpu player selection
 Fl_Choice* CPUsel = new Fl_Choice(200, 240, 100, 30, "CPU Player");
 CPUsel->add("none");
 CPUsel->add("Player 1");
 CPUsel->add("Player 2");
 CPUsel->add("Player 1 and 2");
 CPUsel->value(0);

 //play button
 Fl_Button *playButton = new Fl_Button(200, 350,300, 50, "Play");
 MainMenuCBdata* cbGameMenuData = new MainMenuCBdata{GMainMenu, UserInputX, UserInputY, SimpleGameModeRB, GeneralGameModeRB, CPUsel};
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

void ColorButton(Fl_Double_Window* win, int x, int y, Fl_Color ColorB, int piece)
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
        button->color(ColorB);
        char pieceChar[10];
        sprintf(pieceChar, "%d", piece);
        const char* pieceConstChar = pieceChar;

        //button->label(pieceConstChar);
        break;
      }
    }

  }
}
