#pragma once
#include "../Headers/heads.h"
#include "../events/events.h"

class Weapon
{
protected:
    Weapon(const Point &pos, Trigger *trigger, double interval, double damage);

private:
    double time_last;
    static inline std::vector<Weapon *> all_weapons;

    void Attack();

public:
    double damage;
    double interval;
    Point pos;
    Trigger *trigger;

    Weapon() = delete;
    ~Weapon();

    void Action(double time);

    static auto GetAll() { return all_weapons; }
    const auto GetTrigger() const { return trigger; }
    auto GetProgress() const { return time_last > interval ? 1 : time_last / interval; }
    auto GetPos() const { return pos; }
};

#define slapper_size_x 64
#define slapper_size_y 64
#define slapper_trig_size_x 100
#define slapper_trig_size_y 100

class Slapper : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Direction direction;
    double upgrade_cost = 200;

public:
    Slapper(const Point &pos, Direction direction);

    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const { return level; }
    auto GetDir() const { return direction; }
};

#define dichlorvos_size_x 64
#define dichlorvos_size_y 64
#define dichlorvos_trig_size_x 40
#define dichlorvos_trig_size_y 200

class Dichlorvos : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Direction direction;
    double upgrade_cost = 500;

public:
    Dichlorvos(const Point &pos, Direction direction);

    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const { return level; }
    auto GetDir() const { return direction; }
};

#define trap_size_x 64
#define trap_size_y 64
#define trap_trig_size_x 30
#define trap_trig_size_y 30

class Trap : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Direction direction;
    double upgrade_cost = 250;

public:
    Trap(const Point &pos, Direction direction);

    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const { return level; }
    auto GetDir() const { return direction; }
};