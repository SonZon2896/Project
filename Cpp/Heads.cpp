#include "../Headers/heads.h"

Point& operator+(Point first, const Point& second)
{
    return first += second;
}

Point& operator-(Point first, const Point& second)
{
    return first -= second;
}

Point& operator*(Point first, double second)
{
    return first *= second;
}

Point& operator/(Point first, double second)
{
    return first /= second;
}

double Point::Dist()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

Point& Road::operator[](int index)
{
    return points[index];
}

Cocroach::Cocroach(const Road& road, const Point& pos, double speed, double health)
    : road{road}, pos{pos}, speed{speed}, health{health}
{
    double distance = (this->road[1] - this->road[0]).Dist();
    direction = (this->road[1] - this->road[0]) / distance;
}

void Cocroach::UpdateDir()
{
    ++point_on_road;
    double distance = (road[point_on_road] - road[point_on_road-1]).Dist();
    direction = (this->road[point_on_road] - this->road[point_on_road-1]) / distance;
}

void Cocroach::Move(double time)
{
    pos += direction * speed * time;
    // Проверяем не пробежал ли таракан точку поворота
    if ((pos - road[point_on_road-1]).Dist() > (road[point_on_road] - road[point_on_road-1]).Dist())
    {
        double extra_dist = (pos - road[point_on_road]).Dist();
        UpdateDir();
        pos = road[point_on_road] + direction * extra_dist;
    }
}

void Cocroach::CheckTrigger(const std::vector<Trigger*>& triggers)
{
    if (is_in_trig)
        return;
    for (auto& trigger : triggers)
    {
        if (trigger->In(pos))
        {
            is_in_trig = true;
            trigger->cocroaches.push_back(this);
            return;
        }
    }
}

void Trigger::CheckCocroaches()
{
    for (size_t i = 0; i < cocroaches.size(); ++i)
    {
        if (!In(cocroaches[i]->pos))
        {
            cocroaches[i]->is_in_trig = false;
            cocroaches.erase(cocroaches.begin() + i--);
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