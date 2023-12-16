#include <iostream>
#include <ctime>

#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Weapons/weapons.h"
#include "../events/events.h"
#include "../Headers/utils.h"



/// @brief Start money
#define START_MONEY 1500.
/// @brief Speed of money coming
#define MONEY_SPEED 1500
/// @brief Coast of slapper
#define SLAPPER_COAST 400
/// @brief Coast of dichlorvos
#define DICHLORVOS_COAST 1000
/// @brief Coast of trap
#define TRAP_COAST 150

/// @brief Position of the fridge
#define FRIDGE_POS {250, 210}
/// @brief Start hp of the Fridge 
#define FRIDGE_START_HEALTH 100

/// @brief Time to start new wave
#define WAVE_DELAY 10.

#define PATH_IMAGE_BUTTON_START_WAVE "./PNG/new_wave.png"
#define PATH_IMAGE_BUTTON_QUIT_GAME "./PNG/quit_game_button.png"
#define PATH_IMAGE_WASTED_SCREEN "./PNG/wasted_screen.png"
#define PATH_IMAGE_BUTTON_RESTART "./PNG/restart_button.png"
#define PATH_IMAGE_BUTTON_QUIT "./PNG/quit_button.png"

/// @brief Default window width
#define WINDOW_WIDTH 1280
/// @brief Default window height
#define WINDOW_HEIGHT 770

/// @brief default path to main field image
#define PATH_TO_MAIN_FIELD "./PNG/main_field_px.png"


// Variables ==============================================================================

Point Fridge::pos(FRIDGE_POS);
double Fridge::health;
double Event::money_speed{MONEY_SPEED};
double Event::money;

bool is_event_on_wave;
FieldState field_state;
Labels labels;
Roads roads;

GraphicButton *btn_start_wave;
GraphicButton *btn_close_game;

// Functions ==============================================================================

void StartWave()
{
    if (!Wave::IsAllStarted())
    {
        auto all_waves = Wave::GetAll();
        for (auto wave : all_waves)
            wave->Start(field_state.num_of_wave);
        Graphic::ShowEnemies();
        field_state.timer = 0.;
    }
}

void NextWave()
{
    is_event_on_wave = false;
    Wave::EndAll();
    ++field_state.num_of_wave;
    Event::Scholarship();
}

// Main ===================================================================================

void GameManager::Start()
{
    srand(time(0));
    is_event_on_wave = false;

    field_state.timer = 0.;
    Fridge::health = FRIDGE_START_HEALTH;
    Event::money = START_MONEY;

    field_state.wave_cockroaches.roads = roads.cockroach_roads;
    field_state.wave_mouses.roads = roads.mouse_roads;

    field_state.num_of_wave = 0;
    Graphic::MakeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    Graphic::ClearWindow();
    Graphic::MakeBackground(PATH_TO_MAIN_FIELD);
    Graphic::Show();
    Graphic::ShowRoads(roads.cockroach_roads);

    btn_start_wave = Graphic::MakeButton(0, 720, 100, 50, "Start wave");
    btn_start_wave->callback([](Fl_Widget *w){
                                StartWave(); 
                            });
    btn_start_wave->image = new Fl_PNG_Image(PATH_IMAGE_BUTTON_START_WAVE);

    btn_close_game = Graphic::MakeButton(1230, 720, 50, 50, "Quit");
    btn_close_game->callback([](Fl_Widget *w){
                                GameManager::QuitGame();
                            });
    btn_close_game->image = new Fl_PNG_Image(PATH_IMAGE_BUTTON_QUIT_GAME);

    for (int i = BUTTON_MAKE_WEAPON_SIZE / 2; i <= 1280 - BUTTON_MAKE_WEAPON_SIZE / 2; i += BUTTON_MAKE_WEAPON_SIZE)
        for (int j = BUTTON_MAKE_WEAPON_SIZE / 2; j <= 720 - BUTTON_MAKE_WEAPON_SIZE / 2; j += BUTTON_MAKE_WEAPON_SIZE)
            Graphic::MakeBTNWeapon({i, j});

    
    labels.events = Graphic::MakeText(1000, 720, "output");
    labels.num_wave_text = Graphic::MakeText(100, 720, "wave");
    labels.survived = Graphic::MakeText(200, 720, "survived");
    labels.stipubles = Graphic::MakeText(300, 720, "stipubles");
    labels.timer_text = Graphic::MakeText(400, 720, "timer");
    labels.fridge_hp = Graphic::MakeText(125, 50, "fridge hp");
}

void GameManager::FixedUpdate()
{
    if (Wave::IsAllStarted())
    {
        Wave::ActionAll(time::fixed);
        if (Wave::GetAllSurvived() <= 0)
            NextWave();
    }
    for (auto enemy : Enemy::GetAll())
        enemy->CheckTrigger();
    for (auto weapon : Weapon::GetAll())
        weapon->Action(time::fixed);
    if (Fridge::health <= 0)
    {
        auto all_waves = Wave::GetAll();
        Wave::EndAll();
        EndGame(GAMEOVER_WASTED);
    }
}

void GameManager::Update()
{
    if (!Wave::IsAllStarted() && (field_state.timer += time::DeltaTime()) > WAVE_DELAY)
    {
        StartWave();
        field_state.timer = 0.;
    }

    if (Wave::IsAllStarted() && !is_event_on_wave && (rand() % 1000000 > 999997))
    {
        is_event_on_wave = true;
        size_t num_event = rand() % 2;
        switch (num_event)
        {
        case 0:
            labels.events->output = Event::Evil_Woman(Wave::GetAllRunning());
            break;
        case 1:
            labels.events->output = Event::Renovation();
            break;
        }
        std::cout << "event is " << std::to_string(num_event) << std::endl;
    }
    labels.num_wave_text->output = std::to_string(field_state.num_of_wave);
    labels.survived->output = std::to_string(Wave::GetAllSurvived());
    labels.fridge_hp->output = std::to_string((int)Fridge::health);
    labels.stipubles->output = std::to_string((int)Event::money);
    labels.timer_text->output = std::to_string((int)(WAVE_DELAY - field_state.timer + 0.99));
}

void GameManager::End()
{
    Graphic::ClearWindow();
    Graphic::MakeBackground(PATH_IMAGE_WASTED_SCREEN);

    GraphicButton* btn_restart = Graphic::MakeButton(590, 285, 256, 128, "");
    btn_restart->callback([](Fl_Widget *w){w->hide(); StartGame();});
    btn_restart->image = new Fl_PNG_Image(PATH_IMAGE_BUTTON_RESTART);

    GraphicButton* btn_quit = Graphic::MakeButton(590, 423, 256, 128, "");
    btn_quit->callback([](Fl_Widget *w){GameManager::QuitGame();});
    btn_quit->image = new Fl_PNG_Image(PATH_IMAGE_BUTTON_QUIT);
}