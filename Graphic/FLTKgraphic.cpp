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
    img = new Fl_PNG_Image("./PNG/game_field.png");
}

void Background::draw()
{
    img->draw(0, 0);
}

// GraphicCockr

void GraphicCockr::draw()
{
    Point cur_direction = cockr->GetDirection();
    if (prev_direction != cur_direction){
        UpdateImage();
        prev_direction = cur_direction;
    }

    img->draw(cockr->pos.x - width / 2, cockr->pos.y - height / 2);
}

GraphicCockr::GraphicCockr(Cockroach *cockr) : Fl_Box(0, 0, 0, 0), cockr{cockr}
{
    img = new Fl_PNG_Image("./PNG/cockroach_px.png");
    resize(cockr->pos.x - width / 2, cockr->pos.y - height / 2, width, height);
    prev_direction = Point{0, 0};
}

void GraphicCockr::UpdateImage(){
    img = new Fl_PNG_Image(&GetPathToImageCockr(*cockr)[0]);
    
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
    progress_box->resize(pos.x, pos.y, size.x * progress, size.y);
    Fl_Box::draw();
}

ProgressBar::ProgressBar(const Point &pos)
    : pos{pos}, size{50, 10}, Fl_Box{pos.x, pos.y, size.x, size.y}, progress_box(new Fl_Box(pos.x, pos.y, 0, size.y))
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
    label(&name[0]);
    pb->progress = slapper->GetProgress();
    Fl_Button::draw();
}

#define slapper_size_x 20
#define slapper_size_y 20

GraphicSlapper::GraphicSlapper(Slapper *slapper)
    : slapper{slapper},
      Fl_Button(slapper->GetPos().x - slapper_size_x / 2, slapper->GetPos().y - slapper_size_y / 2, slapper_size_x, slapper_size_y),
      pb(Graphic::MakeProgressBar(slapper->GetPos() + Point{-25., -25.})),
      gtrig{Graphic::MakeTrigger(slapper->GetTrigger())}
{
    name = std::to_string(slapper->GetLvl()) + "lvl\nSlapper\n" + std::to_string((int)slapper->GetCost());
    label(&name[0]);
    box(FL_UP_BOX);
}

#undef slapper_size_x
#undef slapper_size_y

void SlapUpgrade(Fl_Widget* w, void *slapper)
{
    auto slap = (Slapper *)slapper;
    if (Event::money < slap->GetCost())
        return;
    Event::money -= slap->GetCost();
    slap->Upgrade();
    ((GraphicSlapper *)w)->name = std::to_string(slap->GetLvl()) + "lvl\nSlapper\n" + std::to_string((int)slap->GetCost());
}

// GraphicDichlorvos

void GraphicDichlorvos::draw()
{
    label(&name[0]);
    pb->progress = dichlorvos->GetProgress();
    Fl_Button::draw();
}

#define dich_size_x 20
#define dich_size_y 20

GraphicDichlorvos::GraphicDichlorvos(Dichlorvos *dichlorvos)
    : dichlorvos{dichlorvos},
      Fl_Button(dichlorvos->GetPos().x - dich_size_x / 2, dichlorvos->GetPos().y - dich_size_y / 2, dich_size_x, dich_size_y),
      pb(Graphic::MakeProgressBar(dichlorvos->GetPos() + Point{-25, -25})),
      gtrig{Graphic::MakeTrigger(dichlorvos->GetTrigger())}
{
    name = std::to_string(dichlorvos->GetLvl()) + "lvl\nDichlorvos\n" + std::to_string((int)dichlorvos->GetCost());
    label(&name[0]);
    box(FL_UP_BOX);
    callback(DichlorvosUpgrade, dichlorvos);
}

#undef dich_size_x
#undef dich_size_y

void DichlorvosUpgrade(Fl_Widget* w, void *dichlorvos)
{
    auto dichl = (Dichlorvos *)dichlorvos;
    if (Event::money < dichl->GetCost())
        return;
    Event::money -= dichl->GetCost();
    dichl->Upgrade();
    ((GraphicDichlorvos *)w)->name = std::to_string(dichl->GetLvl()) + "lvl\nDichlorvos\n" + std::to_string((int)dichl->GetCost());
}

// GraphicCatch

void GraphicTrap::draw()
{
    label(&name[0]);
    pb->progress = trap->GetProgress();
    Fl_Button::draw();
}

#define trap_size_x 20
#define trap_size_y 20

GraphicTrap::GraphicTrap(Trap *trap)
    : trap{trap},
      Fl_Button(trap->GetPos().x - trap_size_x / 2, trap->GetPos().y - trap_size_y / 2, trap_size_x, trap_size_y),
      pb(Graphic::MakeProgressBar(trap->GetPos() + Point{-25, -25})),
      gtrig{Graphic::MakeTrigger(trap->GetTrigger())}
{
    name = std::to_string(trap->GetLvl()) + "lvl\nTrap\n" + std::to_string((int)trap->GetCost());
    label(&name[0]);
    box(FL_UP_BOX);
    callback(TrapUpgrade, trap);
}

#undef trap_size_x
#undef trap_size_y

void TrapUpgrade(Fl_Widget* w, void *trap)
{
    auto tr = (Trap *)trap;
    if (Event::money < tr->GetCost())
        return;
    Event::money -= tr->GetCost();
    tr->Upgrade();
    ((GraphicTrap *)w)->name = std::to_string(tr->GetLvl()) + "lvl\nTrap\n" + std::to_string((int)tr->GetCost());
}

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

GraphicSlapper *Graphic::MakeSlapper(Slapper *slapper)
{
    auto temp = new GraphicSlapper(slapper);
    temp->callback(SlapUpgrade, slapper);
    window->add(temp);
    return temp;
}

GraphicDichlorvos *Graphic::MakeDichlorvos(Dichlorvos *dichlorvos)
{
    auto temp = new GraphicDichlorvos(dichlorvos);
    window->add(temp);
    return temp;
}

GraphicTrap *Graphic::MakeTrap(Trap *trap)
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