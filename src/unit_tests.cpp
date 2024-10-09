#define CATCH_CONFIG_MAIN
#include "test_lib/catch_amalgamated.hpp"
#include "screen_def.hpp"
#include "game_logic.hpp"

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
 REQUIRE(Counter_val == 3);


 delete UserInputX;
 delete UserInputY;
 delete CounterCheck;

}


/*
 *
 *  AC 2
 *
 */


TEST_CASE("ID 2.1 User presses Simple Gamemode")
{
 GameLogic* GameData = new GameLogic;
 Fl_Round_Button* SimpleGameModeRB = new Fl_Round_Button(200, 300, 70, 20, "Simple Gamemode");
 SimpleGameModeRB->type(FL_RADIO_BUTTON);
 Fl_Round_Button* GeneralGameModeRB = new Fl_Round_Button(410, 300, 70, 20, "General Gamemode");
 GeneralGameModeRB->type(FL_RADIO_BUTTON);
 //user chooses simple gamemode
 SimpleGameModeRB->value(1);
 GameData->setGameMode(SimpleGameModeRB->value());
 REQUIRE(GameData->GameMode == 1);

 delete GameData;
 delete SimpleGameModeRB;
 delete GeneralGameModeRB;
}

TEST_CASE("ID 2.2 User presses General Gamemode")
{
 GameLogic* GameData = new GameLogic;
 Fl_Round_Button* SimpleGameModeRB = new Fl_Round_Button(200, 300, 70, 20, "Simple Gamemode");
 SimpleGameModeRB->type(FL_RADIO_BUTTON);

 Fl_Round_Button* GeneralGameModeRB = new Fl_Round_Button(410, 300, 70, 20, "General Gamemode");
 GeneralGameModeRB->type(FL_RADIO_BUTTON);
 //user chooses General gamemode
 GeneralGameModeRB->value(1);
 GameData->setGameMode(SimpleGameModeRB->value());
 REQUIRE(GameData->GameMode == 0);
 delete GameData;
 delete SimpleGameModeRB;
 delete GeneralGameModeRB;
}


TEST_CASE("ID 3.1")
{
 GameLogic* GameData = new GameLogic;
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
 GameLogic* GameData = new GameLogic;
 GameBoard* GameScreen = new GameBoard;
 Player1Logic* player1Data = new Player1Logic;
 Player2Logic* player2Data = new Player2Logic;
 //set piece to s
 player1Data->SelectedPiece = 1;
 //create the groups
 Fl_Group* Player1Controls = new Fl_Group(10, 100, 50, 100);
Fl_Group* Player2Controls = new Fl_Group(10, 100, 50, 100);
 //create the button pressed
 GameScreen->BoardButton = new Fl_Toggle_Button(226, 226 ,40, 40, "");
 //run the callback for the button
 GameBoardButtonCBdata* GameBoardCBdata = new GameBoardButtonCBdata{GameScreen->BoardButton, player1Data, player2Data, 1, GameData, 3, 3, Player1Controls, Player2Controls};
 GameScreen->GameBoardButtonPressedCB(NULL, GameBoardCBdata);
 //check the vector that holds all the played areas
 REQUIRE(GameData->SpacesPlayed[0].piece == 1);
 REQUIRE(GameData->SpacesPlayed[0].x == 3);
 REQUIRE(GameData->SpacesPlayed[0].y == 3);
}
