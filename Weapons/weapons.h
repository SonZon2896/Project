#pragma once
#include "../Headers/heads.h"
#include "../events/events.h"

/// @brief weapons picture size x
#define WEAPON_SIZE_X 64
/// @brief weapons picture size y
#define WEAPON_SIZE_Y 64

/// @brief slapper start coast
#define SLAPPER_COAST 200
/// @brief slapper start upgrade coast
#define SLAPPER_COAST_UPGRADE 100
/// @brief slapper add to next upgrade coast
#define SLAPPER_COAST_UPGRADE_PER_LVL 200
/// @brief slapper trigger size for x coordinate
#define SLAPPER_TRIGGER_SIZE_X 100
/// @brief slapper trigger size for y coordinate
#define SLAPPER_TRIGGER_SIZE_Y 100
/// @brief slapper start damage
#define SLAPPER_DAMAGE 100
/// @brief slapper add damage for upgrade
#define SLAPPER_DAMAGE_PER_LVL 20
/// @brief slapper start interval
#define SLAPPER_INTERVAL 1.2
/// @brief slapper multipler for upgrade interval
#define SLAPPER_INTERVAL_PER_LVL 0.9

/// @brief dichlorvos start coast
#define DICHLORVOS_COAST 1000
/// @brief diclorvos start upgrade coast
#define DICHLORVOS_COAST_UPGRADE 500
/// @brief dichlorvos add to next upgrade coast
#define DICHLORVOS_COAST_UPGRADE_PER_LVL 400
/// @brief dichlorvos trigger size for x coordinate
#define DICHLORVOS_TRIGGER_SIZE_X 50
/// @brief dichlorvos trigger size for y coordinate
#define DICHLORVOS_TRIGGER_SIZE_Y 200
/// @brief dichlorvos start damage
#define DICHLORVOS_DAMAGE 25
/// @brief dichlorvos add damage for upgrade
#define DICHLORVOS_DAMAGE_PER_LVL 5
/// @brief dichlorvos start interval
#define DICHLORVOS_INTERVAL 0.4
/// @brief dichlorvos multipler for upgrade interval
#define DICHLORVOS_INTERVAL_PER_LVL 0.8

/// @brief trap start coast
#define TRAP_COAST 500
/// @brief trap start upgrade coast
#define TRAP_COAST_UPGRADE 400
/// @brief trap add to next upgrade coast
#define TRAP_COAST_UPGRADE_PER_LVL 200
/// @brief trap trigger size for x coordinate
#define TRAP_TRIGGER_SIZE_X 150
/// @brief trap trigger size for y coordinate
#define TRAP_TRIGGER_SIZE_Y 150
/// @brief trap start damage
#define TRAP_DAMAGE 20
/// @brief trap add damage for upgrade
#define TRAP_DAMAGE_PER_LVL 5
/// @brief trap start interval
#define TRAP_INTERVAL 1
/// @brief trap multipler for upgrade interval
#define TRAP_INTERVAL_PER_LVL 0.95
/// @brief trap slowness to enemy multipler
#define TRAP_SLOWNESS 1.2
/// @brief trap slowness multipler for upgrade
#define TRAP_SLOWNESS_PER_LVL 1.1
/// @brief max slowed speed to which trap can slowed
#define TRAP_MIN_SLOWED_SPEED 25


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
    virtual void Attack();

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
    double upgrade_cost;

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
    double upgrade_cost;

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
    double slowness;
    Trigger trig;
    Direction direction;
    double upgrade_cost;

    void Attack() final;

public:
    Trap(const Point &pos, Direction direction);


    /// @brief go to next level, this function don't check is it possible
    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const { return level; }
    auto GetDir() const { return direction; }
};