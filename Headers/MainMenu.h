#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Enumerations.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_JPEG_Image.H>
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
    static Fl_Button *MakeButton(
        int x, int y, int w, int h, 
        const char *name = ""
    );

    static void Show();
    static void Hide();

};

