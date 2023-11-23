#include "Headers/heads.h"
#include "Main/Waves.h"

int main()
{
    std::vector<Point> road1{{0., 0.}, {0., 5.}, {5., 5.,}};
    std::vector<Point> road2{{5., 0.}, {5., 5.}, {10., 5.,}};
    std::vector<Point> road3{{10., 0.}, {10., 5.}, {15., 5.,}};
    std::vector<std::vector<Point>> roads{road1, road2, road3};
    Wave wave(roads, 10, 1., 100., 0.5);
    wave.StartWave();
    for (; true; )
    {
        wave.MoveWave(1.);
        if (wave.GetSurvived() <= 0)
            return 0;
    }
    return 1;
}