#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Enumerations.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <string>
#include <filesystem>
#include <iostream>

#include "../Headers/heads.h"
#include "../Main/Waves.h"

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
    Fl_PNG_Image* img;
    void draw();

public:
    Background();
};

class GraphicCockr : public Fl_Box
{
private:
    Cockroach* cockr;
    Fl_PNG_Image* img;
    int width = 50;
    int height = 50;
    void draw();

public:
    GraphicCockr(Cockroach* cockr);
};

class Text : public Fl_Box
{
private:
    void draw();

public:
    std::string str = "";

    Text(int x, int y);
};

class Graphic
{
private:
    static inline Fl_Window* window;
    static inline std::vector<GraphicCockr*> cockroaches;

    static void Timer_CB(void* userdata);
public:

    static void MakeWindow();
    static Fl_Button* MakeButton(int x, int y, int w, int h, const char* name = "");
    static GraphicCockr* MakeCockr(Cockroach* cockr);
    static Text* MakeText(int x, int y);

    static void ShowRoads(const std::vector<Road>& roads);
    static void ShowCockroaches();
    static void ClearCockroaches();
};