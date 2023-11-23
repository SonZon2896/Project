#include "Waves.h"

Wave::Wave(const std::vector<std::vector<Point>>& roads, size_t num, double speed, double health, double interval)
    : roads{roads}, num{num}, speed{speed}, health{health}, interval{interval}
{
    cockroaches.reserve(roads.size() * num);
}

void Wave::StartWave()
{
    for (size_t i = 0; i < num; ++i)
        for (size_t i = 0; i < roads.size(); ++i)
            cockroaches.push_back(Cockroach(roads[i], speed, health));
    survived = cockroaches.size();
}

void Wave::MoveWave(double time)
{
    time_from_start += time;
    active_cockr = time / interval + 1;
    if (active_cockr > cockroaches.size())
        active_cockr = cockroaches.size();
    for (size_t i = 0; i < active_cockr; ++i)
    {
        if (cockroaches[i].is_death)
            continue;
        if (cockroaches[i].health <= 0)
        {
            cockroaches[i].is_death = true;
            --survived;
            continue;
        }
        cockroaches[i].Move(time);
    }
}