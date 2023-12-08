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

Background::Background(std::string path) : Fl_Box(0, 0, 1280, 720)
{
    img = new Fl_PNG_Image(&path[0]);
}

void Background::draw()
{
    img->draw(0, 0);
}

Background::~Background()
{
    delete img;
}

// GraphicCockr

void GraphicEnemy::draw()
{
    Point cur_direction = enemy->GetDirection();
    if (prev_direction != cur_direction || (enemy->is_death && !is_death_img))
    {
        UpdateImage();
        prev_direction = cur_direction;
    }
    img_now->draw(enemy->pos.x - ENEMY_SIZE_X / 2, enemy->pos.y - ENEMY_SIZE_Y / 2);
}

GraphicEnemy::GraphicEnemy(Enemy *enemy, std::string path_to_img) : Fl_Box(0, 0, 0, 0), enemy{enemy}
{
    resize(enemy->pos.x - ENEMY_SIZE_X / 2, enemy->pos.y - ENEMY_SIZE_Y / 2, ENEMY_SIZE_X, ENEMY_SIZE_Y);
    prev_direction = Point{0, 0};
    img_up = new Fl_PNG_Image(&(path_to_img + "_up.png")[0]);
    img_down = new Fl_PNG_Image(&(path_to_img + "_down.png")[0]);
    img_left = new Fl_PNG_Image(&(path_to_img + "_left.png")[0]);
    img_right = new Fl_PNG_Image(&(path_to_img + "_right.png")[0]);
    img_death = new Fl_PNG_Image(&(path_to_img + "_death.png")[0]);
}

GraphicEnemy::~GraphicEnemy()
{
    delete img_up, img_down, img_left, img_right, img_death;
}

void GraphicEnemy::UpdateImage()
{
    if (enemy->is_death)
    {
        img_now = img_death;
        is_death_img = true;
        return;
    }
    switch (enemy->GetOrientation())
    {
    case UP:
        img_now = img_up;
        break;
    case DOWN:
        img_now = img_down;
        break;
    case LEFT:
        img_now = img_left;
        break;
    case RIGHT:
        img_now = img_right;
        break;
    }
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
    // Fl_Widget::label_type(FL_ALIGN_BOTTOM);
    Fl_Box::color(FL_DARK1);
    Fl_Box::labelfont(FL_BOLD + FL_ITALIC + FL_SHADOW_LABEL);
    Fl_Box::labelcolor(FL_BLACK);
    Fl_Box::draw();
}

// ProgressBar

void ProgressBar::draw()
{
    progress_box->resize(pos.x, pos.y, pb_size_x * progress, pb_size_y);
    Fl_Box::draw();
}

ProgressBar::ProgressBar(const Point &pos)
    : pos{pos},
      Fl_Box{(int)pos.x, (int)pos.y, pb_size_x, pb_size_y},
      progress_box(new Fl_Box((int)pos.x, (int)pos.y, 0, pb_size_y))
{
    box(FL_UP_BOX);
    progress_box->color(FL_GREEN);
    progress_box->box(FL_UP_BOX);
}

ProgressBar::~ProgressBar()
{
    delete progress_box;
}

// GraphicTrigger

void GraphicTrigger::draw()
{
    if (trig->enemies.size() > 0)
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

// GraphicWeapon

void GraphicWeapon::draw()
{
    label(&name[0]);
    Fl_Button::draw();
}

GraphicWeapon::GraphicWeapon(Point pos, const Trigger *trigger)
    : gtrig{Graphic::MakeTrigger(trigger)},
      pb(Graphic::MakeProgressBar(pos + Point{-pb_size_x / 2, -weapon_size_y / 2 - 10})),
      Fl_Button(pos.x - weapon_size_x / 2, pos.y - weapon_size_y / 2, weapon_size_x, weapon_size_y)
{
    box(FL_NO_BOX);
}

// GraphicSlapper

void GraphicSlapper::draw()
{
    pb->progress = slapper->GetProgress();
    img->draw(slapper->GetPos().x - weapon_size_x / 2, slapper->GetPos().y - weapon_size_y / 2);
    GraphicWeapon::draw();
}

GraphicSlapper::GraphicSlapper(Slapper *slapper)
    : slapper{slapper},
      GraphicWeapon(slapper->GetPos(), slapper->trigger)
{
    name = std::to_string(slapper->GetLvl()) + "lvl\n" + std::to_string((int)slapper->GetCost());
    img = new Fl_PNG_Image("./PNG/slapper_px.png");
    auto upgrade = [](Fl_Widget *w, void *data)
    {
        auto weap = (Slapper *)data;
        if (Event::money < weap->GetCost())
            return;
        Event::money -= weap->GetCost();
        weap->Upgrade();
        ((GraphicWeapon *)w)->name = std::to_string(weap->GetLvl()) + "lvl\n" + std::to_string((int)weap->GetCost());
    };
    callback(upgrade, slapper);
}

GraphicSlapper::~GraphicSlapper()
{
    delete img;
    delete slapper;
}

// GraphicDichlorvos

void GraphicDichlorvos::draw()
{
    pb->progress = dichlorvos->GetProgress();
    img->draw(dichlorvos->GetPos().x - weapon_size_x / 2, dichlorvos->GetPos().y - weapon_size_y / 2);
    GraphicWeapon::draw();
}

GraphicDichlorvos::GraphicDichlorvos(Dichlorvos *dichlorvos)
    : dichlorvos{dichlorvos},
      GraphicWeapon(dichlorvos->GetPos(), dichlorvos->trigger)
{
    name = std::to_string(dichlorvos->GetLvl()) + "lvl\n" + std::to_string((int)dichlorvos->GetCost());
    switch (dichlorvos->GetDir())
    {
    case UP:
        img = new Fl_PNG_Image("./PNG/dichlorvos_up.png");
        break;
    case DOWN:
        img = new Fl_PNG_Image("./PNG/dichlorvos_down.png");
        break;
    case LEFT:
        img = new Fl_PNG_Image("./PNG/dichlorvos_left.png");
        break;
    case RIGHT:
        img = new Fl_PNG_Image("./PNG/dichlorvos_right.png");
        break;
    default:
        img = new Fl_PNG_Image("./PNG/dichlorvos_up.png");
    }
    auto upgrade = [](Fl_Widget *w, void *data)
    {
        auto weap = (Dichlorvos *)data;
        if (Event::money < weap->GetCost())
            return;
        Event::money -= weap->GetCost();
        weap->Upgrade();
        ((GraphicWeapon *)w)->name = std::to_string(weap->GetLvl()) + "lvl\n" + std::to_string((int)weap->GetCost());
    };
    callback(upgrade, dichlorvos);
}

GraphicDichlorvos::~GraphicDichlorvos()
{
    delete img;
    delete dichlorvos;
}

// GraphicTrap

void GraphicTrap::draw()
{
    img->draw(trap->GetPos().x - weapon_size_x / 2, trap->GetPos().y - weapon_size_y / 2);
    pb->progress = trap->GetProgress();
    GraphicWeapon::draw();
}

GraphicTrap::GraphicTrap(Trap *trap)
    : trap{trap},
      GraphicWeapon(trap->GetPos(), trap->trigger)
{
    name = std::to_string(trap->GetLvl()) + "lvl\n" + std::to_string((int)trap->GetCost());
    img = new Fl_PNG_Image("./PNG/trap_px.png");
    auto upgrade = [](Fl_Widget *w, void *data)
    {
        auto weap = (Trap *)data;
        if (Event::money < weap->GetCost())
            return;
        Event::money -= weap->GetCost();
        weap->Upgrade();
        ((GraphicWeapon *)w)->name = std::to_string(weap->GetLvl()) + "lvl\n" + std::to_string((int)weap->GetCost());
    };
    callback(upgrade, trap);
}

GraphicTrap::~GraphicTrap()
{
    delete img;
    delete trap;
}

// Graphic

void Graphic::MakeWindow(int w, int h)
{
    if (is_window)
        return;
    window = new Fl_Window(w, h);
    is_window = true;
    Fl::add_timeout(1. / 60., Timer_CB, (void *)window);
}

void Graphic::MakeBackground(std::string path)
{
    Background *bg = new Background(&path[0]);
    window->add(bg);
}

void Graphic::ClearWindow()
{
    window->clear();
    cockroaches.clear();
}

void Graphic::Show(){
    window->show();
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

GraphicEnemy *Graphic::MakeCockr(Cockroach *cockr)
{
    auto temp = new GraphicEnemy(cockr, "./PNG/cockroach_px");
    window->add(temp);
    return temp;
}

GraphicEnemy *Graphic::MakeMouse(Mouse *mouse)
{
    auto temp = new GraphicEnemy(mouse, "./PNG/mouse");
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

void Graphic::ShowEnemies()
{
    auto all_cockr = Cockroach::GetAll();
    cockroaches.reserve(all_cockr.size());
    for (size_t i = cockroaches.size(); i < all_cockr.size(); ++i)
        cockroaches.push_back(MakeCockr(all_cockr[i]));
    
    auto all_mouses = Mouse::GetAll();
    mouses.reserve(all_mouses.size());
    for (size_t i = mouses.size(); i < all_mouses.size(); ++i)
        mouses.push_back(MakeMouse(all_mouses[i]));
}