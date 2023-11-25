#include "Updates.h"

std::vector<Road> settings_roads{{{0., 0.}, {0., 5.}, {5., 5.,}},
                        {{5., 0.}, {5., 5.}, {10., 5.,}},
                        {{10., 0.}, {10., 5.}, {15., 5.,}}};


double Time::DeltaTime()
{
    std::chrono::duration<double> delta = now - prev;
    return delta.count();
}

void Time::Update()
{
    prev = now;
    now = std::chrono::system_clock::now();
}

void GameManager::MakeWave()
{
    if (wave.Is_Started())
        throw std::runtime_error("Making wave, when it started");

    ++num_of_wave;

    wave.num = 3.;
    wave.health = 100.;
    wave.speed = 1.;
    wave.interval = 1.;
}

void GameManager::StartGame()
{
    if (is_started)
        throw std::runtime_error("Start Game, which stared");

    is_started = true;
    roads = settings_roads;
    wave = Wave(roads);
    num_of_wave = 0;

    MakeWave();
    fix_thr = std::thread(FixedUpdate);
    upd_thr = std::thread(Update);
    std::thread(StartFixedUpdate).detach();
    std::thread(StartUpdate).detach();
}

void GameManager::StartFixedUpdate()
{
    for (; true; )
    {
        fix_thr.detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(int(Time::fixed * 100)));
    }
}

void GameManager::StartUpdate()
{
    for (; true; )
    {
        Time::Update();
        upd_thr.join();
    }
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
    std::cout << "Update" << std::endl;
    //FRONTEND

    //all interface

    //button to start wave

    //timer to start wave
}

void GameManager::EndGame()
{
    if (!is_started)
        throw std::runtime_error("End Game, which not started");

    fix_thr.~thread();
    upd_thr.~thread();

    is_started = false;
}