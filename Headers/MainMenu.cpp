#include "MainMenu.h"


void MainMenu::MakeWindow(int w, int h)
{
    window = new Fl_Window(w, h);
    window->show();
    Background *bg = new Background("./PNG/main_menu.png");
    window->add(bg);
    Fl_PNG_Image *ico = new Fl_PNG_Image("./PNG/cockroach_px.png");
    window->icon(ico);
    window->default_icon(ico);
}

void MainMenu::Show(){
    window->show();
}

void MainMenu::Hide(){
    window->hide();
}


GraphicButton *MainMenu::MakeButton(int x, int y, int w, int h, const char *label)
{
    GraphicButton *btn = new GraphicButton(x, y, w, h, label);
    window->add(btn);
    return btn;
}
