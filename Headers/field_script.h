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
    Point left_down;
    Point right_up;

    Trigger (Point&& left, Point&& right)
    {
        left_down = left;
        right_up = right;
    }

    

}



