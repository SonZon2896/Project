#pragma once
#include <vector>
class Point
{
public:
    double x;
    double y;

    Point(double x, double y)
        :x{x}, y{y} {}

    Point& operator+=(const Point& new_coord)
    {
        x += new_coord.x;
        y += new_coord.y;
        return *this;
    }

    Point& operator*=(double speed)
    {
        x *= speed;
        y *= speed;
        return *this;
    }

    Point& operator=(const Point& point)
    {
        x = point.x;
        y = point.y;
    }
};


class Student_money
{
public:
    double money = 0;
    double speed;

    Student_money(double money)
        :money{money} {}

    void update(double time)
    {
        money += (time * speed);
    }
};

class Road
{
public:
    std::vector<Point> points;

    Road(std::vector<Point> points): points{points} {}
};

class Trigger;
class Cocroach
{
private:
    const Road road;
    std::size_t point_on_road = 0;
public:
    double health;
    Point pos;
    double speed;

    Cocroach() = delete;
    Cocroach(const Road& road, Point pos = {0., 0.}, double speed = 0, double health = 100.)
        : road{road}, pos{pos}, speed{speed}, health{health}
        {}

    void Move(double time);
    void CheckTrigger(const std::vector<Trigger*>& triggers);
};

class Trigger
{
public:
    Point ld;
    Point ru;
    std::vector<Cocroach*> cocroaches;

    Trigger() = delete;
    Trigger(const Point& left, const Point& right)
        : ld(left), ru(right) {}

    void CheckCocroaches();
    bool In(const Point& pos);
};