#include "weapons.h"

// Weapon

Weapon::Weapon(const Point &pos, Trigger *trigger, double interval, double damage)
    : pos{pos}, trigger{trigger}, interval{interval}, damage{damage}
{
    all_weapons.push_back(this);
}

void Weapon::Attack()
{
    for (auto cockr : trigger->cockroaches)
    {
        cockr->health -= damage;
        if (cockr->health <= 0)
            for (size_t i = 0; i < trigger->cockroaches.size(); ++i)
                if (trigger->cockroaches[i] == cockr)
                {
                    trigger->cockroaches.erase(trigger->cockroaches.begin() + i);
                    break;
                }
    }
}

Weapon::~Weapon()
{
    for (size_t i = 0; i < all_weapons.size(); ++i)
        if (all_weapons[i] == this)
        {
            all_weapons.erase(all_weapons.begin() + i);
            return;
        }
}

void Weapon::Action(double time)
{
    time_last += time;
    trigger->CheckCockroaches();
    if (trigger->cockroaches.size() != 0 && time_last >= interval)
    {
        Attack();
        time_last = 0;
    }
}

// Slapper

Slapper::Slapper(const Point &pos)
    : trig({pos.x - 50, pos.y + 25}, {100, 100}), Weapon(pos, &this->trig, 0.5, 50)
{
}

// Dichlorvos

Dichlorvos::Dichlorvos(const Point &pos)
    : trig({pos.x - 50, pos.y + 25}, {100, 100}), Weapon(pos, &this->trig, 1., 50)
{
}

// Catch

Trap::Trap(const Point &pos)
    : trig({pos.x - 50, pos.y + 25}, {100, 100}), Weapon(pos, &this->trig, 1., 50)
{
}
