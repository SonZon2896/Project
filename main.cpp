#include "Headers/heads.h"
#include "Main/Waves.h"
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
    Road road1{{0., 0.}, {0., 5.}, {5., 5.,}};
    Road road2{{5., 0.}, {5., 5.}, {10., 5.,}};
    Road road3{{10., 0.}, {10., 5.}, {15., 5.,}};
    std::vector<Road> roads{road1, road2, road3};
    Wave wave(roads, 1, 0.5, 1., 100.);
    wave.StartWave();
    std::cout << Cockroach::GetAll().size() << std::endl;
    for (; true; )
    {
        Cockroach::GetAll()[0]->health -= 20;
        wave.MoveWave(1.);
        PrintPosCockr();
        if (wave.GetSurvived() <= 0)
        {
            wave.EndWave();
            break;
        }
    }
    PrintPosCockr();
    return 0;
}