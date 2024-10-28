.LG
.ce
Project Sprint 3
.ce
John Chirpich
.LP
Github link: https://github.com/johniscool1/cs-449-project
.NH 1
Demonstration
.LP
Youtube/Panotopo link: Link
.NH 1
Sumamry of Source Code
.LP
.TS
box, center;
cb | cb | cb
c | c | c.
Source Code file name	Production or testcode?	# of lines
main.cpp	pro	16
_
screen_def.hpp	pro	120
_
screen_def.cpp	pro	431
_
game_logic.hpp	pro	102
_
game_logic.cpp	pro	690
_
unit_tests.cpp	test	323
_
	total	745	
.TE
.NH 1
Production Code vs User stories/Acceptance Criteria
.LP
.TS
center, box;
cb | cb | cb | cb | cb | cb
c | c | c | c | c | c.
User Story ID & name	AC ID	Class Name(s)	method Name(s)	Status	Notes
_
1 Choose a board size	1.1-2	GameBoard	T{
GameBoard::SetBoardDimensions, MMcounter_check
T}	done	T{
Both AC 1,1 & 1.2 Invovle the same classes and methods
T}
_
T{
2. Choose the game mode of a chosen board
T}	2.1-2	GameLogic	T{
GameLogic::setGameMode, playGameButtonCB
T}	done	T{
Both AC 2.1 & 2.2 Invovle the same classes and methods
T}	
_
T{
3. Start a new game of the chosen board and game size
T}	3.1	GameBoard, GameLogic	T{
GameBoard::SetBoardDimensions, GameBoard::DrawButtons, playGameButtonCB, GameLogic::setGameMode
T}	done	
_
T{
4. Make a move in a simple game
T}	4.1	GameBoard, GameLogic	T{
GameBoard::GameBoardButtonPressed (uses data from game logic)
T}	done		
_
	4.2	GameBoard	T{
GameBoard::GameBoardButtonPressed
T}	done	T{
By using toggle buttons, the method deactivates them so that they cant be clicked again
T}
.TE
.TS
center, box;
cb | cb | cb | cb | cb | cb
c | c | c | c | c | c.
User Story ID & name	AC ID	Class Name(s)	method Name(s)	Status	Notes
_
T{
5. A simple game is over
T}	5.1	GameBoard, GameLogic	T{
GameLogic::SequenceFinder, CheckOutcome
T}	done	
	5.2	GameBoard, GameLogic	T{
GameLogic::SequenceFinder, CheckOutcome
T}	done	
_
T{
6. Make a move in a general game
T}	6.1	GameBoard, GameLogic	T{
GameBoard::GameBoardButtonPressed (uses data from game logic)
T}	done	
_
	6.2	GameBoard, GameLogic	T{
GameBoard::GameBoardButtonPressed, GameLogic::SequenceFinder
T}	done	
_
	6.3	GameBoard	T{
GameBoard::GameBoardButtonPressed
T}	done	T{
By using toggle buttons, the method deactivates them so that they cant be clicked again
T}
_
T{
7. A general game is over
T}	7.1-3	GameBoard, GameScreen	T{
GameBoard::SequenceFinder, GameBoardButtonPressed
T}	done	
.TE
.bp +1
.NH 1
Tests vs User stories/Acceptance Criteria
.LP
.I "Class Names Have been left out of the table beucase classes were not used in test code."
.br
Tests 2.1 and 2.2 were ai generated, screenshots are at the end.
.TS
center, box;
cb | cb | cb | cb
c | c | c | c.
User Story ID and Name	AC ID	Method	Description(expected I/O)
_
T{
1 Choose a board size
T}	1.1	T{
TEST_CASE("ID 1.1: Choose Gameboard Size is > 3")
T}	T{
Takes the counters and sets the value like a user whould, and passes it to the Main Menu Counter check that checks if it is valid.
T}
_
	1.2	T{
TEST_CASE("ID 1.2: Choose Gameboard Size is < 3")
T}	T{
Like the last one, it takes the counters and sets one of them to an incorrect value. (due to hoe the counter work, only one of them can be set at a time). If a counter's value is < 3, an error will pop up and after the user acknoledges, the counter is set to 3. NOTE: Due to the function calling the popup, this test will display that popup, but you just have to press escape or close the popup
T}
_
T{
2. Choose the game mode of a chosen board
T}	2.1	T{
TEST_CASE("ID 2.1 User presses Simple Gamemode")
T}	T{
Simulates the radio buttons a user uses on the main menu to select a gamemode. Then Uses a class setter to set the gamemode. I am unable to use the whole function that contians this setter becuase it also creates the window for the gameboard. Altough I created both buttons, the code only checks if the simple GM one is checked or not.
T}
	2.2	T{
TEST_CASE("ID 2.2 User presses General Gamemode")
T}	T{
Same as the last one but checks for the general gamemode.
T}
T{
3. Start a new game of the chosen board and game size
T}	3.1	T{
This one combines both of the two previous tests, as any further functions hevailiy involve the GUI and I wanted to try to make these as automated as possible.
T}
.TE

.TS
center, box;
cb | cb | cb | cb
c | c | c | c.
User Story ID and Name	AC ID	Method	Description(expected I/O)
_
4. Make a move in a simple game
T}	4.1	T{
TEST_CASE("ID 4.1 & 6.1 Player places a S or O")
T}	T{
This test revolves around the "GameBoardButtonPressed" callback which runs when a user presses a button on the gameboard. First we setup all the data we need for the CB, create a button, set the piece to S and then run the callback. WE then check the GameLogic class, which has a vector that stores where the palyers has played, and checks if the piece was registered.
T}
_
5. A simple game is over	5.1	T{
TEST_CASE("ID 5.1 & 6.1 Simple Game is over, someone wins")
T}	T{
Creates a gameboard and creates a sos sequence and checks if the game ends and player 1 won.
T}
_
	5.2 & 5.3	T{
TEST_CASE("ID 5.2 Board is filled & 5.3 Declare a draw in simple game")
T}	T{
Fills up the board with all s, creating a filled board and a tie. Check if the game ended and both players points are 0
T}
_

6. Make a move in a general game	6.1
T{
TEST_CASE("ID 4.1 & 6.1 Player places a S or O"
T}	T{
Becuase scoring and sequence finding has not been fully implemented, this AC shares a test with 4.1 becuase the gameplay is the same in both gamemodes until a sequence is formed.
T}
	6.2	T{
TEST_CASE("ID 5.1 & 6.1 Simple Game is over, someone wins")
T}	T{
If the a sequence is formed, than they win, so this test accomplishes both AC.
T}
_
7. A general game is over	7.1 & 7.3	T{
TEST_CASE("ID 7.1 Board is filled & 7.3 Declare a draw in general game")
T}	T{
Fills up the board with all s, creating a filled board and a tie. Check if the game ended and both players points are 0
T}
	7.2	T{
TEST_CASE("ID 7.2 Declare the winner")
T}	T{
Fills up board with S execpt for the 3rd column, were the an sos sequence is scored. WE then cehck if the sequence was found and if it was scored.
T}
.TE
.bp +1
.NH 1
.ps 12
Describe how the class hierarchy in your design deals with the common and different requirements of
the Simple Game and the General Game?
.PP
.ps 12
.vs 1.5m
My program currently only uses class hierarchy in one place and that is with the Parent class GameLogic with 2 children: SimpleGamemode and GeneralGamemode. Since the gameplay is the same between the 2 gamemodes until someone scores, each of the parent function holds all the data needed to run the game such as what spaces ahve been played and whos turn it is. It also holds the score, but that is only really important for the general gamemode. The differences between the two gamemodes come when someone forms a sequence. In the simple Gamemode, the game ends, and for the General game, the game continues and the player gets another turn.

	In order to accomplish this, the GameLogic class has a virtual function called "CheckOutCome". The function is then defined in the children classes GeneralGamemode and Simeplegamemode. For GeneralGamemode, it checks if the boar dis filled, and for the simple gamemode, it checks if there was a sequence from SequenceFinder() or if the board has been filled. Having this virtual fucntion allows me to call the CheckOutcome in the GameBoardButtonPressedCB callback and not have to check what the gamemode is and rewriting it to check for the gamemode. 
.PSPIC img/prompt.ps
.PSPIC img/resp1.ps
.PSPIC img/promt3.ps
.PSPIC img/res2.ps
