#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Enumerations.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <string>
#include <filesystem>
#include <iostream>

#include "../Headers/heads.h"
#include "../events/events.h"
#include "../Main/Waves.h"
#include "../Weapons/weapons.h"

/// @brief class to draw a road
class Line : public Fl_Box
{
private:
    int x, y, x1, y1;
    void draw();

public:
    Line(int x, int y, int x1, int y1);
};

/// @brief class to draw a background
class Background : public Fl_Box
{
private:
    Fl_PNG_Image *img;
    void draw();

public:
    Background(std::string);
    ~Background();
};

/// @brief class to draw a cockroach
class GraphicCockr : public Fl_Box
{
private:
    Cockroach *cockr;
    Fl_PNG_Image *img;
    bool is_death_img = false;
    int width = 64;
    int height = 64;
    Point prev_direction;
    void draw();

public:
    GraphicCockr(Cockroach *cockr);
    void UpdateImage();
    ~GraphicCockr();
};

/// @brief class to output anyone text
class Text : public Fl_Box
{
private:
    std::string name;
    void draw();

public:
    std::string output = "";

    Text(int x, int y, std::string name = "");
};

#define pb_size_x 50
#define pb_size_y 10

/// @brief class to draw readiness of weapon
class ProgressBar : public Fl_Box
{
private:
    Point pos;
    void draw();

public:
    Fl_Box *progress_box;
    double progress;

    ProgressBar(const Point &pos);
    ~ProgressBar();
};

/// @brief class to draw triggers
class GraphicTrigger : public Fl_Box
{
private:
    const Trigger *trig;
    void draw();

public:
    GraphicTrigger(const Trigger *trig);
};

/// @brief absolute class for drawing weapons
class GraphicWeapon : public Fl_Button
{
protected:
    GraphicWeapon(Point pos, const Trigger *trigger);
    ProgressBar *pb;
    void draw();

private:
    GraphicTrigger *gtrig;

public:
    std::string name;
    GraphicWeapon() = delete;
};

/// @brief struct to UpgradeWeapon()
struct PackUpgrade
{
    Weapon *weapon;
    EnumWeapon type;
    PackUpgrade(Weapon *weapon, EnumWeapon type) : weapon{weapon}, type{type} {}
};

/// @brief class to draw Slapper
class GraphicSlapper : public GraphicWeapon
{
private:
    Fl_PNG_Image *img;
    Slapper *slapper;
    void draw();

public:
    GraphicSlapper(Slapper *slapper);
    ~GraphicSlapper();
};

/// @brief class to draw Dichlorvos
class GraphicDichlorvos : public GraphicWeapon
{
private:
    Fl_PNG_Image *img;
    Dichlorvos *dichlorvos;
    void draw();

public:
    GraphicDichlorvos(Dichlorvos *dichlorvos);
    ~GraphicDichlorvos();
};

/// @brief class to draw Trap
class GraphicTrap : public GraphicWeapon
{
private:
    Fl_PNG_Image *img;
    Trap *trap;
    void draw();

public:
    GraphicTrap(Trap *trap);
    ~GraphicTrap();
};

/// @brief class to draw on FLTK
class Graphic
{
private:
    /// @brief main window
    static inline Fl_Window *window;
    static inline bool is_window;
    /// @brief all cockroaches to output
    static inline std::vector<GraphicCockr *> cockroaches;

    /// @brief function to redraw window by timer
    /// @param userdata something
    static void Timer_CB(void *userdata);

public:
    /// @brief Making classes and add to window
    static void MakeWindow(int w, int h);
    static void MakeBackground(std::string path_to_img);
    static void ClearWindow();
    static Fl_Button *MakeButton(int x, int y, int w, int h, const char *name = "");
    static GraphicCockr *MakeCockr(Cockroach *cockr);
    static Text *MakeText(int x, int y, std::string name = "");
    static ProgressBar *MakeProgressBar(const Point &pos);
    static GraphicTrigger *MakeTrigger(const Trigger *trig);
    static GraphicSlapper *MakeSlapper(Slapper *slapper);
    static GraphicDichlorvos *MakeDichlorvos(Dichlorvos *dichlorvos);
    static GraphicTrap *MakeTrap(Trap *trap);

    static void ShowRoads(const std::vector<Road> &roads);
    static void ShowCockroaches();
    static void Show();
    static void ClearCockroaches();
};