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

Cockroach::Cockroach(const std::vector<Point>& road, double speed, double health)
    : road{road}, pos{this->road[0]}, speed{speed}, health{health}
{
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

void Cockroach::CheckTrigger(const std::vector<Trigger*>& triggers)
{
    if (is_in_trig)
        return;
    for (auto& trigger : triggers)
    {
        if (trigger->In(pos))
        {
            is_in_trig = true;
            trigger->cockroaches.push_back(this);
            return;
        }
    }
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