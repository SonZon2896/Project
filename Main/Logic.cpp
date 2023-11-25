#include "Updates.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Weapons/weapons.h"

void GameManager::FixedUpdate()
{
    std::cout << "Fixed Update" << std::endl;
    if (wave.Is_Started())
    {
        wave.MoveWave(Time::fixed);
        if (wave.GetSurvived() <= 0)
        {
            wave.EndWave();
            MakeWave();
        }
    }
}

void GameManager::Update()
{
    std::cout << "Update " << Time::DeltaTime() << std::endl;
    //FRONTEND

    //all interface

    //button to start wave

    //timer to start wave
}