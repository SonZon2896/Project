#include "FLTKgraphic.h"

void Line::draw()
{
    fl_color(24);
    fl_line(x, y, x1, y1);
    fl_line_style(0, 5);
}  

Line::Line(int x, int y, int x1, int y1) 
    :Fl_Box(x, y, x1, y1), x{x}, y{y}, x1{x1}, y1{y1} {}

void GraphicCockr::draw()
{
    Fl_Box::draw();
}

void GraphicCockr::redraw()
{
    position(cockr->pos.x, cockr->pos.y);
    Fl_Box::redraw();
}

GraphicCockr::GraphicCockr(Cockroach* cockr) : Fl_Box(cockr->pos.x, cockr->pos.y, 25, 25) 
{
    box(FL_UP_BOX);
}

void Graphic::MakeWindow()
{
    window = new Fl_Window(600, 400);
    window->show();
}

Fl_Button* Graphic::MakeButton(int x, int y, int w, int h, const char* name)
{
    Fl_Button* btn = new Fl_Button(x, y, w, h, name);
    window->add(btn);
    return btn;
}

void Graphic::RedrawWindow()
{
    window->redraw();
}

void Graphic::ShowRoads(const std::vector<Road>& roads)
{
    for (auto road: roads)
        for (size_t i = 1; i < road.size(); ++i)
            window->add(new Line(road[i-1].x, road[i-1].y, road[i].x, road[i].y));
}

GraphicCockr* Graphic::MakeCockr(Cockroach* cockr)
{
    auto cockroach = new GraphicCockr(cockr);
    window->add(cockroach);
    return cockroach;
}

void Graphic::ShowCockroaches()
{
    cockroaches.reserve(Cockroach::GetAll().size());
    for (auto cockr: Cockroach::GetAll())
    {
        cockroaches.push_back(new GraphicCockr(cockr));
        window->add(cockroaches[cockroaches.size() - 1]);
    }
}