#include "Waves.h"
#include "../Headers/heads.h"

// Wave

Wave::Wave()
{
    all_waves.push_back(this);
}

Wave::~Wave()
{
    for (size_t i = 0; i < all_waves.size(); ++i)
        if (all_waves[i] == this)
        {
            all_waves.erase(all_waves.begin() + i);
            break;
        }
}

void Wave::StartAll(size_t num_of_wave)
{
    for (auto wave : all_waves)
        wave->Start(num_of_wave);
}

void Wave::ActionAll(double time)
{
    for (auto wave : all_waves)
        if (wave->IsStarted())
            wave->Action(time);
}

void Wave::EndAll()
{
    for (auto wave : all_waves)
        wave->End();
}

size_t Wave::GetAllRunning()
{
    size_t result = 0;
    for (auto wave : all_waves)
        result += wave->GetRunning();
    return result;
}

size_t Wave::GetAllSurvived()
{
    size_t result = 0;
    for (auto wave : all_waves)
        result += wave->GetSurvived();
    return result;
}

bool Wave::IsAllStarted()
{
    for (auto wave : all_waves)
        if (wave->IsStarted())
            return true;
    return false;
}

// WaveCockroaches

void WaveCockroaches::Start(size_t num_of_wave) 
{
    prototype.health = COCKROACHES_HEALTH + HEALTH_DELTA_MULT * num_of_wave;
    prototype.speed = COCKROACHES_SPEED + sqrt(HEALTH_DELTA_MULT * num_of_wave);
    prototype.damage = COCKROACHES_DAMAGE;
    num = COCKROACHES_AMOUNT_START + COCKROACHES_AMOUNT_WAVE * num_of_wave;
    interval = COCKROACHES_SPAWN_DELAY * (1 - num_of_wave / (num_of_wave + 5));

    cockroaches.reserve(roads.size() * num);
    // revive old cockroaches
    for (auto cockr : cockroaches)
        cockr->Revive(prototype);
    // add new cockroaches
    for (size_t i = cockroaches.size() / roads.size(); i < num; ++i)
        for (size_t j = 0; j < roads.size(); ++j)
            cockroaches.push_back(new Cockroach(roads[j], prototype));

    survived = cockroaches.size();
    active_enemy = 0;
    time_from_start = 0.;
    is_started = true;
}

void WaveCockroaches::Action(double time)
{
    time_from_start += time;
    active_enemy = time_from_start / interval + 1;
    if (active_enemy > cockroaches.size())
        active_enemy = cockroaches.size();
    for (size_t i = 0; i < active_enemy; ++i)
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
            cockroaches[i]->pos = {-1000, -1000};
            cockroaches[i]->is_death = true;
            --survived;
        }
    }
}

void WaveCockroaches::End()
{
    Event::money += WaveCockroaches::num * 100;
    survived = 0;
    is_started = false;
}

// WaveMouses

void WaveMouses::Start(size_t num_of_wave)
{
    prototype.health = MOUSE_HEALTH * (num_of_wave / MOUSE_WAVE_MULTIPLICITY);
    prototype.speed = MOUSE_DAMAGE;
    prototype.damage = MOUSE_SPEED;
    num = (num_of_wave / MOUSE_WAVE_MULTIPLICITY) * 
          ((num_of_wave % MOUSE_WAVE_MULTIPLICITY) == 0);
    interval = MOUSE_INTERVAL;

    mouses.reserve(roads.size() * num);
    // revive old mouses
    for (auto mouse : mouses)
        mouse->Revive(prototype);
    // add new cockroaches
    for (size_t i = mouses.size() / roads.size(); i < num; ++i)
        for (size_t j = 0; j < roads.size(); ++j)
            mouses.push_back(new Mouse(roads[j], prototype));

    survived = mouses.size();
    time_from_start = 0.;
    is_started = true;
}

void WaveMouses::Action(double time)
{
    time_from_start += time;
    active_enemy = time_from_start / interval + 1;
    if (active_enemy > mouses.size())
        active_enemy = mouses.size();
    for (size_t i = 0; i < active_enemy; ++i)
    {
        if (mouses[i]->is_death)
            continue;
        if (mouses[i]->health <= 0)
        {
            mouses[i]->is_death = true;
            --survived;
            continue;
        }
        if (mouses[i]->Move(time))
        {
            Fridge::health -= mouses[i]->damage;
            mouses[i]->pos = {-1000, -1000};
            mouses[i]->is_death = true;
            --survived;
        }
    }
}

void WaveMouses::End()
{
    survived = 0;
    is_started = false;
}

// WaveRadCockroaches

void WaveRadCockroaches::Start(size_t num_of_wave) 
{
    prototype.health = RAD_COCKROACHES_HEALTH + HEALTH_DELTA_MULT * num_of_wave;
    prototype.speed = RAD_COCKROACHES_SPEED + sqrt(HEALTH_DELTA_MULT * num_of_wave);
    prototype.damage = RAD_COCKROACHES_DAMAGE;
    num = RAD_COCKROACHES_AMOUNT_START + COCKROACHES_AMOUNT_WAVE * num_of_wave;
    interval = RAD_COCKROACHES_SPAWN_DELAY * (1 - num_of_wave / (num_of_wave + 5));

    radcockroaches.reserve(roads.size() * num);
    // revive old cockroaches
    for (auto cockr : radcockroaches)
        cockr->Revive(prototype);

    // add new cockroaches
    for (size_t i = radcockroaches.size() / roads.size(); i < num; ++i)
        for (size_t j = 0; j < roads.size(); ++j)
            radcockroaches.push_back(new RadCockroach(roads[j], prototype));

    survived = radcockroaches.size();
    active_enemy = 0;
    time_from_start = 0.;
    is_started = true;
}

void WaveRadCockroaches::Action(double time)
{
    time_from_start += time;
    active_enemy = time_from_start / interval + 1;
    if (active_enemy > radcockroaches.size())
        active_enemy = radcockroaches.size();
    for (size_t i = 0; i < active_enemy; ++i)
    {
        if (radcockroaches[i]->is_death)
            continue;
        if (radcockroaches[i]->health <= 0)
        {
            radcockroaches[i]->is_death = true;
            --survived;
            continue;
        }
        if (radcockroaches[i]->Move(time))
        {
            Fridge::health -= radcockroaches[i]->damage;
            radcockroaches[i]->pos = {-1000, -1000};
            radcockroaches[i]->is_death = true;
            --survived;
        }
    }
}

void WaveRadCockroaches::End()
{
    Event::money += WaveRadCockroaches::num * 200;
    survived = 0;
    is_started = false;
}