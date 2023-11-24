#include "Headers/heads.h"
#include "Main/Waves.h"
#include <iostream>

void PrintPosCockr()
{
    for (size_t i = 0; i < Cockroach::GetAll().size(); ++i)
    {
        std::cout << "Cockroach " << i << " Position {" << Cockroach::GetAll()[i]->pos.x << ", " << Cockroach::GetAll()[i]->pos.y << "}\n";
    }
    std::cout << "Fridge.health " << Fridge::health << '\n';
    std::cout << std::endl;
}

int main()
{
    std::vector<Point> road1{{0., 0.}, {0., 5.}, {5., 5.,}};
    std::vector<Point> road2{{5., 0.}, {5., 5.}, {10., 5.,}};
    std::vector<Point> road3{{10., 0.}, {10., 5.}, {15., 5.,}};
    std::vector<std::vector<Point>> roads{road1, road2, road3};
    Wave wave(roads, 100, 3, 1., 100., 0.5);
    wave.StartWave();
    std::cout << Cockroach::GetAll().size() << std::endl;
    for (; true; )
    {
        wave.MoveWave(1.);
        PrintPosCockr();
        if (wave.GetSurvived() <= 0)
            return 0;
    }
    return 1;
}