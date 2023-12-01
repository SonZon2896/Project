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
        : x{x}, y{y} {}

    Point operator+=(const Point &point)
    {
        x += point.x;
        y += point.y;
        return *this;
    }

    Point operator-=(const Point &point)
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

    Point operator=(const Point &second)
    {
        this->x = second.x;
        this->y = second.y;
        return *this;
    }

    bool operator==(const Point &second)
    {
        if (this->x == second.x &&
            this->y == second.y)
            return true;
        return false;
    }

    bool operator!=(const Point &second)
    {
        return !(*this == second);
    }

    double Dist();
};

Point operator+(Point first, const Point &second);
Point operator-(Point first, const Point &second);
Point operator/(Point first, double second);
Point operator*(Point first, double second);

class Fridge
{
public:
    static Point pos;
    static double health;
};

#define Road std::vector<Point>

class Trigger;

class Cockroach
{
protected:
    /// @brief vector of pointers to all cockroaches
    static inline std::vector<Cockroach *> all_cockr{};

private:
    Road road;
    Point direction;
    std::size_t point_on_road = 0;
    bool is_in_trig = false;

    /// @brief update directory, when turn
    void UpdateDir();

public:
    friend Trigger;
    double health;
    Point pos;
    double speed;
    double damage;
    bool is_death = false;

    Cockroach() = delete;
    Cockroach(const Road &road, double speed = 1, double health = 100., double damage = 5.);

    bool Move(double time);
    void CheckTrigger();
    static auto GetAll() { return all_cockr; }

    ~Cockroach();
};

/// @brief class to check cockroaches
class Trigger
{
protected:
    /// @brief vector of pointers to all triggers
    static inline std::vector<Trigger *> all_trig{};

public:
    Point pos;
    Point size;
    std::vector<Cockroach *> cockroaches;

    Trigger() = delete;
    Trigger(Point pos, Point size);

    /// @brief check cockroach move out from trigger
    void CheckCockroaches();
    /// @brief check point in trigger or not
    bool In(Point pos);

    static auto GetAll() { return all_trig; }

    ~Trigger();
};