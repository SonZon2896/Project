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

class Slapper : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Point trig_size{100, 100};
    double upgrade_cost = 200;

public:
    Slapper(const Point &pos);

    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const {return level;}
};

class Dichlorvos : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Point trig_size{30, 200};
    bool is_right;
    double upgrade_cost = 500;

public:
    Dichlorvos(const Point &pos, bool is_right = false);

    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const {return level;}
};

class Trap : public Weapon
{
private:
    int level = 1;
    Trigger trig;
    Point trig_size{25, 25};
    double upgrade_cost = 250;

public:
    Trap(const Point &pos);

    void Upgrade();
    auto GetCost() const { return upgrade_cost; }
    auto GetLvl() const {return level;}
};