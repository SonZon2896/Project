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
    : trig({0, 0}, {0, 0}), Weapon(pos, &this->trig, SLAPPER_INTERVAL, SLAPPER_DAMAGE), direction{direction}
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

    upgrade_cost = SLAPPER_COAST_UPGRADE;
}

void Slapper::Upgrade()
{
    upgrade_cost += SLAPPER_COAST_UPGRADE_PER_LVL;
    ++level;
    damage += SLAPPER_DAMAGE_PER_LVL;
    interval *= SLAPPER_INTERVAL_PER_LVL;
}

// Dichlorvos

Dichlorvos::Dichlorvos(const Point &pos, Direction direction)
    : trig({0, 0}, {0, 0}), Weapon(pos, &this->trig, DICHLORVOS_INTERVAL, DICHLORVOS_DAMAGE), direction{direction}
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

    upgrade_cost = DICHLORVOS_COAST_UPGRADE;
}

void Dichlorvos::Upgrade()
{
    upgrade_cost += DICHLORVOS_COAST_UPGRADE_PER_LVL;
    ++level;
    damage += DICHLORVOS_DAMAGE_PER_LVL;
    interval *= DICHLORVOS_INTERVAL_PER_LVL;
}

// Catch

Trap::Trap(const Point &pos, Direction direction)
    : trig({0, 0}, {0, 0}), Weapon(pos, &this->trig, TRAP_INTERVAL, TRAP_DAMAGE), direction{direction}
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

    upgrade_cost = TRAP_COAST_UPGRADE;
    slowness = 1.2;
}

void Trap::Attack()
{
    for (auto enemy : trigger->enemies)
    {
        enemy->speed /= slowness;
        if (enemy->speed < TRAP_MIN_SLOWED_SPEED)
            enemy->speed = TRAP_MIN_SLOWED_SPEED;
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

void Trap::Upgrade()
{
    upgrade_cost += TRAP_COAST_UPGRADE_PER_LVL;
    ++level;
    damage += TRAP_DAMAGE_PER_LVL;
    slowness *= TRAP_SLOWNESS_PER_LVL;
    interval *= TRAP_SLOWNESS_PER_LVL;
}