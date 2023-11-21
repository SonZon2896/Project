class Point
{
public:
    double x;
    double y;

    Point(double x_, double y_)
    {
        x = x_;
        y = y_;
    }

    Point& operator+=(const Point& new_coord)
    {
        x += new_coord.x;
        y += new_coord.y;
        return *this;
    }

    Point& operator*=(const double& speed)
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
    double speed = 1;

    Student_money(const double& money_new)
    {
        money = money_new;
    }

    void update(const double& time)
    {
        money += (time * speed);
    }
};


class Trigger
{
    Point ld;
    Point ru;

    Trigger(const Point& left, const Point& right)
        : ld(left), ru(right) {}

    

};