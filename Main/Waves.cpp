#include "Waves.h"
#include "../Headers/heads.h"

#define HEALTH_DELTA_MULT 10
#define SPEED_DELTA_MULT 5

#define START_AMOUNT_COCKROACHES 20
#define AMOUNT_COCKROACHES_DELTA_MULT 5
#define SPAWN_DELAY .2

#define MOUSE_HEALTH 3000
#define MOUSE_DAMAGE 50
#define MOUSE_SPEED 50
#define MOUSE_INTERVAL 10
#define MOUSE_WAVE_MULTIPLICITY 5


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
    prototype.health = ENEMY_HEALTH + HEALTH_DELTA_MULT * num_of_wave;
    prototype.speed = ENEMY_SPEED + HEALTH_DELTA_MULT * num_of_wave;
    prototype.damage = ENEMY_DAMAGE;
    num = START_AMOUNT_COCKROACHES + AMOUNT_COCKROACHES_DELTA_MULT * num_of_wave;
    interval = SPAWN_DELAY * (1 - num_of_wave / (num_of_wave + 10));

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
    prototype.health = MOUSE_HEALTH;
    prototype.speed = MOUSE_DAMAGE;
    prototype.damage = MOUSE_SPEED;
    num = (
        num_of_wave / MOUSE_WAVE_MULTIPLICITY) * 
        ((num_of_wave % MOUSE_WAVE_MULTIPLICITY) == 0
    );
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