#include <iostream>

#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Graphic/FLTKgraphic.h"
#include "../Weapons/weapons.h"
#include "../events/events.h"

// Variables ==============================================================================

Point Fridge::pos{250, 210};
double Fridge::health;
double Event::money;
double Event::money_speed{1500};
constexpr bool Mark_Lox = false;  // 1 december
const bool Artem_Lox = true; // 2 december
constexpr bool Vanya_Lox = true; // 11 decenmber
std::vector<Road> roads{
    {{700., 250.}, {700., 350.}, {250., 350.}, Fridge::pos},
    {{100., 630.}, {250., 630.}, {250., 350.}, Fridge::pos},
    {{1050., 525.}, {550., 525.}, {550., 350.}, {250., 350.}, Fridge::pos},
    {{500., 700.}, {600., 700.}, {600., 600.}, {400., 600.}, {400., 350.}, {250., 350.}, Fridge::pos}};
std::vector<Road> mouse_roads{{{500., 700.}, {600., 700.}, {600., 600.}, {400., 600.}, {400., 350.}, {250., 350.}, Fridge::pos}};

WaveCockroaches wave_cockroaches;
WaveMouses wave_mouses;
size_t num_of_wave;

Fl_Button *btn_start_wave;
std::vector<Fl_Button *> btns_make_slapper;
std::vector<Fl_Button *> btns_make_dichlorvos;
std::vector<Fl_Button *> btns_make_trap;

Text *events;
Text *num_wave_text;
Text *survived;
Text *wave_started;
Text *fridge_hp;
Text *stipubles;
Text *timer_text;
Text *wasted;

std::vector<GraphicSlapper *> slappers;
std::vector<GraphicDichlorvos *> dichlorvoses;
std::vector<GraphicTrap *> traps;

double timer;
double timer_to_start_wave = 10.;

// Functions ==============================================================================

void StartWave()
{
    if (!Wave::IsAllStarted())
    {
        auto all_waves = Wave::GetAll();
        for (auto wave : all_waves)
            wave->Start(num_of_wave);
        Graphic::ShowEnemies();
        timer = 0.;
    }
}

void NextWave()
{
    Wave::EndAll();
    ++num_of_wave;
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
        if (Event::money < 100)
            return;
        Event::money -= 400;
        w->hide();
        auto slapper = new Slapper(unpack->pos, unpack->direction);
        slappers.push_back(Graphic::MakeSlapper(slapper));
    }
    else if (unpack->type == EnumWeapon::dichlorvos)
    {
        if (Event::money < 400)
            return;
        Event::money -= 1000;
        w->hide();
        auto dichlorvos = new Dichlorvos(unpack->pos, unpack->direction);
        dichlorvoses.push_back(Graphic::MakeDichlorvos(dichlorvos));
    }
    else if (unpack->type == EnumWeapon::trap)
    {
        if (Event::money < 150)
            return;
        Event::money -= 150;
        w->hide();
        auto trap = new Trap(unpack->pos, unpack->direction);
        traps.push_back(Graphic::MakeTrap(trap));
    }
}

// Main ===================================================================================

void GameManager::Start()
{
    timer = 0.;
    Fridge::health = 100;
    Event::money = 1500.;

    wave_cockroaches.roads = roads;
    wave_mouses.roads = mouse_roads;

    num_of_wave = 0;
    Graphic::MakeWindow(1280, 770);
    Graphic::MakeBackground("./PNG/main_field_px.png");
    Graphic::Show();
    Graphic::ShowRoads(roads);

    btn_start_wave = Graphic::MakeButton(0, 720, 100, 50, "start wave");
    btn_start_wave->callback([](Fl_Widget *w)
                             { StartWave(); });

    for (size_t i = BUTTON_MAKE_WEAPON_SIZE / 2; i <= 1280 - BUTTON_MAKE_WEAPON_SIZE / 2; i += BUTTON_MAKE_WEAPON_SIZE)
        for (size_t j = BUTTON_MAKE_WEAPON_SIZE / 2; j <= 720 - BUTTON_MAKE_WEAPON_SIZE / 2; j += BUTTON_MAKE_WEAPON_SIZE)
            Graphic::MakeBTNWeapon({i, j});

    
    events = Graphic::MakeText(1000, 720, "output");
    num_wave_text = Graphic::MakeText(100, 720, "wave");
    survived = Graphic::MakeText(200, 720, "survived");
    stipubles = Graphic::MakeText(300, 720, "stipubles");
    timer_text = Graphic::MakeText(400, 720, "timer");
    wave_started = Graphic::MakeText(500, 720, "Started?");
    fridge_hp = Graphic::MakeText(125, 50, "fridge hp");
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
        EndGame();
    }
}

void GameManager::Update()
{
    if (!Wave::IsAllStarted() && (timer += time::DeltaTime()) > timer_to_start_wave)
    {
        StartWave();
        timer = 0.;
    }

    num_wave_text->output = std::to_string(num_of_wave);
    events->output = Event::Evil_Woman(Wave::GetAllRunning());
    survived->output = std::to_string(Wave::GetAllSurvived());
    wave_started->output = Wave::IsAllStarted() ? "Started" : "Not Started";
    fridge_hp->output = std::to_string((int)Fridge::health);
    stipubles->output = std::to_string((int)Event::money);
    timer_text->output = std::to_string((int)(timer_to_start_wave - timer + 0.99));
}

void GameManager::End()
{
    Graphic::ClearWindow();
    Graphic::MakeText(590, 335, "WASTED");
    auto btn_restart = Graphic::MakeButton(590, 385, 100, 50, "RESTART");
    btn_restart->callback([](Fl_Widget *w){w->hide(); StartGame();});
}