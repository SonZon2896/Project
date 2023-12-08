#include "GameManager.h"

double time::DeltaTime()
{
    std::chrono::duration<double> delta = now - prev;
    return delta.count();
}

void time::Update()
{
    prev = now;
    now = std::chrono::system_clock::now();
}

void GameManager::StartGame()
{
    if (is_started)
        return;

    is_started = true;
    Start();

    fix_thr = std::thread(StartFixedUpdate);
    time::Update();
    upd_thr = std::thread(StartUpdate);
}

void GameManager::StartFixedUpdate()
{
    for (; is_started;)
    {
        std::thread(FixedUpdate).detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(int(time::fixed * 1000)));
    }
}

void GameManager::StartUpdate()
{
    for (; is_started;)
    {
        time::Update();
        std::thread(Update).join();
    }
}

void GameManager::EndGame()
{
    if (!is_started)
        return;

    is_started = false;

    fix_thr.join();
    upd_thr.join();

    End();
}