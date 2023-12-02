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
#include "../Main/Waves.h"
#include "../Weapons/weapons.h"

class Line : public Fl_Box
{
private:
    int x, y, x1, y1;
    void draw();

public:
    Line(int x, int y, int x1, int y1);
};

class Background : public Fl_Box
{
private:
    Fl_PNG_Image *img;
    void draw();

public:
    Background();
};

class GraphicCockr : public Fl_Box
{
private:
    Cockroach *cockr;
    Fl_PNG_Image *img;
    int width = 64;
    int height = 64;
    void draw();

public:
    GraphicCockr(Cockroach *cockr);
};

class Text : public Fl_Box
{
private:
    std::string name;
    void draw();

public:
    std::string output = "";

    Text(int x, int y, std::string name = "");
};

class ProgressBar : public Fl_Box
{
private:
    Point pos;
    Point size;
    void draw();

public:
    Fl_Box *progress_box;
    double progress;

    ProgressBar(const Point &pos);
};

class GraphicTrigger : public Fl_Box
{
private:
    const Trigger *trig;
    void draw();

public:
    GraphicTrigger(const Trigger *trig);
};

class GraphicSlapper : public Fl_Box
{
private:
    const Slapper *slapper;
    ProgressBar *pb;
    GraphicTrigger *gtrig;
    void draw();

public:
    GraphicSlapper(const Slapper *slapper);
};

class GraphicDichlorvos : public Fl_Box
{
private:
    const Dichlorvos *dichlorvos;
    ProgressBar *pb;
    GraphicTrigger *gtrig;
    void draw();

public:
    GraphicDichlorvos(const Dichlorvos *dichlorvos);
};

class GraphicTrap : public Fl_Box
{
private:
    const Trap *trap;
    ProgressBar *pb;
    GraphicTrigger *gtrig;
    void draw();

public:
    GraphicTrap(const Trap *trap);
};

/// @brief class to draw on FLTK
class Graphic
{
private:
    /// @brief main window
    static inline Fl_Window *window;
    /// @brief all cockroaches to output
    static inline std::vector<GraphicCockr *> cockroaches;

    /// @brief function to redraw window by timer
    /// @param userdata something
    static void Timer_CB(void *userdata);

public:
    /// @brief Making classes and add to window
    static void MakeWindow(int w, int h);
    static Fl_Button *MakeButton(int x, int y, int w, int h, const char *name = "");
    static GraphicCockr *MakeCockr(Cockroach *cockr);
    static Text *MakeText(int x, int y, std::string name = "");
    static ProgressBar *MakeProgressBar(const Point &pos);
    static GraphicTrigger *MakeTrigger(const Trigger *trig);
    static GraphicSlapper *MakeSlapper(const Slapper *slapper);
    static GraphicDichlorvos *MakeDichlorvos(const Dichlorvos *dichlorvos);
    static GraphicTrap *MakeTrap(const Trap *trap);

    static void ShowRoads(const std::vector<Road> &roads);
    static void ShowCockroaches();
    static void ClearCockroaches();
};