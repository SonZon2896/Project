#include <iostream>

#include "GameManager.h"
#include "Waves.h"
#include "../Headers/heads.h"
#include "../Graphic/FLTKgraphic.h"
#include "../Weapons/weapons.h"
#include "../events/events.h"

// Variables ==============================================================================

Point Fridge::pos{250, 210};
double Fridge::health{100.};
double Event::money{1000.};
double Event::money_speed{1500.};
const bool Mark_Lox = true; // 1 december
const bool Artem_Lox = true; // 2 december
std::vector<Road> roads{
    {{700., 250.}, {700., 350.}, {250., 350.}, Fridge::pos},
    {{100., 630.}, {250., 630.}, {250., 350.}, Fridge::pos},
    {{1050., 525.}, {550., 525.}, {550., 350.}, {250., 350.}, Fridge::pos},
    {{500., 700.}, {600., 700.}, {600., 600.}, {400., 600.}, {400., 350.}, {250., 350.}, Fridge::pos}};
Wave wave;
size_t num_of_wave;

Fl_Button *btn_start_wave;
std::vector<Fl_Button *> btns_make_slapper;
std::vector<Fl_Button *> btns_make_dichlorvos;
std::vector<Fl_Button *> btns_make_trap;

Text *events;
Text *num_wave_text;
Text *survived;
Text *fridge_hp;
Text *stipubles;
Text *timer_text;

std::vector<GraphicSlapper *> slappers;
std::vector<GraphicDichlorvos *> dichlorvoses;
std::vector<GraphicTrap *> traps;

double timer = 0.;
double timer_to_start_wave = 10.;

// Functions ==============================================================================

void MakeWave()
{
    if (wave.Is_Started())
        throw std::runtime_error("Making wave, when it started");

    ++num_of_wave;

    wave.num = 3 + 2 * (num_of_wave / 2);
    wave.health = 100. + num_of_wave * 20;
    wave.speed = 75. + num_of_wave * 2;
    wave.interval = 0.2 * (1 - num_of_wave / (num_of_wave + 10));
}

void StartWave(Fl_Widget *w)
{
    if (!wave.Is_Started())
    {
        wave.StartWave();
        Graphic::ShowCockroaches();
        timer = 0.;
    }
}

void MakeSlapper(Fl_Widget *w, void *p)
{
    if (Event::money < 100)
        return;
    Event::money -= 100;
    w->hide();
    Point pos = *(Point *)p;
    auto slapper = new Slapper(pos);
    slappers.push_back(Graphic::MakeSlapper(slapper));
    delete p;
}

struct DichlInp
{
    Point pos;
    bool is_right = false;
    DichlInp(Point pos, bool is_right = false)
        : pos{pos}, is_right{is_right} {}
};

void MakeDichlorvos(Fl_Widget *w, void *p)
{
    if (Event::money < 400)
        return;
    Event::money -= 400;
    w->hide();
    auto data = (DichlInp *)p;
    auto dichlorvos = new Dichlorvos(data->pos, data->is_right);
    dichlorvoses.push_back(Graphic::MakeDichlorvos(dichlorvos));
    delete data;
}

void MakeTrap(Fl_Widget *w, void *p)
{
    if (Event::money < 150)
        return;
    Event::money -= 150;
    w->hide();
    Point pos = *(Point *)p;
    auto trap = new Trap(pos);
    traps.push_back(Graphic::MakeTrap(trap));
    delete p;
}

// Main ===================================================================================

void GameManager::Start()
{
    wave = Wave(roads);
    num_of_wave = 0;
    Graphic::MakeWindow(1280, 770);
    Graphic::ShowRoads(roads);

    btn_start_wave = Graphic::MakeButton(0, 720, 100, 50, "start wave");
    btn_start_wave->callback(StartWave);

    btns_make_slapper.reserve(3);
    btns_make_slapper.push_back(Graphic::MakeButton(200, 500, 100, 50, "make slapper \n 100 sb"));
    btns_make_slapper[btns_make_slapper.size() - 1]->callback(MakeSlapper, (void *)(new Point{200 + 50, 500 + (-30)}));
    btns_make_slapper.push_back(Graphic::MakeButton(700, 500, 100, 50, "make slapper \n 100 sb"));
    btns_make_slapper[btns_make_slapper.size() - 1]->callback(MakeSlapper, (void *)(new Point{700 + 50, 500 + (-30)}));
    btns_make_slapper.push_back(Graphic::MakeButton(500, 400, 100, 50, "make slapper \n 100 sb"));
    btns_make_slapper[btns_make_slapper.size() - 1]->callback(MakeSlapper, (void *)(new Point{500 + 50, 400 + (-30)}));

    btns_make_dichlorvos.reserve(2);
    btns_make_dichlorvos.push_back(Graphic::MakeButton(150, 300, 100, 50, "make dichlorvos \n 400 sb"));
    btns_make_dichlorvos[btns_make_dichlorvos.size() - 1]->callback(MakeDichlorvos, (void *)(new DichlInp({150 + 50, 300 + 50}, true)));
    btns_make_dichlorvos.push_back(Graphic::MakeButton(350, 300, 100, 50, "make dichlorvos \n 400 sb"));
    btns_make_dichlorvos[btns_make_dichlorvos.size() - 1]->callback(MakeDichlorvos, (void *)(new DichlInp(Point{350 + 50, 300 + 20})));

    btns_make_trap.reserve(2);
    btns_make_trap.push_back(Graphic::MakeButton(900, 500, 100, 50, "make trap \n 150 sb"));
    btns_make_trap[btns_make_trap.size() - 1]->callback(MakeTrap, (void *)(new Point{900 + 50, 500 + 0}));
    btns_make_trap.push_back(Graphic::MakeButton(200, 350, 100, 50, "make trap \n 150 sb"));
    btns_make_trap[btns_make_trap.size() - 1]->callback(MakeTrap, (void *)(new Point{200 + 50, 350 + 50}));

    events = Graphic::MakeText(1000, 720, "output");
    num_wave_text = Graphic::MakeText(100, 720, "wave");
    survived = Graphic::MakeText(200, 720, "survived");
    stipubles = Graphic::MakeText(300, 720, "stipubles");
    timer_text = Graphic::MakeText(400, 720, "timer");
    fridge_hp = Graphic::MakeText(125, 50, "fridge hp");

    MakeWave();
}

void GameManager::FixedUpdate()
{
    if (wave.Is_Started())
    {
        wave.MoveWave(time::fixed);
        if (wave.GetSurvived() <= 0)
        {
            wave.EndWave();
            Graphic::ClearCockroaches();
            Event::Scholarship();
            MakeWave();
        }
    }
    if (Fridge::health <= 0)
    {
        Graphic::MakeText(590, 335, "WASTED");
        EndGame();
    }
    for (auto weapon : Weapon::GetAll())
        weapon->Action(time::fixed);
}

void GameManager::Update()
{
    if (!wave.Is_Started() && (timer += time::DeltaTime()) > timer_to_start_wave)
    {
        wave.StartWave();
        Graphic::ShowCockroaches();
        timer = 0.;
    }

    num_wave_text->output = std::to_string(num_of_wave);
    events->output = Event::Evil_Woman(wave.GetRunning());
    survived->output = std::to_string(wave.GetSurvived());
    fridge_hp->output = std::to_string((int)Fridge::health);
    stipubles->output = std::to_string((int)Event::money);
    timer_text->output = std::to_string((int)(timer_to_start_wave - timer + 0.99));
}