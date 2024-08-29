#include <iostream>
#include <stdlib.h>

#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Round_Button.H"
#include "FL/Fl_Check_Button.H"
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>



// widget that draws a line
class Draw_line : public Fl_Widget {
public:
    Draw_line(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
    }
    void draw() {
        fl_color(FL_BLACK);
        int x1 = x(),       y1 = y();
        int x2 = w()-1, y2 = h();


        fl_line(x1, y1, x2, y2);

    }
};

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




Fl_Double_Window window(700,600);
 Draw_line draw_x(100, 20, 20, 100);
 window.resizable(draw_x);
 Fl_Round_Button *radio_button_1 = new Fl_Round_Button(100, 300, 20, 10, "Radio Button 1");
 Fl_Box *text_box = new Fl_Box(250, 10, 250, 125, "Sample FLTK GUI");
 text_box->labelsize(40);
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

 window.end();
 window.show();
 return Fl::run();
}
