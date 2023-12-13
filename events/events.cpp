#include "events.h"

/// @brief Max acceptable amount of alive cockroaches  
#define COCKROACHES_LIMIT 30

/// @brief Amount of money taking away in event Evil_Woman
#define TAKING_MONEY 1000.

// /// @brief Coast for event Renovation
// #define RENOVATION_COAST 100


/// @brief If amount of alive cockroaches excced the limit, player is fining 
/// @param running_cockroaches 
/// @return Response status string 
std::string Event::Evil_Woman(size_t alive_cockroaches)
{
    if (alive_cockroaches < COCKROACHES_LIMIT)
    {
        std::string good = "Good boys, i will even not kill you))";
        return good;
    }
    else
    {
        money -= TAKING_MONEY;
        if (money < 0.)
            money = 0.;

        std::string bad = "Bad boys, you should be ready to my attack";
        return bad;
    }
}

/// @brief Player gets money before te next wave
/// @return Status string
std::string Event::Scholarship()
{
    money += money_speed;
    return "Scholarship Enrollment +" + std::to_string(money_speed);
}

// /// @brief 
// /// @return 
// std::string Event::Renovation()
// {
//     money -= RENOVATION_COAST;
//     if (money < 0)
//         money = 0;

//     return "You decided to arrange a renovation -" + std::to_string(RENOVATION_COAST);
// }