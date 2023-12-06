#include "Waves.h"

Wave::Wave(const std::vector<Road> &roads)
    : roads{roads}
{
}

void Wave::StartWave()
{
    cockroaches.reserve(roads.size() * num);
    // revive old cockroaches
    for (auto cockr : cockroaches)
        cockr->Revive(prototype);
    // add new cockroaches
    for (size_t i = cockroaches.size() / roads.size(); i < num; ++i)
        for (size_t j = 0; j < roads.size(); ++j)
            cockroaches.push_back(new Cockroach(roads[j], prototype));

    survived = cockroaches.size();
    time_from_start = 0.;
    is_started = true;
}

void Wave::MoveWave(double time)
{
    time_from_start += time;
    active_cockr = time_from_start / interval + 1;
    if (active_cockr > cockroaches.size())
        active_cockr = cockroaches.size();
    for (size_t i = 0; i < active_cockr; ++i)
    {
        if (cockroaches[i]->is_death)
            continue;
        if (cockroaches[i]->health <= 0)
        {
            cockroaches[i]->is_death = true;
            --survived;
            continue;
        }
        if (cockroaches[i]->Move(time))
        {
            Fridge::health -= cockroaches[i]->damage;
            cockroaches[i]->pos = {-1000., -1000};
            cockroaches[i]->is_death = true;
            --survived;
        }
        cockroaches[i]->CheckTrigger();
    }
}

void Wave::EndWave()
{
    survived = 0;
    is_started = false;
}