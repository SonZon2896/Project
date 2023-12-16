#pragma once
#include <string>
#include "../Headers/heads.h"

/// @brief Max acceptable amount of alive cockroaches  
#define COCKROACHES_LIMIT 30
/// @brief Amount of money taking for renovation
#define RENOVATION_COAST 500
/// @brief Amount of money taking away in event Evil_Woman
#define EVIL_WOMAN_COAST 1000

/// @brief Game events
class Event
{
private:
    /// @brief scholarship
    static double money_speed;

public:
    /// @brief stipubles
    static double money;

    /// @brief check running cockroaches and do something with scholarship
    /// @param running running cockroaches
    /// @return string to output
    static std::string Evil_Woman(size_t running);

    /// @brief add money
    /// @return string to output
    static std::string Scholarship();

    /// @brief you want to renovation (-money)
    /// @return string to output
    static std::string Renovation();
};
