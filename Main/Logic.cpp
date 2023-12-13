#include <iostream>

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

FieldState field_state;
Labels labels;
Roads roads;

Fl_Button *btn_start_wave;
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
    Wave::EndAll();
    ++field_state.num_of_wave;
    Event::Scholarship();
}

struct PackWeapon
{
    Point pos;
    Direction direction;
    EnumWeapon type;
    PackWeapon(Point pos, Direction direction, EnumWeapon type) : pos{pos}, direction{direction}, type{type} {}
};

void MakeWeapon(Fl_Widget *w, void *p)
{
    auto unpack = (PackWeapon *)p;
    if (unpack->type == EnumWeapon::slapper)
    {
        if (Event::money < SLAPPER_COAST)
            return;
        Event::money -= SLAPPER_COAST;
        w->hide();
        auto slapper = new Slapper(unpack->pos, unpack->direction);
        field_state.slappers.push_back(Graphic::MakeSlapper(slapper));
    }
    else if (unpack->type == EnumWeapon::dichlorvos)
    {
        if (Event::money < DICHLORVOS_COAST)
            return;
        Event::money -= DICHLORVOS_COAST;
        w->hide();
        auto dichlorvos = new Dichlorvos(unpack->pos, unpack->direction);
        field_state.dichlorvoses.push_back(Graphic::MakeDichlorvos(dichlorvos));
    }
    else if (unpack->type == EnumWeapon::trap)
    {
        if (Event::money < TRAP_COAST)
            return;
        Event::money -= TRAP_COAST;
        w->hide();
        auto trap = new Trap(unpack->pos, unpack->direction);
        field_state.traps.push_back(Graphic::MakeTrap(trap));
    }
}

// Main ===================================================================================

void GameManager::Start()
{
    field_state.timer = 0.;
    Fridge::health = FRIDGE_START_HEALTH;
    Event::money = START_MONEY;

    field_state.wave_cockroaches.roads = roads.cockroach_roads;
    field_state.wave_mouses.roads = roads.mouse_roads;

    field_state.num_of_wave = 0;
    Graphic::MakeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    Graphic::MakeBackground(PATH_TO_MAIN_FIELD);
    Graphic::Show();
    Graphic::ShowRoads(roads.cockroach_roads);

    btn_start_wave = Graphic::MakeButton(0, 720, 100, 50, "Start wave");
    btn_start_wave->callback([](Fl_Widget *w){
                                StartWave(); 
                            });

    btn_close_game = Graphic::MakeButton(1180, 0, 100, 50, "Quit game");
    btn_close_game->callback([](Fl_Widget *w){
                                GameManager::QuitGame();
                            });

    for (size_t i = BUTTON_MAKE_WEAPON_SIZE / 2; i <= 1280 - BUTTON_MAKE_WEAPON_SIZE / 2; i += BUTTON_MAKE_WEAPON_SIZE)
        for (size_t j = BUTTON_MAKE_WEAPON_SIZE / 2; j <= 720 - BUTTON_MAKE_WEAPON_SIZE / 2; j += BUTTON_MAKE_WEAPON_SIZE)
            Graphic::MakeBTNWeapon({i, j});

    
    labels.events = Graphic::MakeText(1000, 720, "output");
    labels.num_wave_text = Graphic::MakeText(100, 720, "wave");
    labels.survived = Graphic::MakeText(200, 720, "survived");
    labels.stipubles = Graphic::MakeText(300, 720, "stipubles");
    labels.timer_text = Graphic::MakeText(400, 720, "timer");
    labels.wave_started = Graphic::MakeText(500, 720, "Started?");
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

    labels.num_wave_text->output = std::to_string(field_state.num_of_wave);
    labels.events->output = Event::Evil_Woman(Wave::GetAllRunning());
    labels.survived->output = std::to_string(Wave::GetAllSurvived());
    labels.wave_started->output = Wave::IsAllStarted() ? "Started" : "Not Started";
    labels.fridge_hp->output = std::to_string((int)Fridge::health);
    labels.stipubles->output = std::to_string((int)Event::money);
    labels.timer_text->output = std::to_string((int)(WAVE_DELAY - field_state.timer + 0.99));
}

void GameManager::End()
{
    Graphic::ClearWindow();
    Graphic::MakeText(590, 335, "WASTED");
    auto btn_restart = Graphic::MakeButton(590, 385, 100, 50, "RESTART");
    btn_restart->callback([](Fl_Widget *w){w->hide(); StartGame();});
}