#define CATCH_CONFIG_MAIN
#include "test_lib/catch_amalgamated.hpp"
#include "screen_def.hpp"
#include "game_logic.hpp"


bool alert_called = false;
void fl_alert_no_win(const char* msg) {
    alert_called = true;
}

#define fl_alert fl_alert_no_win







//TEST ID 1
TEST_CASE("ID 1: Choose Gameboard Size")
{
 GameBoard* GameScreen;
 Fl_Counter *UserInputX = new Fl_Counter(200 , 200 , 70, 20);
 Fl_Counter *UserInputY = new Fl_Counter(350 , 200 , 70, 20);
 UserInputX->value(3);
 UserInputY->value(2);
 //overide the FLTK alert Function
 MMcounter_checkCBdata* CounterCheck = new MMcounter_checkCBdata{UserInputX};
 MMcounter_check(nullptr, CounterCheck);
 CHECK(alert_called);

 delete UserInputX;
 delete UserInputY;
 delete CounterCheck;

}
