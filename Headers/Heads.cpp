#include "../Headers/heads.h"
#include <cmath>

#define EPS 1e-8

std::map<Direction, std::string> cockroach_direction = {
    {UP, "./PNG/cockroach_px_up.png"},
    {RIGHT, "./PNG/cockroach_px_right.png"},
    {DOWN, "./PNG/cockroach_px_down.png"},
    {LEFT, "./PNG/cockroach_px_left.png"}};

bool is_equal(double a, double b)
{
    long double eps = EPS;
    return abs(a - b) <= eps;
}

Point operator+(Point first, const Point &second)
{
    return first += second;
}

Point operator-(Point first, const Point &second)
{
    return first -= second;
}

Point operator*(Point first, double second)
{
    return first *= second;
}

Point operator/(Point first, double second)
{
    return first /= second;
}

double Point::Dist()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

std::string GetPathToImageCockr(Cockroach &cockr)
{
    return cockroach_direction[cockr.GetOrientation()];
}

// Cockroaches

Cockroach::Cockroach(const Road &road, PrototypeCockroach prototype)
    : road{road}, pos{this->road[0]}, speed{prototype.speed}, health{prototype.health}, damage{prototype.damage}
{
    if (this->road[this->road.size() - 1] != Fridge::pos)
        this->road.push_back(Fridge::pos);
    all_cockr.push_back(this);
    UpdateDir();
}

Point Cockroach::GetDirection()
{
    return direction;
}

Direction Cockroach::GetOrientation()
{
    if (is_equal(direction.x, 0) && is_equal(direction.y, 1))
        return DOWN;
    if (is_equal(direction.x, 1) && is_equal(direction.y, 0))
        return RIGHT;
    if (is_equal(direction.x, 0) && is_equal(direction.y, -1))
        return UP;
    if (is_equal(direction.x, -1) && is_equal(direction.y, 0))
        return LEFT;

    return UP;
}

void Cockroach::UpdateDir()
{

    ++point_on_road;
    double distance = (road[point_on_road] - road[point_on_road - 1]).Dist() * !is_death;
    direction = {(this->road[point_on_road] - this->road[point_on_road - 1]) / distance};
}

void Cockroach::Revive(PrototypeCockroach prototype)
{
    this->speed = prototype.speed;
    this->health = prototype.health;
    this->damage = prototype.damage;

    is_in_trig = false;
    is_death = false;
    pos = road[0];
    point_on_road = 0;
    UpdateDir();
}

bool Cockroach::Move(double time)
{
    pos += direction * speed * time;
    // Проверяем не пробежал ли таракан точку поворота
    if ((pos - road[point_on_road - 1]).Dist() > (road[point_on_road] - road[point_on_road - 1]).Dist())
    {
        double extra_dist = (pos - road[point_on_road]).Dist();
        UpdateDir();
        pos = road[point_on_road - 1] + direction * extra_dist;
    }
    if (point_on_road >= road.size())
        return true;
    return false;
}

void Cockroach::CheckTrigger()
{

    if (is_in_trig)
        return;
    for (auto &trigger : Trigger::GetAll())
    {
        if (trigger->In(pos))
        {
            is_in_trig = true;
            trigger->cockroaches.push_back(this);
            return;
        }
    }
}

Cockroach::~Cockroach()
{
    for (size_t i = 0; i < all_cockr.size(); ++i)
        if (all_cockr[i] == this)
        {
            all_cockr.erase(all_cockr.begin() + i);
            break;
        }
}

// Triggers

Trigger::Trigger(Point pos, Point size)
    : pos{pos}, size{size}
{
    all_trig.push_back(this);
}

void Trigger::CheckCockroaches()
{
    for (size_t i = 0; i < cockroaches.size(); ++i)
    {
        if (!In(cockroaches[i]->pos))
        {
            cockroaches[i]->is_in_trig = false;
            cockroaches.erase(cockroaches.begin() + i--);
        }
    }
}

bool Trigger::In(Point pos)
{
    pos -= this->pos;
    if (0 <= pos.x && pos.x <= this->size.x &&
        0 <= pos.y && pos.y <= this->size.y)
        return true;
    return false;
}

Trigger::~Trigger()
{
    for (size_t i = 0; i < all_trig.size(); ++i)
        if (all_trig[i] == this)
        {
            all_trig.erase(all_trig.begin() + i);
            break;
        }
}