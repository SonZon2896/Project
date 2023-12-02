#pragma once
#include "../Headers/heads.h"

class Weapon
{
protected:
    Weapon(const Point &pos, Trigger *trigger, double interval, double damage);

private:
    double time_last;
    static inline std::vector<Weapon*> all_weapons;

    void Attack();

public:
    double damage;
    double interval;
    Point pos;
    Trigger *trigger;

    Weapon() = delete;
    ~Weapon();

    void Action(double time);

    static auto GetAll() {return all_weapons;}
    const auto GetTrigger() const {return trigger;}
    auto GetProgress() const {return time_last > interval ? 1 : time_last / interval;}
    auto GetPos() const {return pos;}
};

class Slapper : public Weapon
{
private:
    int level = 1;
    Trigger trig;

public:
    Slapper(const Point &pos);

    void Upgrade();
};

class Dichlorvos : public Weapon
{
private:
    int level = 1;
    Trigger trig;

public:
    Dichlorvos(const Point &pos);

    void Upgrade();
};

class Trap : public Weapon
{
private:
    int level = 1;
    Trigger trig;

public:
    Trap(const Point &pos);

    void Upgrade();
};