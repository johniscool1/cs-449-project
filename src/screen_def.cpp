
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

//Set the Board Dimensions, checks if it is out of range. TODO: check if too large
bool GameBoard::SetBoardDimensions(int x, int y)
{
 if( x <= 2 || y <= 2)
 {
  return False;
 }
 else
 {
  rows = x;
  cols = y;
  return True;
 }
}

//draw the buttons for the game board
void GameBoard::DrawButtons(Player1Logic* player1data, Player2Logic* player2data, GameLogic* gameData)
{
//variables to later caluclate where to put the buttons.
 int ButtonDrawX = 0;
 int ButtonDrawY = 0;

 //draw in both x and y direction
 for(int i = 0; i < rows; i++)
 {
  for(int j = 0; j < cols; j++)
  {
   //If these calculations are changed. change them in the Button callback. TODO: implement function
   ButtonDrawX = i * 42 + 100;
   ButtonDrawY = j * 42 + 100;
   BoardButton = new Fl_Toggle_Button(ButtonDrawX, ButtonDrawY, 40, 40, "");
   //cbGameButtonData->Button = BoardButton;
   GameBoardButtonPressedData* cbGameButtonData = new GameBoardButtonPressedData{BoardButton, player1data, player2data, gameData->CurrentTurn, gameData, rows, cols};

   //set button callback
   BoardButton->callback(GameBoardButtonPressed, cbGameButtonData);
   //make the buttons parent windows to the board
   BoardButton->parent(GameBoardWin);
  }
 }
 //draw the player controls: radio buttons for S and O
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);

 Player1Controls->begin();
 Fl_Box *P1TB = new Fl_Box(20, 80, 20, 10, "Player 1");
 Fl_Round_Button *P1SRadio = new Fl_Round_Button(10,100, 20, 10, "S");
 Fl_Round_Button *P1ORadio = new Fl_Round_Button(10,120, 20, 10, "O");
 P1SRadio->type(FL_RADIO_BUTTON);
 P1ORadio->type(FL_RADIO_BUTTON);

 //set callbacks to set the selected piece for the player
 SelectedPieceCBdata* P1RBSdata = new SelectedPieceCBdata{P1SRadio, 1, player1data};
 SelectedPieceCBdata* P1RBOdata = new SelectedPieceCBdata{P1ORadio, 0, player1data};
 //set default to S selected
 P1SRadio->value(1);

 P1SRadio->callback(changePlayer1Piece, P1RBSdata);
 P1ORadio->callback(changePlayer1Piece, P1RBOdata);
 //P1SRadio->callback(DrawPlayer1Selection, "O");

 Player1Controls->end();
 //Same as player 1 bu player 2
 Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);

 Player2Controls->begin();
 Fl_Box *P2TB = new Fl_Box(620, 80, 20, 10, "Player 2");
 Fl_Round_Button *P2SRadio = new Fl_Round_Button(630,100, 20, 10, "S");
 Fl_Round_Button *P2ORadio = new Fl_Round_Button(630,120, 20, 10, "O");
 P2SRadio->type(FL_RADIO_BUTTON);
 P2ORadio->type(FL_RADIO_BUTTON);
 SelectedPieceCBdata P2RadioButtonData;

 //P2SRadio->callback(GameData.Change);


 Player2Controls->end();


 //make sure the are all drawn
 GameBoardWin->redraw();
}


/*
void GameBoard::DrawSettings()
{
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);

 Player1Controls->begin();
 Fl_Box *P1TB = new Fl_Box(15, 80, 20, 10, "Player 1");
 Fl_Round_Button *P1SRadio = new Fl_Round_Button(10,100, 20, 10, "S");
 Fl_Round_Button *P2ORadio = new Fl_Round_Button(10,120, 20, 10, "O");
 P1SRadio->type(FL_RADIO_BUTTON);
 P2ORadio->type(FL_RADIO_BUTTON);

 P1SRadio->callback();


 Player1Controls->end();


}
*/




void playGameButtonCB(Fl_Widget*, void* data)
{
 //get data needed
 CallbackDataMainMenu* menuSettings = static_cast<CallbackDataMainMenu*>(data);
 //create new windpw
 Fl_Window* win = static_cast<Fl_Double_Window*>(menuSettings->window); // Cast void* to Fl_Window*
 win->hide();

 int xVal = static_cast<int>(menuSettings->x->value());
 int yVal = static_cast<int>(menuSettings->y->value());
 //create all the variables we need
 GameLogic* GameData = new GameLogic;
 GameBoard* sosGameBoard = new GameBoard;
 Player1Logic* player1Data = new Player1Logic;
 Player2Logic* player2Data = new Player2Logic;
 //set gamemode
 switch (menuSettings->GeneralGamemodeRB->value()) {
   case 1:
     GameData->GameMode = 1;
   //if the General Gamemode radio button isn't checked, then it is simple gamemode
   case 0:
     GameData->GameMode = 0;
 }



 //intialize window
 sosGameBoard->initwin();
 sosGameBoard->SetBoardDimensions(xVal,yVal);
 sosGameBoard->DrawButtons(player1Data, player2Data, GameData);
 //sosGameBoard.DrawSettings();
 sosGameBoard->show();


}




//callback for when a button is pressed
void GameBoard::GameBoardButtonPressed(Fl_Widget*, void* data)
{

 GameBoardButtonPressedData* ButtonPressedData = reinterpret_cast<GameBoardButtonPressedData*>(data);

 //variable to caluclate where the buttons are
 int ButtonX, ButtonY;
 //"grab" tjhe button to use it in this function
 Fl_Toggle_Button *ButtonThatWasPressed = (Fl_Toggle_Button*)ButtonPressedData->Button;
 ButtonX = ButtonThatWasPressed->x();
 ButtonY = ButtonThatWasPressed->y();
 //find the button
 ButtonX = (ButtonX - 100) / 42;
 ButtonY = (ButtonY - 100) / 42;

 int current_player = ButtonPressedData->currentPlayer;
 //printf("Piece int: %d  ", ButtonPressedData->Player1Data.SelectedPiece);
 const char* piece;

 switch (ButtonPressedData->Player1Data->SelectedPiece)
 {
   case 1:
    piece = "S";
    break;
   case 0:
    piece = "O";
    break;
 }
 //printf("Piece: %s\n", piece);


 ButtonThatWasPressed->label(piece);

 //keep button down
 ButtonThatWasPressed->deactivate();

 //add button to are list of played spaces
 ButtonPressedData->GameData->addMovetoList(ButtonX, ButtonY, ButtonPressedData->Player1Data->SelectedPiece);
 //See if sequence was created
 ButtonPressedData->GameData->SequenceFinder(ButtonPressedData->rows, ButtonPressedData->cols);
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
 MMcounter_checkCBdata* CounterCheckDataX = new MMcounter_checkCBdata{UserInputX, false};
 MMcounter_checkCBdata* CounterCheckDataY = new MMcounter_checkCBdata{UserInputY, false};


 UserInputX->callback(MMcounter_check, CounterCheckDataX);
 UserInputY->callback(MMcounter_check, CounterCheckDataY);

 //Gamemode selctionradio buttons
 Fl_Round_Button* SimpleGameModeRB = new Fl_Round_Button(200, 300, 70, 20, "Simple Gamemode");
 SimpleGameModeRB->type(FL_RADIO_BUTTON);

 Fl_Round_Button* GeneralGameModeRB = new Fl_Round_Button(410, 300, 70, 20, "General Gamemode");
 GeneralGameModeRB->type(FL_RADIO_BUTTON);
 //set defualt choosen gamemode
 SimpleGameModeRB->value(1);




 //play button
 Fl_Button *playButton = new Fl_Button(200, 350,300, 50, "Play");
 CallbackDataMainMenu* cbGameMenuData = new CallbackDataMainMenu{GMainMenu, UserInputX, UserInputY, SimpleGameModeRB, GeneralGameModeRB};
 playButton->callback(playGameButtonCB, cbGameMenuData);
 //Fl_Button *resButton = new Fl_Button(200, 310,300, 50, "Set Resultion");
 Fl_Button *quitButton = new Fl_Button(200, 400,300, 50, "Quit");


 GMainMenu->end();
 GMainMenu->show();


}


void MMcounter_check(Fl_Widget*, void* data)
{
 //get the counter
 MMcounter_checkCBdata* Cbdata = static_cast<MMcounter_checkCBdata*>(data);
 //int counterVal = Cbdata->counter->value();
 //printf("%d\n", counterVal);
 Fl::wait();


 if(Cbdata->counter->value() < 3.0 && !Cbdata->alertDisplayed)
 {
   fl_alert("GameBoard must be more than 3 x 3");
   Cbdata->counter->value(3);
 }
}
