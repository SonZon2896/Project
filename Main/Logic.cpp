#include <iostream>

#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Graphic/FLTKgraphic.h"
#include "../Weapons/weapons.h"
#include "../events/events.h"

// Variables ==============================================================================

Point Fridge::pos{250, 210};
double Fridge::health{1000.};
std::vector<Road> roads{{{100., 365.}, {250., 350.}, Fridge::pos},
                        {{100., 630.}, {260., 600.}, {250., 350.}, Fridge::pos},
                        {{670., 545.}, {550., 525.}, {550., 350.}, {250., 350.}, Fridge::pos}
                        };
Wave wave;
size_t num_of_wave;
Fl_Button* btn_start_wave;
Text* output;
Text* survived;
Text* fridge_hp;

// Functions ==============================================================================

void MakeWave()
{
    if (wave.Is_Started())
        throw std::runtime_error("Making wave, when it started");

    ++num_of_wave;

    wave.num = 3;
    wave.health = 100.;
    wave.speed = 25.;
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
    output = Graphic::MakeText(400, 0);
    survived = Graphic::MakeText(500, 0);
    fridge_hp = Graphic::MakeText(180, 100);

    MakeWave();
}

void GameManager::FixedUpdate()
{
    // std::cout << "Fixed Update" << std::endl;
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
    if (wave.Is_Started() && output->str != Event::Evil_Woman(wave.GetRunning()))
        output->str = Event::Evil_Woman(wave.GetRunning());
    survived->str = std::to_string(wave.GetSurvived());
    fridge_hp->str = std::to_string((int)Fridge::health);
    //FRONTEND

    //all interface

    //button to start wave

    //timer to start wave
}