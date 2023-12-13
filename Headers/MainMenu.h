#pragma once
#include "../lib/fltk/FL/Fl.H"
#include "../lib/fltk/FL/Fl_Button.H"
#include "../lib/fltk/FL/Fl_Double_Window.H"
#include "../lib/fltk/FL/fl_draw.H"
#include "../lib/fltk/FL/Fl_Box.H"
#include "../lib/fltk/FL/Fl_Widget.H"
#include "../lib/fltk/FL/Enumerations.H"
#include "../lib/fltk/FL/Fl_PNG_Image.H"
#include "../lib/fltk/FL/Fl_RGB_Image.H"
#include "../lib/fltk/FL/Fl_JPEG_Image.H"
#include <string>
#include <filesystem>
#include <iostream>

#include "../Headers/heads.h"
#include "../events/events.h"
#include "../Main/Waves.h"
#include "../Weapons/weapons.h"
#include "../Graphic/FLTKgraphic.h"


/// @brief class of main menu window
class MainMenu
{
private:
    static inline Fl_Window *window;

public:
    static void MakeWindow(int, int);
    static GraphicButton *MakeButton(
        int x, int y, int w, int h, 
        const char *name = ""
    );

    static void Show();
    static void Hide();

};

