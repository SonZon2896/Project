#pragma once
#include <vector>
#include "../Headers/heads.h"
#include "../Weapons/weapons.h"

/// @brief Abstract Class
class Wave
{
protected:
    Wave();
    
    double time_from_start;
    double interval;
    size_t num;
    size_t active_enemy;
    size_t survived;
    bool is_started = false;

private:
    static inline std::vector<Wave *> all_waves;

public:
    std::vector<Road> roads;

    // Wave() = delete;
    ~Wave();

    /// @brief main functions, which control logic of wave
    virtual void Start(size_t num_of_wave) = 0;
    virtual void Action(double time) = 0;
    virtual void End() = 0;

    static void StartAll(size_t num_of_wave);
    static void ActionAll(double time);
    static void EndAll();

    /// @brief Get functions
    size_t GetSurvived() { return survived; }
    size_t GetRunning() { return active_enemy + survived >= num * roads.size() ? active_enemy + survived - num * roads.size() : 0; }
    bool IsStarted() { return is_started; }
    static size_t GetAllSurvived();
    static size_t GetAllRunning();
    static bool IsAllStarted();
    static auto GetAll() {return all_waves;}
};

class WaveCockroaches : public Wave
{
private:
    std::vector<Cockroach *> cockroaches;
    PrototypeEnemy prototype;

public:
    WaveCockroaches() = default;

    void Start(size_t num_of_wave) final;
    void Action(double time) final;
    void End() final;
};

class WaveMouses : public Wave
{
private:
    std::vector<Mouse *> mouses;
    PrototypeEnemy prototype;

public:
    WaveMouses() = default;

    void Start(size_t num_of_wave) final;
    void Action(double time) final;
    void End() final;
};