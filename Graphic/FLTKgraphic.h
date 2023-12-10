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

#define ENEMY_SIZE_X 64
#define ENEMY_SIZE_Y 64

/// @brief class to draw a cockroach
class GraphicEnemy : public Fl_Box
{
private:
    Enemy *enemy;
    Fl_Image *img_now;
    Point prev_direction;
    void draw();

public:
    Fl_Image *img_up;
    Fl_Image *img_down;
    Fl_Image *img_left;
    Fl_Image *img_right;
    Fl_Image *img_death;

    GraphicEnemy(Enemy *enemy, std::string path_to_image);
    void UpdateImage();
    ~GraphicEnemy();
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

#define BUTTON_MAKE_WEAPON_SIZE 64

class ButtonMakeWeapon : public Fl_Button
{
private:
    Point pos;

    EnumWeapon type;
    Fl_Button *btn_make_slapper;
    Fl_Button *btn_make_dichlorvos;
    Fl_Button *btn_make_trap;

    Direction direction;
    Fl_Button *btn_dir_up;
    Fl_Button *btn_dir_down;
    Fl_Button *btn_dir_left;
    Fl_Button *btn_dir_right;

    Fl_Button *btn_accept;
    Fl_Button *btn_back;
    void StageZero();
    void StageWeapon();
    void StageDirection();
    void StageAccept();
    void MakeWeapon();

public:
    friend void StageWeaponCB(Fl_Widget *, void *);
    friend void StageDirectionCB(Fl_Widget *, void *);
    friend void StageZeroCB(Fl_Widget *, void *);
    friend void StageAcceptCB(Fl_Widget *, void *);
    friend void MakeWeaponCB(Fl_Widget *, void *);

    ButtonMakeWeapon() = delete;
    ButtonMakeWeapon(Point pos);
};

/// @brief class to draw on FLTK
class Graphic
{
private:
    /// @brief main window
    static inline Fl_Window *window;
    static inline bool is_window;
    /// @brief all cockroaches to output
    static inline std::vector<GraphicEnemy *> cockroaches;
    static inline std::vector<GraphicEnemy *> mouses;

    /// @brief function to redraw window by timer
    /// @param userdata something
    static void Timer_CB(void *userdata);

public:
    /// @brief Making classes and add to window
    static void MakeWindow(int w, int h);
    static void MakeBackground(std::string path_to_img);
    static void ClearWindow();
    static Fl_Button *MakeButton(int x, int y, int w, int h, const char *name = "");
    static GraphicEnemy *MakeCockr(Cockroach *cockr);
    static GraphicEnemy *MakeMouse(Mouse *mouse);
    static Text *MakeText(int x, int y, std::string name = "");
    static ProgressBar *MakeProgressBar(const Point &pos);
    static GraphicTrigger *MakeTrigger(const Trigger *trig);
    static GraphicSlapper *MakeSlapper(Slapper *slapper);
    static GraphicDichlorvos *MakeDichlorvos(Dichlorvos *dichlorvos);
    static GraphicTrap *MakeTrap(Trap *trap);
    static ButtonMakeWeapon *MakeBTNWeapon(Point pos);

    static void ShowRoads(const std::vector<Road> &roads);
    static void ShowEnemies();
    static void Show();
};