#include "Updates.h"

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

void GameManager::FixedUpdate()
{
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
    Time::Update();
    
    //FRONTEND

    //all interface

    //button to start wave

    //timer to start wave
}