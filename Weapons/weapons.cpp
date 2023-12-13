#include "weapons.h"

// Weapon

Weapon::Weapon(const Point &pos, Trigger *trigger, double interval, double damage)
    : pos{pos}, trigger{trigger}, interval{interval}, damage{damage}
{
    all_weapons.push_back(this);
}

void Weapon::Attack()
{
    for (auto enemy : trigger->enemies)
    {
        enemy->health -= damage;
        if (enemy->health <= 0)
            for (size_t i = 0; i < trigger->enemies.size(); ++i)
                if (trigger->enemies[i] == enemy)
                {
                    trigger->enemies.erase(trigger->enemies.begin() + i);
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
    trigger->CheckEnemies();
    if (trigger->enemies.size() != 0 && time_last >= interval)
    {
        Attack();
        time_last = 0;
    }
}

// Slapper

Slapper::Slapper(const Point &pos, Direction direction)
    : trig({0, 0}, {0, 0}), Weapon(pos, &this->trig, 1.2, 110), direction{direction}
{
    switch (direction)
    {
    case UP:
        trig.pos = {pos.x - SLAPPER_TRIGGER_SIZE_X / 2, pos.y - WEAPON_SIZE_Y / 2 - SLAPPER_TRIGGER_SIZE_Y};
        trig.size = {SLAPPER_TRIGGER_SIZE_X, SLAPPER_TRIGGER_SIZE_Y};
        break;
    case DOWN:
        trig.pos = {pos.x - SLAPPER_TRIGGER_SIZE_X / 2, pos.y + WEAPON_SIZE_Y / 2};
        trig.size = {SLAPPER_TRIGGER_SIZE_X, SLAPPER_TRIGGER_SIZE_Y};
        break;
    case LEFT:
        trig.pos = {pos.x - WEAPON_SIZE_X / 2 - SLAPPER_TRIGGER_SIZE_Y, pos.y - SLAPPER_TRIGGER_SIZE_X / 2};
        trig.size = {SLAPPER_TRIGGER_SIZE_Y, SLAPPER_TRIGGER_SIZE_X};
        break;
    case RIGHT:
        trig.pos = {pos.x + WEAPON_SIZE_X / 2, pos.y - SLAPPER_TRIGGER_SIZE_X / 2};
        trig.size = {SLAPPER_TRIGGER_SIZE_Y, SLAPPER_TRIGGER_SIZE_X};
        break;
    }
}

void Slapper::Upgrade()
{
    upgrade_cost += 200;
    ++level;
    damage += 5;
    interval -= interval / 100.;
}

#undef SLAPPER_TRIGGER_SIZE_X
#undef SLAPPER_TRIGGER_SIZE_Y

// Dichlorvos

Dichlorvos::Dichlorvos(const Point &pos, Direction direction)
    : trig({0, 0}, {0, 0}), Weapon(pos, &this->trig, 1, 120), direction{direction}
{
    switch (direction)
    {
    case UP:
        trig.pos = {pos.x - DICHLORVOS_TRIGGER_SIZE_X / 2, pos.y - WEAPON_SIZE_Y / 2 - DICHLORVOS_TRIGGER_SIZE_Y};
        trig.size = {DICHLORVOS_TRIGGER_SIZE_X, DICHLORVOS_TRIGGER_SIZE_Y};
        break;
    case DOWN:
        trig.pos = {pos.x - DICHLORVOS_TRIGGER_SIZE_X / 2, pos.y + WEAPON_SIZE_Y / 2};
        trig.size = {DICHLORVOS_TRIGGER_SIZE_X, DICHLORVOS_TRIGGER_SIZE_Y};
        break;
    case LEFT:
        trig.pos = {pos.x - WEAPON_SIZE_X / 2 - DICHLORVOS_TRIGGER_SIZE_Y, pos.y - DICHLORVOS_TRIGGER_SIZE_X / 2};
        trig.size = {DICHLORVOS_TRIGGER_SIZE_Y, DICHLORVOS_TRIGGER_SIZE_X};
        break;
    case RIGHT:
        trig.pos = {pos.x + WEAPON_SIZE_X / 2, pos.y - DICHLORVOS_TRIGGER_SIZE_X / 2};
        trig.size = {DICHLORVOS_TRIGGER_SIZE_Y, DICHLORVOS_TRIGGER_SIZE_X};
        break;
    }
}

#undef DICHLORVOS_TRIGGER_SIZE_X
#undef DICHLORVOS_TRIGGER_SIZE_Y

void Dichlorvos::Upgrade()
{
    upgrade_cost += 400;
    ++level;
    damage += 10;
    interval -= interval / 50.;
}

// Catch

Trap::Trap(const Point &pos, Direction direction)
    : trig({0, 0}, {0, 0}), Weapon(pos, &this->trig, 3, 200), direction{direction}
{
    switch (direction)
    {
    case UP:
        trig.pos = {pos.x - TRAP_TRIGGER_SIZE_X / 2, pos.y - WEAPON_SIZE_Y / 2 - TRAP_TRIGGER_SIZE_Y};
        trig.size = {TRAP_TRIGGER_SIZE_X, TRAP_TRIGGER_SIZE_Y};
        break;
    case DOWN:
        trig.pos = {pos.x - TRAP_TRIGGER_SIZE_X / 2, pos.y + WEAPON_SIZE_Y / 2};
        trig.size = {TRAP_TRIGGER_SIZE_X, TRAP_TRIGGER_SIZE_Y};
        break;
    case LEFT:
        trig.pos = {pos.x - WEAPON_SIZE_X / 2 - TRAP_TRIGGER_SIZE_Y, pos.y - TRAP_TRIGGER_SIZE_X / 2};
        trig.size = {TRAP_TRIGGER_SIZE_Y, TRAP_TRIGGER_SIZE_X};
        break;
    case RIGHT:
        trig.pos = {pos.x + WEAPON_SIZE_X / 2, pos.y - TRAP_TRIGGER_SIZE_X / 2};
        trig.size = {TRAP_TRIGGER_SIZE_Y, TRAP_TRIGGER_SIZE_X};
        break;
    }
}

#undef TRAP_TRIGGER_SIZE_X
#undef TRAP_TRIGGER_SIZE_Y

void Trap::Upgrade()
{
    upgrade_cost += 100;
    ++level;
    damage += 100;
    interval -= interval / 100.;
}