#include "MainMenu.h"


void MainMenu::MakeWindow(int w, int h)
{
    window = new Fl_Window(w, h);
    window->show();
    Background *bg = new Background("./PNG/trap_px.png");
    window->add(bg);

}

void MainMenu::Show(){
    window->show();
}

void MainMenu::Hide(Fl_Widget* w, void *p){
    window->hide();
}


Fl_Button *MainMenu::MakeButton(int x, int y, int w, int h, const char *name)
{
    Fl_Button *btn = new Fl_Button(x, y, w, h, name);
    window->add(btn);
    return btn;
}
