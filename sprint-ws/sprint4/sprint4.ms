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
Player wants to play with computer component
T}	1	3
.TE
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
.TE
.NH 1
Sumamry of Source Code
.LP
.TS
box, center;
cb | cb | cb
c | c | c.
Source Code file name   Production or testcode? # of lines
main.cpp        pro     16
_
screen_def.hpp  pro     133
_
screen_def.cpp  pro     498
_
game_logic.hpp  pro     138
_
game_logic.cpp  pro     1177
_
unit_tests.cpp  test    323
_
        total   745     
.TE

