.LG
.ce
.B "Project Sprint #4"
.ce
John Chirpich
.LP
Github link: https://github.com/johniscool1/cs-449-project
.NH 1
Demonstration
.LP
Youtube/Panotopo link: Link
.NH 1
User Storie for the Computer Opponent Requirements
.LP
.TS
box, center;
cb | cb | cb | cb | cb
c | c | c | c | c.
ID	User Story	User story Description          	Priority	Est Time
_
8	Computer Component	T{
As a player, I want to choose a computer player so that I can test my skills.
T}	1	3
.TE
.NH 1
User Stories for the Computer Opponent Requirements
.TS
center, box;
cb | cb | cb | cb
c | c | c | c.
T{
User Story and Name
T}	AC ID	Description of AC                               	Status
_
8 Computer Player	8.1	T{
AC 8.1 Computer Player is selected
.br
Given the player selects for a CPU player to play
.br
when they select the CPU as Player 1 or 2 or both
.br
Then Have the cpu play the correct player
T}	done
_
	8.2	T{
AC 8.2 Computer Player is "Compitent"
.br
Given the player is one letter off of an SOS sequence
.br
When its the CPUs turn
.br
Then I want the CPU try to score
T}	done
_
	8.3	T{
AC 8.3 Computer VS Computer
.br
Given The player has selected CPU vs CPU
.br
When The player starts the game
.br
Then the Computer should play its self
T}	done
.TE
.NH 1
Sumamry of Source Code
.LP
.TS
box, center;
cb | cb | cb
c | c | c.
Source Code file name   Production or testcode? # of lines
_
main.cpp	pro	16
_
screen_def.hpp	pro	133
_
screen_def.cpp	pro	498
_
game_logic.hpp	pro	138
_
game_logic.cpp	pro	1177
_
unit_tests.cpp	test	323
_
	total	2285     
.TE
.NH 1
Production Code vs New User stories/Acceptance Criteria
.LP
.TS
center, box;
cb | cb | cb | cb | cb | cb
c | c | c | c | c | c.
User Story ID & name	AC ID	Class Name(s)	method Name(s)	Status	Notes
8. Computer Oponent	8.1-3	T{
GameLogic, CPUlogic (public PlayerLogic)
T}	T{
GameLogic::CPUseek, GameLogic::CheckIfScore, GameLogic::FindButton
T}	Done	
.TE
.NH 1
Tests vs New User stories/Acceptance Criteria
.LP
.TS
center, box;
cb | cb | cb | cb
c | c | c | c.
User Story ID and Name	AC ID	Method	Description(expected I/O)
_
8. Computer oponent	8.1&2	T{
TEST_CASE("8.1 & 8.2 CPU player is compitent")
T}	T{
Creates a board, then has player 1 create an SO, then has the computer player play to see if the Computer player is compitent.
T}
_
	8.3	T{
TEST_CASE("8.3 CPU v CPU")
T}	T{
Creates a gameboard and has the computer play its self in a general game. Then checks if all 100 spaces were played (10x10 board) and then chackes if the computer played on a space already played.
T}
.TE
.NH 1
Present the class diagram of your production code and describe how the class hierarchy in your design deals with the computer opponent requirements
.LP
For class Hierarchy relating too the commputer opponenet, I create a class CPUlogic woth the parent class playerlogic. The Computer player is a player so it is a child of the parent class player logic. Due to all the data needed to use the cpu player being contained in the gamelogic class, all the logic pertaining to the CPU player is in the game logic class.
