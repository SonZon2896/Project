#pragma once
#include <string>
#include "../Headers/heads.h"

/// @brief Game events
class Event{
private:
    /// @brief scholarship
    static inline double money_speed = 100;

public:
    /// @brief stipubles
    static inline double money = 0;

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

