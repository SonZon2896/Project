#include "../Main/MainMenuManager.h"
#include "../Headers/MainMenu.h"

void MainMenuManager::StartMenu()
{
    MainMenu::MakeWindow(500, 500);
    SetWidgets();
    MainMenu::Show();
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
    Fl_Button* t = MainMenu::MakeButton(200, 200, 100, 100, "Start Game");
    t->callback(MainMenu::Hide, (void*)nullptr);
}