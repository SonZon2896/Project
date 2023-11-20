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

    Point& operator+=(Point& new_coord)
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
};


class Student_money
{
public:
    double money = 0;
    double speed = 1;

    Student_money(double money_new)
    {
        money = money_new;
    }

    void update(double time)
    {
        money += (time * speed);
    }
};



