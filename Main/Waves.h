#pragma once
#include <vector>
#include "../Headers/heads.h"

class Wave
{
private:
    std::vector<Cockroach> cockroaches;
    double time_from_start;
    size_t active_cockr = 0;
    size_t survived;
    bool is_started = false;

public:
    std::vector<Road> roads;
    double speed;
    double health;
    double interval;
    size_t num;

    Wave(const std::vector<Road>& roads, size_t num_cockr_on_road = 3., double interval = 0.5, double speed = 1., double cockr_health = 100.);

    void StartWave();
    // доделать изменение хп у холодоса
    void MoveWave(double time);
    size_t GetSurvived() {return survived;}
    bool Is_Started() {return is_started;}
    void EndWave();
};