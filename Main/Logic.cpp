#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
// #include "../Weapons/weapons.h"


std::vector<Road> roads{{{0., 0.}, {0., 5.}, {5., 5.,}},
                        {{5., 0.}, {5., 5.}, {10., 5.,}},
                        {{10., 0.}, {10., 5.}, {15., 5.,}}};
Wave wave;
size_t num_of_wave;

void MakeWave()
{
    if (wave.Is_Started())
        throw std::runtime_error("Making wave, when it started");

    ++num_of_wave;

    wave.num = 3.;
    wave.health = 100.;
    wave.speed = 1.;
    wave.interval = 1.;
}



void GameManager::Start()
{
    wave = Wave(roads);
    num_of_wave = 0;

    MakeWave();
}

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