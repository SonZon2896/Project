#include "Waves.h"

Wave::Wave(const std::vector<std::vector<Point>>& roads, double fridge_health, size_t num, double speed, double health, double interval)
    : roads{roads},  fridge_health{fridge_health}, num{num}, speed{speed}, health{health}, interval{interval}
{
    cockroaches.reserve(roads.size() * num);
}

void Wave::StartWave()
{
    for (size_t i = 0; i < num; ++i)
        for (size_t i = 0; i < roads.size(); ++i)
            cockroaches.emplace_back(roads[i], speed, health);
    survived = cockroaches.size();
}

void Wave::MoveWave(double time)
{
    time_from_start += time;
    active_cockr = time_from_start / interval;
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
        if (cockroaches[i].Move(time))
        {
            cockroaches[i].pos = {-1., -1};
            cockroaches[i].is_death = true;
            --survived;
        }
    }
}