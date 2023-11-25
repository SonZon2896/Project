#include "Headers/heads.h"
#include "Main/Waves.h"
#include "Main/Updates.h"
#include <iostream>

void PrintPosCockr()
{
    for (size_t i = 0; i < Cockroach::GetAll().size(); ++i)
    {
        std::cout << "Cockroach " << i << " Position {" << Cockroach::GetAll()[i]->pos.x << ", " << Cockroach::GetAll()[i]->pos.y << "}, health = " << Cockroach::GetAll()[i]->health << std::endl;
    }
    std::cout << "Fridge.health " << Fridge::health << '\n';
    std::cout << std::endl;
}

int main()
{
    // Wave wave(roads, 1, 0.5, 1., 100.);
    // wave.StartWave();
    // std::cout << Cockroach::GetAll().size() << std::endl;
    // for (; true; )
    // {
    //     Cockroach::GetAll()[0]->health -= 20;
    //     wave.MoveWave(1.);
    //     PrintPosCockr();
    //     if (wave.GetSurvived() <= 0)
    //     {
    //         wave.EndWave();
    //         break;
    //     }
    // }
    // PrintPosCockr();
    // return 0;



    // Time::Update();
    // for (size_t i = 0; i < 100000; ++i) {}
    // Time::Update();
    // std::cout << Time::DeltaTime() << std::endl;

    // for (size_t i = 0; i < 10000000; ++i) {}
    // Time::Update();
    // std::cout << Time::DeltaTime() << std::endl;
    // Time::Update();
    // std::cout << Time::DeltaTime() << std::endl;


    GameManager::StartGame();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    GameManager::EndGame();
    std::cout << "EndGame" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
}