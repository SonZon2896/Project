#include "../Main/MainMenuManager.h"

void MainMenuManager::StartMenu()
{
    MainMenu::MakeWindow(500, 500);
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

void MainMenuManager::SetWidgets()
{
    Fl_Button* t = MainMenu::MakeButton(150, 150, 200, 200, "Start Game");
    auto lambda = [](Fl_Widget *w) {MainMenuManager::StartGame();};
    t->callback(lambda);
}
