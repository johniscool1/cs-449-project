#include <iostream>
#include <stdlib.h>

#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Round_Button.H"
#include "FL/Fl_Check_Button.H"

void cb_radio_button_1_clicked(Fl_Widget*, void *) 
{
 printf("Radio Button 1 Clicked\n");
}

void cb_radio_button_2_clicked(Fl_Widget*, void *) 
{
 printf("Radio Button 2 Clicked\n");
}

void cb_checkbox_1_checked(Fl_Widget*, void *v) 
{
 Fl_Round_Button *checkbox_1 = (Fl_Round_Button*)v;
 if(checkbox_1->value() == 1)
 {
  printf("Check box 1 checked\n");
 } else 
 {
  printf("Check box 1 unchecked\n");
 }
}
int main() 
{

 static int window_x = 750;
 static int window_y = 500;
 Fl_Window *window = new Fl_Window(window_x, window_y);
 Fl_Box *text_box = new Fl_Box(250, 10, 250, 125, "Sample FLTK GUI");
 text_box->labelsize(40);

 Fl_Round_Button *radio_button_1 = new Fl_Round_Button(100, 300, 20, 10, "Radio Button 1");
 radio_button_1->type(FL_RADIO_BUTTON);
 radio_button_1->labelsize(20);
 radio_button_1->callback(cb_radio_button_1_clicked);

 Fl_Round_Button *radio_button_2 = new Fl_Round_Button(100, 340, 20, 10, "Radio Button 2");
 radio_button_2->type(FL_RADIO_BUTTON);
 radio_button_2->labelsize(20);
 radio_button_2->callback(cb_radio_button_2_clicked);

 Fl_Check_Button *check_button_1 = new Fl_Check_Button(350, 300, 20, 10, "Check Box 1");
 check_button_1->labelsize(20);
 check_button_1->callback(cb_checkbox_1_checked, check_button_1);

 window->end();
 window->show();
 return Fl::run();
}
