.ce
.LG
.B "Project sprint #1"
.ce
John Chirpich
Repo Link: 
.UL "https://github.com/johniscool1/cs-449-project" 
.NH I
User Stories
.LP
.TS
box;
cb | cb | cb | cb | cb
c | c | c | c | c.
ID	User Story Nam 	                      User Stor Desc.                    	Priority	Est Effort (hrs)
_
1	Choose A board size	T{
As a player, I want the board to be corectly made given the dimesions so that I can play the game with the correct dimensions 
T}	1	1
_
2	T{
Choose the game mode of a choosen board	
T}	T{
As a Player, I want to choose what game mode I want to play so that I know the criteria for winning
T}	1	2
_
3	T{
Start a new game of the chosen board size and game mode
T}	T{
As a player, I want to choose the game board size and gamemode so that I can choose how difficult or how long the game might last.
T}	1	2
_
4	T{
Make a move in a simple game
T}	T{
As a player I want to make a move in a simple game so that I can form the sequence SOS and win the game.
T}	2	2
_
5	T{
A simple game is over
T}	T{
As a player, I want to complete the first SOS sequence so that I win
T}	2	3
_
6	T{
Make a move in a general game
T}	T{
.I "AI: "
As a player, I want to make a move during my turn in a general game so that I can strategically place my letters and work towards forming an SOS.
T}	1	2
_
7	T{
A general game is over
T}	T{
.I "AI :"
As a player, I want to know when the general game is over so that I can understand the outcome and celebrate or reflect on my performance.
T}	3	2
.TE
.bp +1
.NH 1.
Acceptance Criteria
.LP
.I "Player refers to a person taking a turn adn the computer taking a turn"
.TS
center, box;
cb | cb | cb | cb
c | c | l | c.
T{
User Story ID
.br
and Name
T}	AC ID	Description of acceptance criterion                                     	Status
_
1. Choose a board size	1.1	T{
AC 1.1 Player creates a valid board
.br
Given the board size x is > 2 and y > 2
.br
When the user inputs x and y size of game board
.br
then show game board with given size
T}	in progress
	_	_	_
	1.2	T{
AC 1.2 Player creates an invalid board
.br
Given the board size x is < 2 and y < 2
.br
When the user inputs x and y size of game board
.br
Then give an error and tell the user to renter a valid size
T}	TODO
_
T{
2.Choose the game mode of a chosen board
T}	2.1	T{
AC 2.1 User presses the simple game mode 
.br
Given a user chooses the simple game mode
.br
When a user presses the simple game mode button
.br
Then initialize the simple game mode
T}	toDo
	_	_	_
	2.2	T{
AC 2.1 User presses the General game button
.br
Given the user chooses to play a general game
.br
When the general game button is pressed
.br
Then initialize the general game mode
T}	toDo
_
T{
3. Start a new game of the chosen board and game size
T}	3.1	T{
AC 3.1 Start a new game
Given the user has chosen a game mode and game size
When the user wants to start the game
Then Initialize the game
And Show the game board
T}	toDo
_
T{
4. Make a move in a simple game
T}	4.1	T{
AC 4.1 Player places a S or O
.br
Given The player make a move
.br
When It is their turn
.br
and an S or O is selected
.br
and the player chooses a valid space
.br
and an SOS sequence is not completed
.br
then place the selected letter in the space
T}	inProgress
	_	_	_
	4.2	T{
AC 4.2 move in an invalid space
.br
Given a Player makes a move 
.br
When they click on a space occupied with a letter

.br
Then tell the user they are trying to play in an invalid space
T}	toDo
_
T{
5. A simple game is over
T}	5.1	T{
AC 5.1 simple game is over	
.br
Given a player places the last letter to complete an SOS sequence
.br
When the player has placed a letter
.br
Then end the game
.br
And announce who won
T}	toDo
.TE
.bp +1
.SH
Ai Generated
.LP
.TS
center, box;
cb | cb | cb | cb
c | c | l | c.
T{
User Story ID
.br
and Name
T}	AC ID	Description of acceptance criterion                                     	Status
_
T{
6. Make a move in a general game
T}	6.1	T{
AC 6.1 Player places a letter ('S' or 'O')
.br
Given it is the player's turn
.br
When they select an empty space on the board
.br
Then place the selected letter in the chosen space
T}	inProgress
	_	_	_
	6.2	T{
AC 6.2 Form an SOS sequence
.br
Given it is the player's turn
.br
When the player successfully completes an SOS sequence
.br
Then the system should recognize and count the sequence
T}	inProgress
	_	_	_
	6.3	T{
AC 6.3 Attempt to place letter in occupied space
.br
Given it is the player's turn
.br
When they try to place a letter in an already occupied space
.br
Then the system should prevent the move and display an error
T}	inProgress
_
7. A general game is over	7.1	T{
AC 7.1 Game ends when board is full
.br
Given the board is full
.br
When no more moves are possible
.br
Then the system should declare the game over
T}	inProgress
	_	_	_
	7.2	T{
AC 7.2 Declare the winner
.br
Given the game is over
.br
When one player has more SOS sequences
.br
Then the system declares that player the winner
T}	inProgress
	_	_	_
	7.3	T{
AC 7.3 Declare a draw
.br
Given the game is over
.br
When both players have the same number of SOS sequences
.br
Then the system declares a draw
T}	inProgress
.TE
.bp +1
.NH 1.
Data Flow diagram
.LP
.SH 
DFD: SOS Game application
.PS
A: box "User Player 1";
move down from last box;
B: box "User Player 2";
move right from A;
move 3;
C: circle rad 1;
circle fillval 0 rad .75 at last circle "SOS game application";
arrow from B .e  to C .sw above "Game input"; 
arrow from A .e to C .w above "game input";
arrow from C .nw to A .ne "UI / gameboard";
arrow from C .s to B .se "UI/ gameboard";
.PE
.SH
DFD: SOS Game application Level 1
.PS
move left 10i;
A: box "Players";
move right from A 2;
B: circle rad .5 "Web Site UI";
move up from B 1;
C: circle rad .5 "Scorboard";
move down from B 1;
D: circle rad .5 "Game logic";
arrow from B .n to C .s "score";
arrow from A .ne to B .nw "Game play request";
arrow from B .sw to A .se "Game play response";
arrow from B .sw to D .nw 
arrow from D .ne to B .se "Game play data I/O"
.PE
.SH 
AI screenshots
.SH
User stories
.LP
.PSPIC -C prompt_user.ps
.PSPIC -C userstory_7.ps
.PSPIC -C userstory6.ps
.SH
Acceptance criteria
.LP
.PSPIC -C promt_acceptance.ps
.PSPIC -C acceptance.ps

