#include "FLTKgraphic.h"

// Line

void Line::draw()
{
    fl_color(24);
    fl_line_style(0, 5);
    fl_line(x, y, x1, y1);
}

Line::Line(int x, int y, int x1, int y1)
    : Fl_Box(x, y, x1, y1), x{x}, y{y}, x1{x1}, y1{y1} {}

// Background

Background::Background() : Fl_Box(0, 0, 1280, 720)
{
    img = new Fl_PNG_Image("../PNG/game_field.png");
}

void Background::draw()
{
    img->draw(0, 0);
}

// GraphicCockr

void GraphicCockr::draw()
{
    img->draw(cockr->pos.x - width / 2, cockr->pos.y - height / 2);
}

GraphicCockr::GraphicCockr(Cockroach *cockr) : Fl_Box(0, 0, 0, 0), cockr{cockr}
{
    img = new Fl_PNG_Image("../PNG/cockroach_px.png");
    resize(cockr->pos.x - width / 2, cockr->pos.y - height / 2, width, height);
}

// Text

Text::Text(int x, int y, std::string name) : Fl_Box{x, y, 100, 50}, name{name}
{
    box(FL_UP_BOX);
}

void Text::draw()
{
    std::string temp = name + '\n' + output;
    label(&temp[0]);
//Fl_Widget::label_type(FL_ALIGN_BOTTOM);
    Fl_Box::color(FL_DARK1);
    Fl_Box::labelfont(FL_BOLD+FL_ITALIC+FL_SHADOW_LABEL);
    Fl_Box::labelcolor(FL_BLACK);
    Fl_Box::draw();
}

// ProgressBar

void ProgressBar::draw()
{
Fl_Box::draw();
    progress_box->resize(pos.x, pos.y, size.x * progress, size.y);
    Fl_Box::draw();
}

ProgressBar::ProgressBar(const Point &pos)
    : pos{pos}, size{100, 25}, Fl_Box{pos.x, pos.y, size.x, size.y}, progress_box(new Fl_Box(pos.x, pos.y, 0, size.y))
{
    box(FL_UP_BOX);
    progress_box->color(FL_GREEN);
    progress_box->box(FL_UP_BOX);
}

// GraphicTrigger

void GraphicTrigger::draw()
{
    if (trig->cockroaches.size() > 0)
        fl_color(FL_RED);
    else
        fl_color(FL_GREEN);
    fl_line(trig->pos.x, trig->pos.y, trig->pos.x + trig->size.x, trig->pos.y, trig->pos.x + trig->size.x, trig->pos.y + trig->size.y);
    fl_line(trig->pos.x, trig->pos.y, trig->pos.x, trig->pos.y + trig->size.y, trig->pos.x + trig->size.x, trig->pos.y + trig->size.y);
    Fl_Box::draw();
}

GraphicTrigger::GraphicTrigger(const Trigger *trig)
    : trig{trig}, Fl_Box(trig->pos.x, trig->pos.y, trig->size.x, trig->size.y)
{
    // box(FL_UP_BOX);
}

// GraphicSlapper

void GraphicSlapper::draw()
{
    pb->progress = slapper->GetProgress();
    Fl_Box::draw();
}

#define size_x 20
#define size_y 20

GraphicSlapper::GraphicSlapper(const Slapper *slapper)
    : slapper{slapper},
      Fl_Box(slapper->GetPos().x - size_x / 2, slapper->GetPos().y - size_y / 2, size_x, size_y, "Slapper"),
      pb(Graphic::MakeProgressBar(slapper->GetPos() + Point{-50, -45})),
      gtrig{Graphic::MakeTrigger(slapper->GetTrigger())}
{
    box(FL_UP_BOX);
}

// GraphicDichlorvos

void GraphicDichlorvos::draw()
{
    pb->progress = dichlorvos->GetProgress();
    Fl_Box::draw();
}

#define size_x 20
#define size_y 20

GraphicDichlorvos::GraphicDichlorvos(const Dichlorvos *dichlorvos)
    : dichlorvos{dichlorvos},
      Fl_Box(dichlorvos->GetPos().x - size_x / 2, dichlorvos->GetPos().y - size_y / 2, size_x, size_y, "Dichlorvos"),
      pb(Graphic::MakeProgressBar(dichlorvos->GetPos() + Point{-50, -45})),
      gtrig{Graphic::MakeTrigger(dichlorvos->GetTrigger())}
{
    box(FL_UP_BOX);
}

// GraphicCatch

void GraphicTrap::draw()
{
    pb->progress = trap->GetProgress();
    Fl_Box::draw();
}

#define size_x 20
#define size_y 20

GraphicTrap::GraphicTrap(const Trap *trap)
    : trap{trap},
      Fl_Box(trap->GetPos().x - size_x / 2, trap->GetPos().y - size_y / 2, size_x, size_y, "Trap"),
      pb(Graphic::MakeProgressBar(trap->GetPos() + Point{-50, -45})),
      gtrig{Graphic::MakeTrigger(trap->GetTrigger())}
{
    box(FL_UP_BOX);
}

#undef size_x
#undef size_y

// Graphic

void Graphic::MakeWindow(int w, int h)
{
    window = new Fl_Window(w, h);
    window->show();
    Background *bg = new Background();
    window->add(bg);
    Fl::add_timeout(1. / 60., Timer_CB, (void *)window);
}

Fl_Button *Graphic::MakeButton(int x, int y, int w, int h, const char *name)
{
    Fl_Button *btn = new Fl_Button(x, y, w, h, name);
    window->add(btn);
    return btn;
}

void Graphic::Timer_CB(void *userdata)
{
    Fl_Window *w = (Fl_Window *)userdata;
    w->redraw();
    Fl::repeat_timeout(1. / 60., Timer_CB, userdata);
}

void Graphic::ShowRoads(const std::vector<Road> &roads)
{
    for (auto road : roads)
        for (size_t i = 1; i < road.size(); ++i)
            window->add(new Line(road[i - 1].x, road[i - 1].y, road[i].x, road[i].y));
}

// Graphic Fabric

GraphicCockr *Graphic::MakeCockr(Cockroach *cockr)
{
    auto temp = new GraphicCockr(cockr);
    window->add(temp);
    return temp;
}

Text *Graphic::MakeText(int x, int y, std::string name)
{
    Text *temp = new Text(x, y, name);
    window->add(temp);
    return temp;
}

ProgressBar *Graphic::MakeProgressBar(const Point &pos)
{
    auto temp = new ProgressBar(pos);
    window->add(temp);
    window->add(temp->progress_box);
    return temp;
}

GraphicTrigger *Graphic::MakeTrigger(const Trigger *trig)
{
    auto temp = new GraphicTrigger(trig);
    window->add(temp);
    return temp;
}

GraphicSlapper *Graphic::MakeSlapper(const Slapper *slapper)
{
    auto temp = new GraphicSlapper(slapper);
    window->add(temp);
    return temp;
}

GraphicDichlorvos *Graphic::MakeDichlorvos(const Dichlorvos *dichlorvos)
{
    auto temp = new GraphicDichlorvos(dichlorvos);
    window->add(temp);
    return temp;
}

GraphicTrap *Graphic::MakeTrap(const Trap *trap)
{
    auto temp = new GraphicTrap(trap);
    window->add(temp);
    return temp;
}

void Graphic::ShowCockroaches()
{
    cockroaches.reserve(Cockroach::GetAll().size());
    for (auto cockr : Cockroach::GetAll())
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