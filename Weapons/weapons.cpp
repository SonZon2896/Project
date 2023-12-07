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
            break;
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

Slapper::Slapper(const Point &pos, Direction direction)
    : trig({0., 0.}, {0., 0.}), Weapon(pos, &this->trig, 0.4, 150), direction{direction}
{
    switch (direction)
    {
    case UP:
        trig.pos = {pos.x - slapper_trig_size_x / 2, pos.y - weapon_size_y / 2 - slapper_trig_size_y};
        trig.size = {slapper_trig_size_x, slapper_trig_size_y};
        break;
    case DOWN:
        trig.pos = {pos.x - slapper_trig_size_x / 2, pos.y + weapon_size_y / 2};
        trig.size = {slapper_trig_size_x, slapper_trig_size_y};
        break;
    case LEFT:
        trig.pos = {pos.x - weapon_size_x / 2 - slapper_trig_size_y, pos.y - slapper_trig_size_x / 2};
        trig.size = {slapper_trig_size_y, slapper_trig_size_x};
        break;
    case RIGHT:
        trig.pos = {pos.x + weapon_size_x / 2, pos.y - slapper_trig_size_x / 2};
        trig.size = {slapper_trig_size_y, slapper_trig_size_x};
        break;
    }
}

void Slapper::Upgrade()
{
    upgrade_cost += 100;
    ++level;
    damage += 20;
    interval -= interval / 100.;
}

#undef slapper_trig_size_x
#undef slapper_trig_size_y

// Dichlorvos

Dichlorvos::Dichlorvos(const Point &pos, Direction direction)
    : trig({0., 0.}, {0., 0.}), Weapon(pos, &this->trig, 0.1, 15), direction{direction}
{
    switch (direction)
    {
    case UP:
        trig.pos = {pos.x - dichlorvos_trig_size_x / 2, pos.y - weapon_size_y / 2 - dichlorvos_trig_size_y};
        trig.size = {dichlorvos_trig_size_x, dichlorvos_trig_size_y};
        break;
    case DOWN:
        trig.pos = {pos.x - dichlorvos_trig_size_x / 2, pos.y + weapon_size_y / 2};
        trig.size = {dichlorvos_trig_size_x, dichlorvos_trig_size_y};
        break;
    case LEFT:
        trig.pos = {pos.x - weapon_size_x / 2 - dichlorvos_trig_size_y, pos.y - dichlorvos_trig_size_x / 2};
        trig.size = {dichlorvos_trig_size_y, dichlorvos_trig_size_x};
        break;
    case RIGHT:
        trig.pos = {pos.x + weapon_size_x / 2, pos.y - dichlorvos_trig_size_x / 2};
        trig.size = {dichlorvos_trig_size_y, dichlorvos_trig_size_x};
        break;
    }
}

#undef dichlorvos_trig_size_x
#undef dichlorvos_trig_size_y

void Dichlorvos::Upgrade()
{
    upgrade_cost += 100;
    ++level;
    damage += 10;
    interval -= interval / 50.;
}

// Catch

Trap::Trap(const Point &pos, Direction direction)
    : trig({0., 0.}, {0., 0.}), Weapon(pos, &this->trig, 3., 200), direction{direction}
{
    switch (direction)
    {
    case UP:
        trig.pos = {pos.x - trap_trig_size_x / 2, pos.y - weapon_size_y / 2 - trap_trig_size_y};
        trig.size = {trap_trig_size_x, trap_trig_size_y};
        break;
    case DOWN:
        trig.pos = {pos.x - trap_trig_size_x / 2, pos.y + weapon_size_y / 2};
        trig.size = {trap_trig_size_x, trap_trig_size_y};
        break;
    case LEFT:
        trig.pos = {pos.x - weapon_size_x / 2 - trap_trig_size_y, pos.y - trap_trig_size_x / 2};
        trig.size = {trap_trig_size_y, trap_trig_size_x};
        break;
    case RIGHT:
        trig.pos = {pos.x + weapon_size_x / 2, pos.y - trap_trig_size_x / 2};
        trig.size = {trap_trig_size_y, trap_trig_size_x};
        break;
    }
}

#undef trap_trig_size_x
#undef trap_trig_size_y

void Trap::Upgrade()
{
    upgrade_cost += 100;
    ++level;
    damage += 100;
    interval -= interval / 100.;
}