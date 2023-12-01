#include "events.h"

std::string Event::Evil_Woman(size_t running)
{
    if (running < 30)
    {
        std::string good = "Good boys, i will even not kill you))";
        return good;
    }
    else
    {
        money -= 1000.;
        if (money < 0.)
            money = 0.;
        std::string bad = "Bad boys, you should be ready to my attack";
        return bad;
    }
}

std::string Event::Scholarship()
{
    money += money_speed;
    return "Scholarship Enrollment +" + std::to_string(money_speed);
}

std::string Event::Renovation()
{
    double cost = 100;
    money -= cost;
    if (money < 0)
        money = 0;
    return "You decided to arrange a renovation -" + std::to_string(cost);
}