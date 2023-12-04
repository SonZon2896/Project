#include "Headers/heads.h"
#include "Main/Waves.h"
#include "Main/GameManager.h"
#include "Headers/MainMenu.h"
#include "Graphic/FLTKgraphic.h"
#include "Main/MainMenuManager.h"
#include <iostream>

int main()
{
    MainMenuManager::StartMenu();
    Fl::run();   

    GameManager::StartGame();
    Fl::run();
    GameManager::EndGame();
    return 0;
}