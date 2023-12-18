#include <cmath>

#include "../Headers/heads.h"

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

// Enemy

Enemy::Enemy(const Road &road, PrototypeEnemy prototype)
    : road{road}, pos{this->road[0]}, speed{prototype.speed}, health{prototype.health}, damage{prototype.damage}
{
    if (this->road[this->road.size() - 1] != Fridge::pos)
        this->road.push_back(Fridge::pos);
    all_enemy.push_back(this);
    UpdateDir();
}

Point Enemy::GetDirection()
{
    return direction;
}

Direction Enemy::GetOrientation()
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

void Enemy::UpdateDir()
{

    point_on_road++;
    if (point_on_road == road.size()) return;
    
    double distance = (road[point_on_road] - road[point_on_road - 1]).Dist() * !is_death;
    direction = {(this->road[point_on_road] - this->road[point_on_road - 1]) / distance};
}

void Enemy::Revive(PrototypeEnemy prototype)
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

bool Enemy::Move(double time)
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

void Enemy::CheckTrigger()
{
    if (is_in_trig)
        return;
    for (auto &trigger : Trigger::GetAll())
    {
        if (trigger->In(pos))
        {
            is_in_trig = true;
            trigger->enemies.push_back(this);
            return;
        }
    }
}

Enemy::~Enemy()
{
    for (size_t i = 0; i < all_enemy.size(); ++i)
        if (all_enemy[i] == this)
        {
            all_enemy.erase(all_enemy.begin() + i);
            break;
        }
}

// Cockroaches

Cockroach::Cockroach(const Road &road, PrototypeEnemy prototype)
    : Enemy(road, prototype)
{
    all_cockroaches.push_back(this);
}

Cockroach::~Cockroach()
{
    for (size_t i = 0; i < all_cockroaches.size(); ++i)
        if (all_cockroaches[i] == this)
        {
            all_cockroaches.erase(all_cockroaches.begin() + i);
            break;
        }
}

// Mouse

Mouse::Mouse(const Road &road, PrototypeEnemy prototype)
    : Enemy(road, prototype)
{
    all_mouses.push_back(this);
}

Mouse::~Mouse()
{
    for (size_t i = 0; i < all_mouses.size(); ++i)
        if (all_mouses[i] == this)
        {
            all_mouses.erase(all_mouses.begin() + i);
            break;
        }
}

// Cockroaches

RadCockroach::RadCockroach(const Road &road, PrototypeEnemy prototype)
    : Enemy(road, prototype)
{
    all_rad_cockroaches.push_back(this);
}

RadCockroach::~RadCockroach()
{
    for (size_t i = 0; i < all_rad_cockroaches.size(); ++i)
        if (all_rad_cockroaches[i] == this)
        {
            all_rad_cockroaches.erase(all_rad_cockroaches.begin() + i);
            break;
        }
}

// Triggers

Trigger::Trigger(Point pos, Point size)
    : pos{pos}, size{size}
{
    all_trig.push_back(this);
}

void Trigger::CheckEnemies()
{
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        if (!In(enemies[i]->pos))
        {
            enemies[i]->is_in_trig = false;
            enemies.erase(enemies.begin() + i--);
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

DoomGuy::DoomGuy(int w, int h){
    pos = Point(w, h);
}

void DoomGuy::update_state(size_t amount_alive){
    if (amount_alive <= DOOMGUY_NORMAL)
        _current_state = DGSates::NORMAL;
    else if (amount_alive <= DOOMGUY_LITTLE_WARNING)
        _current_state = DGSates::LITTLE_WARNING;
    else if (amount_alive <= DOOMGUY_WARNING)
        _current_state = DGSates::WARNING;
}

DGSates DoomGuy::get_state(){
    return _current_state;
}
