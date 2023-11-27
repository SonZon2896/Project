#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Graphic/FLTKgraphic.h"
// #include "../Weapons/weapons.h"

// Variables ==============================================================================

std::vector<Road> roads{{{0., 0.}, {100., 100.}, {200., 100.}, Fridge::pos},
                        {{50., 0.}, {25., 100.}, {50., 400.}, Fridge::pos},
                        {{0., 50.}, {300., 50.}, {400., 200.}, Fridge::pos}
                        };
Wave wave;
size_t num_of_wave;
Fl_Button* btn_start_wave;

// Functions ==============================================================================

void MakeWave()
{
    if (wave.Is_Started())
        throw std::runtime_error("Making wave, when it started");

    ++num_of_wave;

    wave.num = num_of_wave;
    wave.health = 100.;
    wave.speed = 100.;
    wave.interval = 0.5;
}

void StartWave(Fl_Widget* w)
{
    if (!wave.Is_Started())
    {
        wave.StartWave();
        Graphic::ShowCockroaches();
    }
}

// Main ===================================================================================

void GameManager::Start()
{
    wave = Wave(roads);
    num_of_wave = 0;
    Graphic::MakeWindow();
    Graphic::ShowRoads(roads);
    btn_start_wave = Graphic::MakeButton(200, 0, 100, 50, "start wave");
    btn_start_wave->callback(StartWave);

    MakeWave();
}

void GameManager::FixedUpdate()
{
    std::cout << "Fixed Update" << std::endl;
    if (wave.Is_Started())
    {
        wave.MoveWave(time::fixed);
        if (wave.GetSurvived() <= 0)
        {
            wave.EndWave();
            Graphic::ClearCockroaches();
            MakeWave();
        }
    }
    if (Fridge::health <= 0)
    {
        // Event::EndGame();
    }
}

void GameManager::Update()
{
    // std::cout << "Update " << time::DeltaTime() << std::endl;
    //FRONTEND

    //all interface

    //button to start wave

    //timer to start wave
}