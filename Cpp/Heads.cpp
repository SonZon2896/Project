#include "../Headers/heads.h"

Point operator+(Point first, const Point& second)
{
    return first += second;
}

Point operator-(Point first, const Point& second)
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

//Cockroaches

Cockroach::Cockroach(const Road& road, double speed, double health, double damage)
    : road{road}, pos{this->road[0]}, speed{speed}, health{health}, damage{damage}
{
    if (this->road[this->road.size()-1] != Fridge::pos)
        this->road.push_back(Fridge::pos);
    all_cockr.push_back(this);
    UpdateDir();
}

void Cockroach::UpdateDir()
{
    ++point_on_road;
    double distance = (road[point_on_road] - road[point_on_road-1]).Dist();
    direction = {(this->road[point_on_road] - this->road[point_on_road-1]) / distance};
}

bool Cockroach::Move(double time)
{
    pos += direction * speed * time;
    // Проверяем не пробежал ли таракан точку поворота
    if ((pos - road[point_on_road-1]).Dist() > (road[point_on_road] - road[point_on_road-1]).Dist())
    {
        double extra_dist = (pos - road[point_on_road]).Dist();
        UpdateDir();
        pos = road[point_on_road-1] + direction * extra_dist;
    }
    if (point_on_road >= road.size())
        return true;
    return false;
}

void Cockroach::CheckTrigger()
{
    
    if (is_in_trig)
        return;
    for (auto& trigger : Trigger::GetAll())
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

//Triggers

Trigger::Trigger(const Point& left, const Point& right)
    :ld{left}, ru{right}
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

bool Trigger::In(const Point& pos)
{
    if (ld.x <= pos.x && pos.x <= ru.x &&
        ld.y <= pos.y && pos.y <= ru.y)
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