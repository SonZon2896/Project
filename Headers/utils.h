#pragma once
#include "../Graphic/FLTKgraphic.h"

/// @brief Structure describes the state on the game field
struct FieldState{
    WaveCockroaches wave_cockroaches;
    WaveMouses wave_mouses;
    WaveRadCockroaches wave_rad_cockroaches;

    size_t num_of_wave;
    double timer;
};


/// @brief Structure contains the all game labels
struct Labels{
    Text *events;
    Text *num_wave_text;
    Text *survived;
    Text *fridge_hp;
    Text *stipubles;
    Text *timer_text;
    Text *wasted;
};


/// @brief Structure contains all roads
struct Roads{
    std::vector<Road> cockroach_roads{
        {{700, 250}, {700, 350}, {250, 350}, Fridge::pos},
        {{100, 630}, {250, 630}, {250, 350}, Fridge::pos},
        {{1050, 525}, {550, 525}, {550, 350}, {250, 350}, Fridge::pos},
        {{500, 700}, {600, 700}, {600, 600}, {400, 600}, {400, 350}, {250, 350}, Fridge::pos}
    };

    std::vector<Road> mouse_roads{
        {{500, 700}, {600, 700}, {600, 600}, {400, 600}, {400, 350}, {250, 350}, Fridge::pos}
    };
};