#pragma once
#include <vector>
#include "../Headers/heads.h"

class Road
{
public:
    std::vector<Point> points;

    Road(std::vector<Point> points): points{points} {}
};

class Cocroach
{
private:
    const Road road;
public:
    double health;
    Point pos;
    double speed;

    Cocroach() = delete;
    Cocroach(const Road& road, Point pos = {0., 0.}, double speed = 0, double health = 100.)
        : road{road}, pos{pos}, speed{speed}, health{health}
        {}

    CheckTriggers(const std::vector<*Trigger> triggers);    
};