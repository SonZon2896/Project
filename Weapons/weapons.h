#pragma once
#include "../Headers/heads.h"

class Weapon
{
protected:
    Weapon(const Point& coordinate, const Trigger& trigger_, double time_sleep, double damage_)
    : coord{coordinate}, trigger{trigger_}, time{time_sleep}, damage{damage_} {}
public:
    double damage;
    double time;
    Point coord;
    Trigger trigger;

    Weapon() = delete;


    std::vector<Cockroach*> cocr = trigger.cockroaches;

    void DamageForCockroaches()
    {
        for(auto taracan: cocr)
            taracan->health -= damage;
    }

    ~Weapon(){
        
    }
};


class Tapok : protected Weapon
{
public:
    Tapok() = delete;
    Tapok(const Point& start_pos) : Weapon(start_pos, {{0.0, 0.0}, {1.0,1.0}}, 2.0, 25.0) {};

};

class Dihlofoz : protected Weapon
{
public:
    Dihlofoz() = delete;
    Dihlofoz(const Point& start_pos) : Weapon(start_pos, {{0.0, 0.0}, {1.0,1.0}}, 2.0, 50.0) {};

};

class Catch : protected Weapon
{
public:
    Catch() = delete;
    Catch(const Point& start_pos) : Weapon(start_pos, {{0.0, 0.0}, {1.0,1.0}}, 2.0, 100.0) {};

};