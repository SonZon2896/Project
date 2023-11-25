#include "../Headers/heads.h"
#include "Waves.h"
#include "../Weapons/weapons.h"
#include <chrono>
#include <iostream>

class Time
{
private:
    static inline auto prev{std::chrono::system_clock::now()};
    static inline auto now{std::chrono::system_clock::now()};

public:
    static inline double fixed{0.2};

    Time() = delete;
    static double DeltaTime();
    static void Update();
};

class GameManager
{
private:
    Wave wave;
    size_t num_of_wave = 0;

    std::vector<Road> roads;
    void MakeWave();
public:
    GameManager() = delete;
    GameManager(std::vector<Road> roads);
    void FixedUpdate();
    void Update();
};
