#pragma once
#include <vector>
#include <math.h>

class Point
{
public:
    double x;
    double y;

    Point() = default;
    Point(double x, double y)
        :x{x}, y{y} {}

    Point operator+=(const Point& point)
    {
        x += point.x;
        y += point.y;
        return *this;
    }

    Point operator-=(const Point& point)
    {
        x -= point.x;
        y -= point.y;
        return *this;
    }

    Point operator*=(double value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    Point operator/=(double value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    Point operator=(const Point& second)
    {
        this->x = second.x;
        this->y = second.y;
        return *this;
    }

    double Dist();
};

Point operator+(Point first, const Point& second);
Point operator-(Point first, const Point& second);
Point operator/(Point first, double second);
Point operator*(Point first, double second);

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

class Trigger;

class Cockroach
{
private:
    std::vector<Point> road;
    Point direction;
    std::size_t point_on_road = 0;
    bool is_in_trig = false;

    void UpdateDir();
public:
    friend Trigger;
    double health;
    Point pos;
    double speed;
    bool is_death = false;

    Cockroach() = delete;
    Cockroach(const std::vector<Point>& road, double speed = 0, double health = 100.);

    bool Move(double time);
    void CheckTrigger(const std::vector<Trigger*>& triggers);
};

class Trigger
{
public:
    Point ld;
    Point ru;
    std::vector<Cockroach*> cockroaches;

    Trigger() = delete;
    Trigger(const Point& left, const Point& right)
        : ld(left), ru(right) {}

    void CheckCockroaches();
    bool In(const Point& pos);
};