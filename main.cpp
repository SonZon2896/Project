#include "Headers/heads.h"
#include "Main/Waves.h"
#include "Main/GameManager.h"
#include "Graphic/FLTKgraphic.h"
#include <iostream>

int main()
{
    GameManager::StartGame();
    Fl::run();
    GameManager::EndGame();
    return 0;
}