#pragma once
#include <vector>
#include "../Headers/heads.h"

class Wave
{
private:
    const std::vector<std::vector<Point>>& roads;
    std::vector<Cockroach> cockroaches;
    double time_from_start;
    size_t active_cockr = 0;
    size_t survived;

    double speed;
    double health;
    double interval;
    size_t num;

public:
    Wave(const std::vector<std::vector<Point>>& roads, size_t num_cockr_on_road, double speed, double cockr_health, double interval);

    void StartWave();
    // доделать изменение хп у холодоса
    void MoveWave(double time);
    size_t GetSurvived() {return survived;}
};