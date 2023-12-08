#pragma once
#include <vector>
#include "../Headers/heads.h"
#include "../Weapons/weapons.h"

/// @brief Wave of cockroaches
class Wave
{
private:
    std::vector<Cockroach *> cockroaches;
    double time_from_start;
    size_t active_cockr = 0;
    size_t survived;
    bool is_started = false;

public:
    /// @brief variables to make a cockroaches
    std::vector<Road> roads;
    PrototypeEnemy prototype;
    double interval;
    size_t num;

    Wave() = default;
    Wave(const std::vector<Road> &roads);
    /// @brief main functions, which control logic of wave
    void StartWave();
    void MoveWave(double time);
    void EndWave();

    /// @brief Get functions
    size_t GetSurvived() { return survived; }
    size_t GetRunning() { return active_cockr + survived >= num * roads.size() ? active_cockr + survived - num * roads.size() : 0; }
    bool Is_Started() { return is_started; }
};