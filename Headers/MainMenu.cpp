#include "MainMenu.h"

#define PATH_IMAGE_MAIN_MENU "./PNG/main_menu.png"
#define PATH_IMAGE_DEFAULT_COCKROACH "./PNG/cockroach_px.png"

void MainMenu::MakeWindow(int w, int h)
{
    window = new Fl_Window(w, h);
    window->show();
    Background *bg = new Background(PATH_IMAGE_MAIN_MENU);
    window->add(bg);
    Fl_PNG_Image *ico = new Fl_PNG_Image(PATH_IMAGE_DEFAULT_COCKROACH);
    window->icon(ico);
    window->default_icon(ico);
}

void MainMenu::Show(){
    window->show();
}

void MainMenu::Hide(){
    window->hide();
}


Fl_Button *MainMenu::MakeButton(int x, int y, int w, int h, const char *label)
{
    Fl_Button *btn = new Fl_Button(x, y, w, h, label);
    window->add(btn);
    return btn;
}
