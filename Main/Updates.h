#include "../Headers/heads.h"
#include "Waves.h"
#include "../Weapons/weapons.h"
#include <chrono>
#include <iostream>
#include <thread>

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
    static inline Wave wave;
    static inline size_t num_of_wave = 0;

    static inline std::vector<Road> roads;
    static void MakeWave();

    static void FixedUpdate();
    static void Update();

    static inline std::thread fix_thr;
    static inline std::thread upd_thr;

    static void StartFixedUpdate();
    static void StartUpdate();

    static inline bool is_started = false;

public:
    GameManager() = delete;

    static void StartGame();
    static void EndGame();
};
