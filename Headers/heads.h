#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <map>
#include <string>

/// @brief Enum of directions
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

/// @brief Enum with game exit statuses
enum GameOverStatus{
    GAMEOVER_WASTED,
    GAMEOVER_QUIT
};

/// @brief enum for Pack Structures
enum EnumWeapon
{
    slapper = 0,
    dichlorvos,
    trap
};

/// @brief Utility structure for positioning objects
class Point
{
public:
    int x;
    int y;

    Point() = default;
    Point(int x, int y)
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

/// @brief Fridge on game field
class Fridge
{
public:
    static Point pos;
    static double health;
};

#define Road std::vector<Point>

class Trigger;

/// @brief Structure with default common field of all enemies
struct PrototypeEnemy
{
    double health;
    double speed;
    double damage;
    PrototypeEnemy() = default;
    PrototypeEnemy(double hp, double sp, double dm) : health{hp}, speed{sp}, damage{dm} {}
};

/// @brief Main enemy class
class Enemy
{
protected:
    /// @brief vector of pointers to all cockroaches
    static inline std::vector<Enemy *> all_enemy;
    Enemy(const Road& road, PrototypeEnemy prototype);

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

    Enemy() = delete;

    void Revive(PrototypeEnemy prototype);
    bool Move(double time);
    void CheckTrigger();
    static auto GetAll() { return all_enemy; }
    Direction GetOrientation();
    Point GetDirection();

    ~Enemy();
};

/// @brief Class of cockroaches
class Cockroach : public Enemy
{
private:
    static inline std::vector<Cockroach *> all_cockroaches;
public:
    Cockroach() = delete;
    Cockroach(const Road &road, PrototypeEnemy prototype);
    ~Cockroach();

    static auto GetAll() {return all_cockroaches;}
};

/// @brief Class of mouse
class Mouse : public Enemy
{
private:
    static inline std::vector<Mouse *> all_mouses;
public:
    Mouse() = delete;
    Mouse(const Road &road, PrototypeEnemy prototype);
    ~Mouse();

    static auto GetAll() {return all_mouses;}
};

/// @brief Class of enter trigger 
class Trigger
{
protected:
    /// @brief vector of pointers to all triggers
    static inline std::vector<Trigger *> all_trig{};

public:
    Point pos;
    Point size;
    std::vector<Enemy *> enemies;

    Trigger() = delete;
    Trigger(Point pos, Point size);

    /// @brief check cockroach move out from trigger
    void CheckEnemies();
    /// @brief check point in trigger or not
    bool In(Point pos);

    static auto GetAll() { return all_trig; }

    ~Trigger();
};

/// @brief Function which takes orientated image of cockroach 
std::string GetPathToImageCockr(Cockroach &);
