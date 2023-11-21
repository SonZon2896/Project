#include <heads.h>
class Trigger;
class Point;







class Weapon
{
protected:
    Weapon(const Point& coordinate, const Trigger& trigger_, double time_sleep, double damage_)
    {
        damage = damage_;
        time = time_sleep; 
        coord = coordinate;
        trigger = trigger_;
    }
public:
    double damage;
    double time;
    Point coord;
    Trigger trigger;

    Weapon() = delete;


    std::vector<Cocroach*> cocr = trigger.cocroaches;

    void DamageForCocroaches()
    {
        for(auto taracan: cocr)
            taracan->health -= damage;
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