#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Graphic/FLTKgraphic.h"
// #include "../Weapons/weapons.h"

// Variables ==============================================================================

std::vector<Road> roads{{{0., 0.}, {100., 100.}, {200., 100.}, Fridge::pos},
                        {{50., 0.}, {50., 100.}, {50., 400.}, Fridge::pos},
                        {{0., 50.}, {300., 50.}, {300., 300.}, Fridge::pos}
                        };
Wave wave;
size_t num_of_wave;
Fl_Button* btn_start_wave;
Cockroach cockr{roads[0]};
GraphicCockr* gcockr;

// Functions ==============================================================================

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

void StartWave(Fl_Widget* w)
{
    wave.StartWave();
    Graphic::ShowCockroaches();
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
    gcockr = Graphic::MakeCockr(&cockr);

    MakeWave();
}

void GameManager::FixedUpdate()
{
    ++cockr.pos.x;
    std::cout << "Fixed Update" << std::endl;
    if (wave.Is_Started())
    {
        wave.MoveWave(time::fixed);
        if (wave.GetSurvived() <= 0)
        {
            wave.EndWave();
            MakeWave();
        }
    }
}

void GameManager::Update()
{
    std::cout << "Update " << time::DeltaTime() << std::endl;
    //FRONTEND

    //all interface

    //button to start wave

    //timer to start wave
}