class PlayerLogic
{
public:
 int SelectedPiece = 1; // s=1, o=0. Default selections is S so set to 1
 int points =0;
 void ChangeSelectedPiece(int Selection); //change what piece the player has selected on the gameboard
 void addPoint();

};

//subclasses to store player specific data
class Player1Logic : public PlayerLogic{
public:
 void DrawPlayer1Selection();
 //Fl_Group* Player1Controls;
};
class Player2Logic : public PlayerLogic{
public:
 void DrawPlayer2Selection();
 //Fl_Group* Player2Controls;
};
