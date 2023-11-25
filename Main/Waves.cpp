#include "Waves.h"

Wave::Wave(const std::vector<Road>& roads, size_t num, double interval, double speed, double health)
    : roads{roads}, num{num}, interval{interval}, speed{speed}, health{health}
{
    cockroaches.reserve(roads.size() * num);
}

void Wave::StartWave()
{
    for (size_t i = 0; i < num; ++i)
        for (size_t i = 0; i < roads.size(); ++i)
            cockroaches.emplace_back(roads[i], speed, health);
    survived = cockroaches.size();
    time_from_start = 0.;
    is_started = true;
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
            Fridge::health -= cockroaches[i].damage;
            cockroaches[i].pos = {-1., -1};
            cockroaches[i].is_death = true;
            --survived;
        }
        cockroaches[i].CheckTrigger();
    }
}

void Wave::EndWave()
{
    cockroaches.clear();
    survived = 0;
    is_started = false;
}