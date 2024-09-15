
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
void GameBoard::DrawButtons()
{
//variables to later caluclate where to put the buttons.
 int ButtonDrawX = 0;
 int ButtonDrawY = 0;
 for(int i = 0; i < rows; i++)
 {
  for(int j = 0; j < cols; j++)
  {
   //If these calculations are changed. change them in the Button callback. TODO: implement function
   ButtonDrawX = i * 42 + 100;
   ButtonDrawY = j * 42 + 100;
   BoardButton = new Fl_Toggle_Button(ButtonDrawX, ButtonDrawY, 40, 40, "");

   //set button callback
   BoardButton->callback(GameBoardButtonPressed, BoardButton);
   //make the buttons parent windows to the board
   BoardButton->parent(GameBoardWin);
  }
 }

 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);

 Player1Controls->begin();
 Fl_Box *P1TB = new Fl_Box(20, 80, 20, 10, "Player 1");
 Fl_Round_Button *P1SRadio = new Fl_Round_Button(10,100, 20, 10, "S");
 Fl_Round_Button *P1ORadio = new Fl_Round_Button(10,120, 20, 10, "O");
 P1SRadio->type(FL_RADIO_BUTTON);
 P1ORadio->type(FL_RADIO_BUTTON);

 //P1SRadio->callback(changePlayer1Piece, Player1Data, "S");
 //P1SRadio->callback(DrawPlayer1Selection, "O");

 Player1Controls->end();

 Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);

 Player2Controls->begin();
 Fl_Box *P2TB = new Fl_Box(620, 80, 20, 10, "Player 2");
 Fl_Round_Button *P2SRadio = new Fl_Round_Button(630,100, 20, 10, "S");
 Fl_Round_Button *P2ORadio = new Fl_Round_Button(630,120, 20, 10, "O");
 P2SRadio->type(FL_RADIO_BUTTON);
 P2ORadio->type(FL_RADIO_BUTTON);

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




void playGameButtonCB(Fl_Widget*, void * window)
{
 Fl_Window* win = static_cast<Fl_Double_Window*>(window); // Cast void* to Fl_Window*
 win->hide();
 GameLogic GameData;
 GameBoard sosGameBoard;
 sosGameBoard.initwin();
 sosGameBoard.SetBoardDimensions(10,10);
 sosGameBoard.DrawButtons();
 //sosGameBoard.DrawSettings();
 sosGameBoard.show();


}

void game_main_menu()
{
 Fl_Double_Window* GMainMenu = new Fl_Double_Window(700, 700, "SOS GAME");
 Fl_Box* MM_text_box_title = new Fl_Box(50,40, 600, 200, "SOS GAME");
 MM_text_box_title->labelsize(100);

 //play button
 Fl_Button *playButton = new Fl_Button(200, 255,300, 50, "Play");
 playButton->callback(playGameButtonCB, GMainMenu);
 Fl_Button *resButton = new Fl_Button(200, 310,300, 50, "Set Resultion");
 Fl_Button *quitButton = new Fl_Button(200, 365,300, 50, "quit");


 GMainMenu->end();
 GMainMenu->show();



}

//callback for when a button is pressed
void GameBoard::GameBoardButtonPressed(Fl_Widget*, void* ButtonThatPressed)
{
 //variable to caluclate where the buttons are
 int ButtonX, ButtonY;
 //"grab" tjhe button to use it in this function
 Fl_Toggle_Button *ButtonThatWasPressed = (Fl_Toggle_Button*)ButtonThatPressed;
 ButtonX = ButtonThatWasPressed->x();
 ButtonY = ButtonThatWasPressed->y();
 //find the button
 ButtonX = (ButtonX - 100) / 42;
 ButtonY = (ButtonY - 100) / 42;

 //print to console where the button was pressed
 //printf("Button %d,", ButtonX);
 //printf("%d\n", ButtonY);




 ButtonThatWasPressed->label("S");

 //keep button down
 ButtonThatWasPressed->deactivate();
}


