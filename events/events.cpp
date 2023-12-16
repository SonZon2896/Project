#include "events.h"

std::string Event::Evil_Woman(size_t alive_cockroaches)
{
    if (alive_cockroaches < COCKROACHES_LIMIT)
    {
        money += EVIL_WOMAN_COAST / 2;
        return "Evil woman give you " + std::to_string(EVIL_WOMAN_COAST / 2);
    }
    else
    {
        money -= EVIL_WOMAN_COAST;
        if (money < 0.)
            money = 0.;

        return "Evil woman takes " + std::to_string(EVIL_WOMAN_COAST);
    }
}

std::string Event::Scholarship()
{
    money += money_speed;
    return "Scholarship Enrollment +" + std::to_string(money_speed);
}

std::string Event::Renovation()
{
    money -= RENOVATION_COAST;
    if (money < 0)
        money = 0;

    return "You decided to arrange a renovation -" + std::to_string(RENOVATION_COAST);
}