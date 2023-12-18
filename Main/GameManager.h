#pragma once
#include "../Headers/heads.h"
#include "../Weapons/weapons.h"
#include "../Graphic/FLTKgraphic.h"
#include "Waves.h"
#include <chrono>
#include <iostream>
#include <thread>

/// @brief class to check time for GameManager
class time
{
private:
    static inline auto prev{std::chrono::system_clock::now()};
    static inline auto now{std::chrono::system_clock::now()};

public:
    static inline double fixed{0.02};

    time() = delete;
    /// @brief function to GameManager::Update()
    /// @return time past last update
    static double DeltaTime();
    /// @brief update time for DeltaTime()
    static void Update();
};

/// @brief main class to logic
class GameManager
{
private:
    /// @brief Do something on starting game
    static void Start();
    /// @brief Do something every time by time::fixed
    static void FixedUpdate();
    /// @brief Do something like a cycle for
    static void Update();
    /// @brief function to delete variables, when game is ended
    static void End();

    /// @brief threads, which started FixedUpdate and Update
    static inline std::thread fix_thr;
    static inline std::thread upd_thr;

    /// @brief start threads
    static void StartFixedUpdate();
    static void StartUpdate();

    static inline volatile bool is_started = false;
public:
    GameManager() = delete;

    static void StartGame();
    static void EndGame(GameOverStatus);
    static void QuitGame();
};
