#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Graphic/FLTKgraphic.h"
#include "../Weapons/weapons.h"
#include "../events/events.h"

// Variables ==============================================================================

std::vector<Road> roads{{{0., 0.}, {100., 100.}, {200., 100.}, Fridge::pos},
                        {{50., 0.}, {25., 100.}, {50., 400.}, Fridge::pos},
                        {{0., 50.}, {300., 50.}, {400., 200.}, Fridge::pos}
                        };
Wave wave;
size_t num_of_wave;
Fl_Button* btn_start_wave;
Text* new_text;

// Functions ==============================================================================

void MakeWave()
{
    if (wave.Is_Started())
        throw std::runtime_error("Making wave, when it started");

    ++num_of_wave;

    wave.num = num_of_wave + 8;
    wave.health = 100.;
    wave.speed = 100. + num_of_wave * 10;
    wave.interval = 0.5 - (0.5 - 0.4 / ((num_of_wave + 10) / 5));
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
    new_text = Graphic::MakeText(400, 0);
    new_text->str = "Pizdec rebyata";

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
    //FRONTEND

    //all interface
    new_text->str = Event::Evil_Woman();

    //button to start wave

    //timer to start wave
}