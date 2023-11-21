#include <head.h>
class Trigger;
class Point;





class Tapok
{
public:
    double damage;
    double time;
    Point coord;
    Trigger trigger;


    Tapok(Point&& coordinate, Trigger&& trigger_, double time_sleep, double damage_)
    {
        damage = damage_;
        time = time_sleep; 
        coord = coordinate;
        trigger = trigger_;
    }

    std::vector<Cocroach*> cocr = trigger_.cocroaches;

    void DamageForCocroaches()
    {
        for(auto taracan: cocr)
            taracan.health -= damage;
    }

    



    

};