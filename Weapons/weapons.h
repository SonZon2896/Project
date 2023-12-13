#pragma once
#include "../Headers/heads.h"
#include "../events/events.h"

#define WEAPON_SIZE_X 64
#define WEAPON_SIZE_Y 64

#define SLAPPER_TRIGGER_SIZE_X 100
#define SLAPPER_TRIGGER_SIZE_Y 100

#define DICHLORVOS_TRIGGER_SIZE_X 50
#define DICHLORVOS_TRIGGER_SIZE_Y 200

#define TRAP_TRIGGER_SIZE_X 30
#define TRAP_TRIGGER_SIZE_Y 30

/// @brief Absolute class to make weapons
class Weapon
{
protected:
    Weapon(const Point &pos, Trigger *trigger, double interval, double damage);

private:
    /// @brief time from last attack
    double time_last;
    /// @brief pointers to all weapons
    static inline std::vector<Weapon *> all_weapons;

    /// @brief kick cockroaches in trigger
    void Attack();

public:
    double damage;
    double interval;
    Point pos;
    Trigger *trigger;

    Weapon() = delete;
    ~Weapon();

    /// @brief check what weapon need to do
    /// @param time 
    void Action(double time);

    static auto GetAll() { return all_weapons; }
    const auto GetTrigger() const { return trigger; }
    auto GetProgress() const { return time_last > interval ? 1 : time_last / interval; }
    auto GetPos() const { return pos; }
};



class Slapper : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Direction direction;
    double upgrade_cost = 200;

public:
    Slapper(const Point &pos, Direction direction);

    /// @brief go to next level, this function don't check is it possible
    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const { return level; }
    auto GetDir() const { return direction; }
};


class Dichlorvos : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Direction direction;
    double upgrade_cost = 1000;

public:
    Dichlorvos(const Point &pos, Direction direction);

    /// @brief go to next level, this function don't check is it possible
    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const { return level; }
    auto GetDir() const { return direction; }
};

class Trap : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Direction direction;
    double upgrade_cost = 250;

public:
    Trap(const Point &pos, Direction direction);

    /// @brief go to next level, this function don't check is it possible
    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const { return level; }
    auto GetDir() const { return direction; }
};