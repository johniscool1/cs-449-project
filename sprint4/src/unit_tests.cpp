#define CATCH_CONFIG_MAIN
#include "test_lib/catch_amalgamated.hpp"
#include "screen_def.hpp"
#include "game_logic.hpp"

using namespace std;


bool debug = true;
int CPUwaittime = 0;

//gcc -g -o tests tests.cpp test_lib/catch_amalgamated.cpp screen_def.cpp game_logic.cpp game_logic.hpp -lfltk -lm -lstdc++

//TEST ID 1
TEST_CASE("ID 1.1: Choose Gameboard Size is > 3")
{
 GameBoard* GameScreen;
 Fl_Counter *UserInputX = new Fl_Counter(200 , 200 , 70, 20);
 Fl_Counter *UserInputY = new Fl_Counter(350 , 200 , 70, 20);
 UserInputX->value(3);
 UserInputY->value(3);
 //overide the FLTK alert Function
 MMcounter_checkCBdata* CounterCheck = new MMcounter_checkCBdata{UserInputX};
 MMcounter_checkCB(nullptr, CounterCheck);
 int Counter_val = UserInputX->value();
  //checks if the function changed the value that is under 3 to 3
 REQUIRE(Counter_val == 3);

 delete UserInputX;
 delete UserInputY;
 delete CounterCheck;
}


TEST_CASE("ID 1.2: Choose Gameboard Size is < 3")
{
 GameBoard* GameScreen;
 Fl_Counter *UserInputX = new Fl_Counter(200 , 200 , 70, 20);
 Fl_Counter *UserInputY = new Fl_Counter(350 , 200 , 70, 20);
 UserInputX->value(1);
 UserInputY->value(3);
 //overide the FLTK alert Function
 MMcounter_checkCBdata* CounterCheck = new MMcounter_checkCBdata{UserInputX};
 MMcounter_checkCB(nullptr, CounterCheck);
 int Counter_val = UserInputX->value();
 //checks if the function changed the value that is under 3 to 3
 REQUIRE(Counter_val == 3);


 delete UserInputX;
 delete UserInputY;
 delete CounterCheck;

}


/*
 *
 *  AC 2 AI generated test cases
 *
 */


TEST_CASE("ID 2.1 User presses Simple Gamemode")
{
 // Initialize game logic
 SimpleGameMode* GameData = new SimpleGameMode;
 // Create the radio buttons for game modes
 Fl_Round_Button* SimpleGameModeRB = new Fl_Round_Button(200, 300, 70, 20, "Simple Gamemode");
 SimpleGameModeRB->type(FL_RADIO_BUTTON);
 Fl_Round_Button* GeneralGameModeRB = new Fl_Round_Button(410, 300, 70, 20, "General Gamemode");
 GeneralGameModeRB->type(FL_RADIO_BUTTON);
 // Simulate user selecting the simple game mode
 SimpleGameModeRB->value(1);
 // Call the game logic to set the mode based on the user's selection
 GameData->setGameMode(SimpleGameModeRB->value());
 // Check that the simple game mode was correctly set in GameLogic
 REQUIRE(GameData->GameMode == 1);

 delete GameData;
 delete SimpleGameModeRB;
 delete GeneralGameModeRB;
}

TEST_CASE("ID 2.2 User presses General Gamemode")
{
 // Initialize game logic
 GeneralGameMode* GameData = new GeneralGameMode;
 // Create the radio buttons for game modes
 Fl_Round_Button* SimpleGameModeRB = new Fl_Round_Button(200, 300, 70, 20, "Simple Gamemode");
 SimpleGameModeRB->type(FL_RADIO_BUTTON);
 Fl_Round_Button* GeneralGameModeRB = new Fl_Round_Button(410, 300, 70, 20, "General Gamemode");
 GeneralGameModeRB->type(FL_RADIO_BUTTON);
 // Simulate user selecting the general game mode
 GeneralGameModeRB->value(1);
 // Call the game logic to set the mode based on the user's selection
 GameData->setGameMode(SimpleGameModeRB->value());
 // Check that the general game mode was correctly set in GameLogic
 REQUIRE(GameData->GameMode == 0);

 // Clean up
 delete GameData;
 delete SimpleGameModeRB;
 delete GeneralGameModeRB;
}


TEST_CASE("ID 3.1 Create gameboard given size")
{
 GeneralGameMode* GameData = new GeneralGameMode;
 Fl_Round_Button* SimpleGameModeRB = new Fl_Round_Button(200, 300, 70, 20, "Simple Gamemode");
 SimpleGameModeRB->type(FL_RADIO_BUTTON);

 Fl_Round_Button* GeneralGameModeRB = new Fl_Round_Button(410, 300, 70, 20, "General Gamemode");
 GeneralGameModeRB->type(FL_RADIO_BUTTON);
 //user chooses General gamemode
 GeneralGameModeRB->value(1);
 GameData->setGameMode(SimpleGameModeRB->value());
 REQUIRE(GameData->GameMode == 0);

 GameBoard* GameScreen;
 Fl_Counter *UserInputX = new Fl_Counter(200 , 200 , 70, 20);
 Fl_Counter *UserInputY = new Fl_Counter(350 , 200 , 70, 20);
 UserInputX->value(3);
 UserInputY->value(3);
 //overide the FLTK alert Function
 MMcounter_checkCBdata* CounterCheck = new MMcounter_checkCBdata{UserInputX};
 MMcounter_checkCB(nullptr, CounterCheck);
 int Counter_val = UserInputX->value();
 REQUIRE(Counter_val == 3);
 delete GameData;
 delete SimpleGameModeRB;
 delete GeneralGameModeRB;
 delete UserInputX;
 delete UserInputY;
 delete CounterCheck;
}




TEST_CASE("ID 4.1 & 6.1 Player places a S or O")
{
 SimpleGameMode* GameData;
 GameData = new SimpleGameMode;
 GameBoard* GameScreen = new GameBoard;
 PlayerLogic* player1Data = new PlayerLogic;
 PlayerLogic* player2Data = new PlayerLogic;
 //set piece to s
 player1Data->SelectedPiece = 1;
 //create the groups
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);
 Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);
 //create the button pressed
 GameScreen->BoardButton = new Fl_Toggle_Button(226, 226 ,40, 40, "");
 //run the callback for the button
 GameBoardButtonCBdata* GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 1, GameData, 3, 3, Player1Controls, Player2Controls};
 GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 //check the vector that holds all the played areas
 REQUIRE(GameData->SpacesPlayed[0].piece == 1);
 REQUIRE(GameData->SpacesPlayed[0].x == 3);
 REQUIRE(GameData->SpacesPlayed[0].y == 3);
}

TEST_CASE("ID 5.1 & 6.1 Simple Game is over, someone wins")
{
 GameLogic* GameData;
 GameData = new SimpleGameMode;
 GameData->rows =3;
 GameData->cols=3;
 //GameData = new SimpleGameMode;
 GameBoard* GameScreen = new GameBoard;
 PlayerLogic* player1Data = new PlayerLogic;
 PlayerLogic* player2Data = new PlayerLogic;
 //set gamemode
 GameData->GameMode = 1;
 //set piece to s
 player1Data->SelectedPiece = 1;
 //create the groups
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);
 Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);
 //create the button pressed
 GameScreen->BoardButton = new Fl_Toggle_Button(184, 226 ,40, 40, "");
 //run the callback for the button
 GameBoardButtonCBdata* GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 1, GameData, 3, 3, Player1Controls, Player2Controls};
 GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 //check the vector that holds all the played areas
 player2Data->SelectedPiece = 0;
 GameScreen->BoardButton = new Fl_Toggle_Button(184, 184 ,40, 40, "");
 GameBoardCBdata = nullptr;
 GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 2, GameData, 3, 3, Player1Controls, Player2Controls};
 GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 player1Data->SelectedPiece = 1;
 GameScreen->BoardButton = new Fl_Toggle_Button(184, 142 ,40, 40, "");
 GameBoardCBdata = nullptr;
 GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 1, GameData, 3, 3, Player1Controls, Player2Controls};
 GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 GameData->CheckOutcome();

 REQUIRE(GameData->EndGame == true);
}



TEST_CASE("ID 5.2 Board is filled & 5.3 Declare a draw in simple game")
{
 GameLogic* GameData;
 GameData = new SimpleGameMode;
 //set gameboard size
 GameData->rows =3;
 GameData->cols=3;
 //Add pieces to game board
 for(int i =0; i < 3; i++)
 {
    for(int j=0; j < 3; j++)
    {
            GameData->addMovetoList(i, j, 1, NULL);
    }
 }
 PlayerLogic* player1Data = new PlayerLogic;
 PlayerLogic* player2Data = new PlayerLogic;
 //since the gameboard is filled with s, there should be no found sequences, which means its a draw
 GameData->SequenceFinder(3, 3, player1Data, player2Data);
 REQUIRE(GameData->FoundSequences.size() == 0);
 //check if the game ends
 GameData->CheckOutcome();
 REQUIRE(GameData->EndGame == true);


}



//6.1 AC is with 4.1



TEST_CASE("ID 7.2 Declare the winner")
{
 GameLogic* GameData;
 GameData = new GeneralGameMode;
 //GameData = new SimpleGameMode;
 GameData->rows =3;
 GameData->cols=3;
 GameBoard* GameScreen = new GameBoard;
 PlayerLogic* player1Data = new PlayerLogic;
 PlayerLogic* player2Data = new PlayerLogic;
 //set gamemode
 GameData->GameMode = 1;
 //set piece to s
 player1Data->SelectedPiece = 1;
 //create the groups
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);
 Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);
 //create the button pressed
 //fill up board, but not filling in the 3rd col
 for(int i =0; i < 2; i++)
 {
    for(int j=0; j < 3; j++)
    {

            GameData->addMovetoList(i, j, 1, NULL);
    }
 }
 //form sos sequence
 GameScreen->BoardButton = new Fl_Toggle_Button(184, 226 ,40, 40, "");
 //run the callback for the button
 GameBoardButtonCBdata* GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 1, GameData, 3, 3, Player1Controls, Player2Controls};
 GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 //check the vector that holds all the played areas
 player2Data->SelectedPiece = 0;
 GameScreen->BoardButton = new Fl_Toggle_Button(184, 184 ,40, 40, "");
 GameBoardCBdata = nullptr;
 GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 2, GameData, 3, 3, Player1Controls, Player2Controls};
 GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 player1Data->SelectedPiece = 1;
 GameScreen->BoardButton = new Fl_Toggle_Button(184, 142 ,40, 40, "");
 GameBoardCBdata = nullptr;
 GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 1, GameData, 3, 3, Player1Controls, Player2Controls};
 GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 //GameData->CheckOutcome();
 REQUIRE(GameData->EndGame == true);
 REQUIRE(player1Data->points == 1);
 REQUIRE(player2Data->points == 0);
}





TEST_CASE("ID 7.1 & 7.3 Declare a draw in general game") //Test if the filled up board ends the game and the game is a draw
{
 GameLogic* GameData;
 GameData = new GeneralGameMode;
 //set gameboard size
 GameData->rows =3;
 GameData->cols=3;
 //Add pieces to game board
 for(int i =0; i < 3; i++)
 {
    for(int j=0; j < 3; j++)
    {
            GameData->addMovetoList(i, j, 1, NULL);
    }
 }
 PlayerLogic* player1Data = new PlayerLogic;
 PlayerLogic* player2Data = new PlayerLogic;
 //since the gameboard is filled with s, there should be no found sequences, which means its a draw
 GameData->SequenceFinder(3, 3, player1Data, player2Data);
 REQUIRE(GameData->FoundSequences.size() == 0);
 //check if the game ends
 GameData->CheckOutcome();
 REQUIRE(GameData->EndGame == true);
 REQUIRE(player1Data->points == 0);
 REQUIRE(player2Data->points == 0);

}


TEST_CASE("8.1 & 8.2 CPU player is compitent")
{
 GameLogic* GameData;
 GameData = new SimpleGameMode;
 //GameData = new SimpleGameMode;
 GameData->rows =3;
 GameData->cols=3;
 GameBoard* GameScreen = new GameBoard;
 PlayerLogic* player1Data = new PlayerLogic;
 CPULogic* player2Data = new CPULogic;
 player2Data->CPUplayer = 2;
 GameData->CPUplayernum =2;
 //set gamemode
 GameData->GameMode = 1;
 //set piece to s
 player1Data->SelectedPiece = 1;
 //create the groups
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);
 Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);

 GameData->CurrentTurn = 1;
 GameData->addMovetoList(0,0,1,NULL);
 GameData->addMovetoList(0,1,0,NULL);
 GameData->CurrentTurn = 2;
 GameData->CPUseek(NULL);
 GameData->CurrentTurn = 1;
 GameData->SequenceFinder(3,3,player1Data,player2Data);
 GameData->CheckOutcome();
 REQUIRE(GameData->EndGame == true);
 REQUIRE(player1Data->points == 0);
 REQUIRE(player2Data->points == 1);

}


struct TempVect
{
        int x;
        int y;
};

TEST_CASE("8.3 CPU v CPU")
{
 GameLogic* GameData;
 GameData = new GeneralGameMode;
 //GameData = new SimpleGameMode;
 GameData->rows =10;
 GameData->cols=10;
 GameBoard* GameScreen = new GameBoard;
 CPULogic* player1Data = new CPULogic;
 player1Data->CPUplayer = 1;
 CPULogic* player2Data = new CPULogic;
 player2Data->CPUplayer = 2;
 GameData->CPUplayernum =3;
 //set gamemode
 GameData->GameMode = 0;
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);
 Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);
 GameScreen->BoardButton = new Fl_Toggle_Button(184, 226 ,40, 40, "");
 while(!GameData->EndGame)
 {
  GameData->CPUseek(NULL);
  GameData->RotatePlayerTurn();
  GameData->CheckOutcome();
 }
 //remove duplicates
 vector<TempVect> SpacesPlayedNoDupes;
 for(int i=0; i < GameData->SpacesPlayed.size(); i++)
 {
   bool isDupe = false;
   for(int j=0; j < SpacesPlayedNoDupes.size(); j++)
   {
     if(GameData->SpacesPlayed[i].x == SpacesPlayedNoDupes[j].x && GameData->SpacesPlayed[i].y == SpacesPlayedNoDupes[j].y)
     {
        isDupe = True;
     }
   }
   if(!isDupe)
   {
      TempVect tempCont;
      tempCont.x = GameData->SpacesPlayed[i].x;
      tempCont.y = GameData->SpacesPlayed[i].y;
      SpacesPlayedNoDupes.push_back(tempCont);
   }
 }

 REQUIRE(SpacesPlayedNoDupes.size() == 100);

}
