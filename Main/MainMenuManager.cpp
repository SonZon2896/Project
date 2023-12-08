#include "../Main/MainMenuManager.h"

#define WINDOW_SIZE_X 500
#define WINDOW_SIZE_Y 500

void MainMenuManager::StartMenu()
{
    MainMenu::MakeWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    SetWidgets();
    MainMenu::Show();
}

void MainMenuManager::StartGame()
{
    MainMenu::Hide();
    GameManager::StartGame();
}

void MainMenuManager::EndMenu()
{
    // MainMenu::Hide();
}

bool MainMenuManager::GameStarted()
{
    return game_started;
}

#define BTN_START_SIZE_X 100
#define BTN_START_SIZE_Y 100

void MainMenuManager::SetWidgets()
{
    Fl_Button* t = MainMenu::MakeButton(WINDOW_SIZE_X / 2 - BTN_START_SIZE_X / 2, WINDOW_SIZE_Y / 2 - BTN_START_SIZE_Y / 2, BTN_START_SIZE_X, BTN_START_SIZE_Y);
    t->image(new Fl_PNG_Image("PNG/button_start_game.png"));
    t->box(FL_NO_BOX);
    auto lambda = [](Fl_Widget *w) {MainMenuManager::StartGame();};
    t->callback(lambda);
}
