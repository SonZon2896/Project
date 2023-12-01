#include <iostream>

#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Graphic/FLTKgraphic.h"
#include "../Weapons/weapons.h"
#include "../events/events.h"

// Variables ==============================================================================

Point Fridge::pos{250, 210};
double Fridge::health{100.};
double Event::money{100.};
double Event::money_speed{100.};
const bool Mark_Lox = true; // 1 december
std::vector<Road> roads{{{100., 365.}, {250., 350.}, Fridge::pos},
                        {{100., 630.}, {260., 600.}, {250., 350.}, Fridge::pos},
                        {{670., 545.}, {550., 525.}, {550., 350.}, {250., 350.}, Fridge::pos}};
Wave wave;
size_t num_of_wave;
Fl_Button *btn_start_wave;
Text *events;
Text *survived;
Text *fridge_hp;
Text *stipubles;
Text *timer_text;

double timer = 0.;
double timer_to_start_wave = 10.;

// Functions ==============================================================================

void MakeWave()
{
    if (wave.Is_Started())
        throw std::runtime_error("Making wave, when it started");

    ++num_of_wave;

    wave.num = 3;
    wave.health = 100.;
    wave.speed = 150.;
    wave.interval = 0.1;
}

void StartWave(Fl_Widget *w)
{
    if (!wave.Is_Started())
    {
        wave.StartWave();
        Graphic::ShowCockroaches();
        timer = 0.;
    }
}

// Main ===================================================================================

void GameManager::Start()
{
    wave = Wave(roads);
    num_of_wave = 0;
    Graphic::MakeWindow(1280, 770);
    Graphic::ShowRoads(roads);
    btn_start_wave = Graphic::MakeButton(0, 720, 100, 50, "start wave");
    btn_start_wave->callback(StartWave);
    events = Graphic::MakeText(1000, 720, "output");
    survived = Graphic::MakeText(100, 720, "survived");
    stipubles = Graphic::MakeText(200, 720, "stipubles");
    timer_text = Graphic::MakeText(300, 720, "timer");
    fridge_hp = Graphic::MakeText(125, 50);

    MakeWave();
}

void GameManager::FixedUpdate()
{
    if (wave.Is_Started())
    {
        wave.MoveWave(time::fixed);
        if (wave.GetSurvived() <= 0)
        {
            wave.EndWave();
            Graphic::ClearCockroaches();
            Event::Scholarship();
            MakeWave();
        }
    }
    if (Fridge::health <= 0)
    {
        Graphic::MakeText(590, 335, "WASTED");
        EndGame();
    }
}

void GameManager::Update()
{
    if (!wave.Is_Started() && (timer += time::DeltaTime()) > timer_to_start_wave)
    {
        wave.StartWave();
        Graphic::ShowCockroaches();
        timer = 0.;
    }

    events->output = Event::Evil_Woman(wave.GetRunning());
    survived->output = std::to_string(wave.GetSurvived());
    fridge_hp->output = std::to_string((int)Fridge::health);
    stipubles->output = std::to_string((int)Event::money);
    timer_text->output = std::to_string((int)(timer_to_start_wave - timer + 0.99));
}