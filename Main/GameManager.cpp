#include "GameManager.h"

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

void GameManager::StartGame()
{
    if (is_started)
        throw std::runtime_error("Start Game, which stared");

    is_started = true;
    Start();

    fix_thr = std::thread(StartFixedUpdate);
    upd_thr = std::thread(StartUpdate);
}

void GameManager::StartFixedUpdate()
{
    for (; is_started; )
    {
        std::thread(FixedUpdate).detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(int(Time::fixed * 100)));
    }
}

void GameManager::StartUpdate()
{
    for (; is_started; )
    {
        Time::Update();
        std::thread(Update).join();
    }
}

void GameManager::EndGame()
{
    if (!is_started)
        throw std::runtime_error("End Game, which not started");

    is_started = false;

    fix_thr.join();
    upd_thr.join();
    fix_thr.~thread();
    upd_thr.~thread();

}