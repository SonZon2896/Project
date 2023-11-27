#include "FLTKgraphic.h"

void Line::draw()
{
    fl_color(24);
    fl_line_style(0, 5);
    fl_line(x, y, x1, y1);
}  

Line::Line(int x, int y, int x1, int y1) 
    :Fl_Box(x, y, x1, y1), x{x}, y{y}, x1{x1}, y1{y1} {}

void GraphicCockr::draw()
{
    img->draw(cockr->pos.x - width / 2, cockr->pos.y - height / 2);
}

GraphicCockr::GraphicCockr(Cockroach* cockr) : Fl_Box(0, 0, 0, 0), cockr{cockr} 
{
    img = new Fl_PNG_Image(RESOURCES_DIR"/PNG/cockroach.png");
    resize(cockr->pos.x - width / 2, cockr->pos.y - height / 2, width, height);
}

void Graphic::MakeWindow()
{
    window = new Fl_Window(1920, 1080);
    window->show();
    Fl::add_timeout(1. / 60., Timer_CB, (void*)window);
}

Fl_Button* Graphic::MakeButton(int x, int y, int w, int h, const char* name)
{
    Fl_Button* btn = new Fl_Button(x, y, w, h, name);
    window->add(btn);
    return btn;
}

void Graphic::Timer_CB(void* userdata)
{
    Fl_Window *w = (Fl_Window*)userdata;
    w->redraw();
    Fl::repeat_timeout(1. / 60., Timer_CB, userdata);
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

Text::Text(int x, int y): Fl_Box{x, y, 100, 50}
{
    box(FL_UP_BOX);
}

void Text::draw()
{
    label(&str[0]);
    Fl_Box::draw();
}

Text* Graphic::MakeText(int x, int y)
{
    Text* text = new Text(x, y);
    window->add(text);
    return text;
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

void Graphic::ClearCockroaches()
{
    for (auto cockr : cockroaches)
        cockr->hide();
    cockroaches.clear();
}