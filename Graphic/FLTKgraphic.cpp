
#include "FLTKgraphic.h"


#define PATH_IMAGE_SLAPPER "./PNG/slapper_px.png"

#define PATH_IMAGE_TRAP "./PNG/trap_px.png"

#define PATH_IMAGE_DEFAULT_COCKROACH "./PNG/cockroach_px"
#define PATH_IMAGE_MOUSE "./PNG/mouse"
#define PATH_IMAGE_RAD_COCKROACH "./PNG/cockroach_radioactive"

#define PATH_IMAGE_DICHLORVOS_UP "./PNG/dichlorvos_up.png"
#define PATH_IMAGE_DICHLORVOS_DOWN "./PNG/dichlorvos_down.png"
#define PATH_IMAGE_DICHLORVOS_LEFT "./PNG/dichlorvos_left.png"
#define PATH_IMAGE_DICHLORVOS_RIGHT "./PNG/dichlorvos_right.png"

#define PATH_IMAGE_REJECT_BOX "./PNG/reject_box.png"
#define PATH_IMAGE_ACCEPT_BOX "./PNG/accept_box.png"
#define PATH_IMAGE_ARROW_UP_BOX "./PNG/arrow_up_box.png"
#define PATH_IMAGE_ARROW_DOWN_BOX "./PNG/arrow_down_box.png"
#define PATH_IMAGE_ARROW_LEFT_BOX "./PNG/arrow_left_box.png"
#define PATH_IMAGE_ARROW_RIGHT_BOX "./PNG/arrow_right_box.png"
#define PATH_IMAGE_SLAPPER_BOX "./PNG/slapper_box.png"
#define PATH_IMAGE_DICHLORVOS_BOX "./PNG/dichlorvos_box.png"
#define PATH_IMAGE_TRAP_BOX "./PNG/trap_box.png"

// Line

void Line::draw()
{
    fl_color(24);
    fl_line_style(0, 5);
    fl_line(x, y, x1, y1);
}

Line::Line(int x, int y, int x1, int y1)
    : Fl_Box(x, y, x1, y1), x{x}, y{y}, x1{x1}, y1{y1} {}

// GraphicButton

void GraphicButton::draw()
{
    Fl_Button::draw();
    if (image != nullptr)
        image->draw(pos.x, pos.y);
}

GraphicButton::GraphicButton(int x, int y, int w, int h, const char*name)
    : Fl_Button{x, y, w, h, name}, pos{x, y} {}

GraphicButton::~GraphicButton()
{
    delete image;
}

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
    UpdateImage();
    img_now->draw(enemy->pos.x - ENEMY_SIZE_X / 2, enemy->pos.y - ENEMY_SIZE_Y / 2);
}

GraphicEnemy::GraphicEnemy(Enemy *enemy, std::string path_to_img) : Fl_Box(0, 0, 0, 0), enemy{enemy}
{
    resize(
        enemy->pos.x - ENEMY_SIZE_X / 2, enemy->pos.y - ENEMY_SIZE_Y / 2, 
        ENEMY_SIZE_X, ENEMY_SIZE_Y
    );

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
    fl_line(
        trig->pos.x, trig->pos.y, 
        trig->pos.x + trig->size.x,
        trig->pos.y, 
        trig->pos.x + trig->size.x, 
        trig->pos.y + trig->size.y
    );
    fl_line(
        trig->pos.x, trig->pos.y, 
        trig->pos.x, 
        trig->pos.y + trig->size.y, 
        trig->pos.x + trig->size.x,
        trig->pos.y + trig->size.y
    );

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
      pb(Graphic::MakeProgressBar(pos + Point{-pb_size_x / 2, -WEAPON_SIZE_Y / 2 - 10})),
      Fl_Button(
        pos.x - WEAPON_SIZE_X / 2, pos.y - WEAPON_SIZE_Y / 2, 
        WEAPON_SIZE_X, WEAPON_SIZE_Y
      )
{
    box(FL_NO_BOX);
}

// GraphicSlapper

void GraphicSlapper::draw()
{
    pb->progress = slapper->GetProgress();
    img->draw(
        slapper->GetPos().x - WEAPON_SIZE_X / 2, 
        slapper->GetPos().y - WEAPON_SIZE_Y / 2
    );
    GraphicWeapon::draw();
}

GraphicSlapper::GraphicSlapper(Slapper *slapper)
    : slapper{slapper},
      GraphicWeapon(slapper->GetPos(), slapper->trigger)
{
    
    name = std::to_string(slapper->GetLvl()) + "lvl\n" + std::to_string((int)slapper->GetCost());
    img = new Fl_PNG_Image(PATH_IMAGE_SLAPPER);

    auto upgrade = [](Fl_Widget *w, void *data)
    {
        auto weap = (Slapper *)data;

        if (Event::money < weap->GetCost())
            return;

        Event::money -= weap->GetCost();
        weap->Upgrade();
        ((GraphicWeapon *)w)->name = std::to_string(
            weap->GetLvl()) + "lvl\n" + 
            std::to_string((int)weap->GetCost()
        );
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
    img->draw(
        dichlorvos->GetPos().x - WEAPON_SIZE_X / 2, 
        dichlorvos->GetPos().y - WEAPON_SIZE_Y / 2
    );
    GraphicWeapon::draw();
}

GraphicDichlorvos::GraphicDichlorvos(Dichlorvos *dichlorvos)
    : dichlorvos{dichlorvos},
      GraphicWeapon(dichlorvos->GetPos(), dichlorvos->trigger)
{
    name = std::to_string(
        dichlorvos->GetLvl()) + "lvl\n" + 
        std::to_string((int)dichlorvos->GetCost()
    );

    switch (dichlorvos->GetDir())
    {
    case UP:
        img = new Fl_PNG_Image(PATH_IMAGE_DICHLORVOS_UP);
        break;
    case DOWN:
        img = new Fl_PNG_Image(PATH_IMAGE_DICHLORVOS_DOWN);
        break;
    case LEFT:
        img = new Fl_PNG_Image(PATH_IMAGE_DICHLORVOS_LEFT);
        break;
    case RIGHT:
        img = new Fl_PNG_Image(PATH_IMAGE_DICHLORVOS_RIGHT);
        break;
    default:
        img = new Fl_PNG_Image(PATH_IMAGE_DICHLORVOS_UP);
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
    img->draw(trap->GetPos().x - WEAPON_SIZE_X / 2, trap->GetPos().y - WEAPON_SIZE_Y / 2);
    pb->progress = trap->GetProgress();
    GraphicWeapon::draw();
}

GraphicTrap::GraphicTrap(Trap *trap)
    : trap{trap},
      GraphicWeapon(trap->GetPos(), trap->trigger)
{
    name = std::to_string(
        trap->GetLvl()) + "lvl\n" + 
        std::to_string((int)trap->GetCost()
    );

    img = new Fl_PNG_Image(PATH_IMAGE_TRAP);
    auto upgrade = [](Fl_Widget *w, void *data)
    {
        auto weap = (Trap *)data;

        if (Event::money < weap->GetCost())
            return;

        Event::money -= weap->GetCost();
        weap->Upgrade();
        ((GraphicWeapon *)w)->name = std::to_string(
            weap->GetLvl()) + "lvl\n" + 
            std::to_string((int)weap->GetCost()
        );
    };

    callback(upgrade, trap);
}

GraphicTrap::~GraphicTrap()
{
    delete img;
    delete trap;
}

// ButtonMakeWeapon

ButtonMakeWeapon::ButtonMakeWeapon(Point pos)
    : pos{pos},
      Fl_Button(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 2, pos.y - BUTTON_MAKE_WEAPON_SIZE / 2, 
        BUTTON_MAKE_WEAPON_SIZE, BUTTON_MAKE_WEAPON_SIZE
      ),

      btn_back{Graphic::MakeButton(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 6, pos.y - BUTTON_MAKE_WEAPON_SIZE / 6, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3  
      )},

      btn_accept{Graphic::MakeButton(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 6, pos.y + BUTTON_MAKE_WEAPON_SIZE / 6, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )},

      btn_make_slapper{Graphic::MakeButton(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 2, pos.y - BUTTON_MAKE_WEAPON_SIZE / 6, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )},

      btn_make_dichlorvos{Graphic::MakeButton(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 6, pos.y - BUTTON_MAKE_WEAPON_SIZE / 2, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )},

      btn_make_trap{Graphic::MakeButton(
        pos.x + BUTTON_MAKE_WEAPON_SIZE / 6, pos.y - BUTTON_MAKE_WEAPON_SIZE / 6, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )},

      btn_dir_up{Graphic::MakeButton(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 6, pos.y - BUTTON_MAKE_WEAPON_SIZE / 2, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )},

      btn_dir_down{Graphic::MakeButton(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 6, pos.y + BUTTON_MAKE_WEAPON_SIZE / 6, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )},

      btn_dir_left{Graphic::MakeButton(
        pos.x - BUTTON_MAKE_WEAPON_SIZE / 2, pos.y - BUTTON_MAKE_WEAPON_SIZE / 6, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )},
      
      btn_dir_right{Graphic::MakeButton(
        pos.x + BUTTON_MAKE_WEAPON_SIZE / 6, pos.y - BUTTON_MAKE_WEAPON_SIZE / 6, 
        BUTTON_MAKE_WEAPON_SIZE / 3, BUTTON_MAKE_WEAPON_SIZE / 3
      )}
{
    box(FL_NO_BOX);

    btn_back->image = new Fl_PNG_Image(PATH_IMAGE_REJECT_BOX);
    btn_back->box(FL_NO_BOX);
    btn_accept->image = new Fl_PNG_Image(PATH_IMAGE_ACCEPT_BOX);
    btn_accept->box(FL_NO_BOX);
    btn_dir_up->image = new Fl_PNG_Image(PATH_IMAGE_ARROW_UP_BOX);
    btn_dir_up->box(FL_NO_BOX);
    btn_dir_down->image = new Fl_PNG_Image(PATH_IMAGE_ARROW_DOWN_BOX);
    btn_dir_down->box(FL_NO_BOX);
    btn_dir_left->image = new Fl_PNG_Image(PATH_IMAGE_ARROW_LEFT_BOX);
    btn_dir_left->box(FL_NO_BOX);
    btn_dir_right->image = new Fl_PNG_Image(PATH_IMAGE_ARROW_RIGHT_BOX);
    btn_dir_right->box(FL_NO_BOX);
    btn_make_slapper->image = new Fl_PNG_Image(PATH_IMAGE_SLAPPER_BOX);
    btn_make_slapper->box(FL_NO_BOX);
    btn_make_dichlorvos->image = new Fl_PNG_Image(PATH_IMAGE_DICHLORVOS_BOX);
    btn_make_dichlorvos->box(FL_NO_BOX);
    btn_make_trap->image = new Fl_PNG_Image(PATH_IMAGE_TRAP_BOX);
    btn_make_trap->box(FL_NO_BOX);

    auto StageZeroCB = [](Fl_Widget *w, void *data){((ButtonMakeWeapon *)data)->StageZero();};
    auto StageWeaponCB = [](Fl_Widget *w, void *data){((ButtonMakeWeapon *)data)->StageWeapon();};
    auto StageDirectionCB = [](Fl_Widget *w, void *data){auto unpack = ((std::pair<ButtonMakeWeapon *, EnumWeapon> *)data);
                                                         unpack->first->type = unpack->second;
                                                         unpack->first->StageDirection();};
    auto StageAcceptCB = [](Fl_Widget *w, void *data){auto unpack = ((std::pair<ButtonMakeWeapon *, Direction> *)data);
                                                     unpack->first->direction = unpack->second;
                                                     unpack->first->StageAccept();};
    auto MakeWeaponCB = [](Fl_Widget *w, void *data){((ButtonMakeWeapon *)data)->MakeWeapon();};
    
    callback(StageWeaponCB, this);
    btn_back->callback(StageZeroCB, this);
    btn_accept->callback(MakeWeaponCB, this);
    btn_make_slapper->callback(
        StageDirectionCB, 
        (void *)(new std::pair<ButtonMakeWeapon *, EnumWeapon>(this, EnumWeapon::slapper))
    );
    btn_make_dichlorvos->callback(
        StageDirectionCB, 
        (void *)(new std::pair<ButtonMakeWeapon *, EnumWeapon>(this, EnumWeapon::dichlorvos))
    );
    btn_make_trap->callback(
        StageDirectionCB, 
        (void *)(new std::pair<ButtonMakeWeapon *, EnumWeapon>(this, EnumWeapon::trap))
    );
    btn_dir_up->callback(
        StageAcceptCB, 
        (void *)(new std::pair<ButtonMakeWeapon *, Direction>(this, UP))
    );
    btn_dir_down->callback(
        StageAcceptCB, 
        (void *)(new std::pair<ButtonMakeWeapon *, Direction>(this, DOWN))
    );
    btn_dir_left->callback(
        StageAcceptCB, 
        (void *)(new std::pair<ButtonMakeWeapon *, Direction>(this, LEFT))
    );
    btn_dir_right->callback(
        StageAcceptCB, 
        (void *)(new std::pair<ButtonMakeWeapon *, Direction>(this, RIGHT))
    );

    StageZero();
}

void ButtonMakeWeapon::StageZero()
{
    btn_back->hide();
    btn_accept->hide();
    btn_make_slapper->hide();
    btn_make_dichlorvos->hide();
    btn_make_trap->hide();
    btn_dir_up->hide();
    btn_dir_down->hide();
    btn_dir_left->hide();
    btn_dir_right->hide();
    this->show();
}

void ButtonMakeWeapon::StageWeapon()
{
    btn_back->show();
    btn_accept->hide();
    btn_make_slapper->show();
    btn_make_dichlorvos->show();
    btn_make_trap->show();
    btn_dir_up->hide();
    btn_dir_down->hide();
    btn_dir_left->hide();
    btn_dir_right->hide();
    this->hide();
}

void ButtonMakeWeapon::StageDirection()
{
    btn_back->show();
    btn_accept->hide();
    btn_make_slapper->hide();
    btn_make_dichlorvos->hide();
    btn_make_trap->hide();
    btn_dir_up->show();
    btn_dir_down->show();
    btn_dir_left->show();
    btn_dir_right->show();
    this->hide();
}

void ButtonMakeWeapon::StageAccept()
{
    btn_back->show();
    btn_accept->show();
    btn_make_slapper->hide();
    btn_make_dichlorvos->hide();
    btn_make_trap->hide();
    btn_dir_up->hide();
    btn_dir_down->hide();
    btn_dir_left->hide();
    btn_dir_right->hide();
    this->hide();
}

void ButtonMakeWeapon::MakeWeapon()
{

    switch (type)
    {
    case EnumWeapon::slapper:
    {
        if(Event::money < SLAPPER_COAST)
            return;
        Event::money -= SLAPPER_COAST;
        auto slapper = new Slapper(pos, direction);
        Graphic::MakeSlapper(slapper);
        break;
    }
    case EnumWeapon::dichlorvos:
    {
        if(Event::money < DICHLORVOS_COAST)
            return;
        Event::money -= DICHLORVOS_COAST;
        auto dichlorvos = new Dichlorvos(pos, direction);
        Graphic::MakeDichlorvos(dichlorvos);
        break;
    }
    case EnumWeapon::trap:
    {
        if(Event::money < TRAP_COAST)
            return;
        Event::money -= TRAP_COAST;
        auto trap = new Trap(pos, direction);
        Graphic::MakeTrap(trap);
        break;
    }
    }
    
    btn_back->hide();
    btn_accept->hide();
    btn_make_slapper->hide();
    btn_make_dichlorvos->hide();
    btn_make_trap->hide();
    btn_dir_up->hide();
    btn_dir_down->hide();
    btn_dir_left->hide();
    btn_dir_right->hide();
    this->hide();
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
    mouses.clear();
    radcockroaches.clear();
}

void Graphic::Show(){
    window->show();
}

void Graphic::Hide(){
    window->hide();
}

GraphicButton *Graphic::MakeButton(int x, int y, int w, int h, const char *name)
{
    GraphicButton *btn = new GraphicButton(x, y, w, h, name);
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


void Graphic::AddDoomGuy(DoomGuy* doom_guy){
    auto temp = new GraphicDoomGuy(doom_guy);
    window->add(temp);
}


// Graphic Fabric

GraphicEnemy *Graphic::MakeCockr(Cockroach *cockr)
{
    auto temp = new GraphicEnemy(cockr, PATH_IMAGE_DEFAULT_COCKROACH);
    window->add(temp);
    return temp;
}

GraphicEnemy *Graphic::MakeMouse(Mouse *mouse)
{
    auto temp = new GraphicEnemy(mouse, PATH_IMAGE_MOUSE);
    window->add(temp);
    return temp;
}

GraphicEnemy *Graphic::MakeRadCockr(RadCockroach *rad_cockr)
{
    auto temp = new GraphicEnemy(rad_cockr, PATH_IMAGE_RAD_COCKROACH);
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

ButtonMakeWeapon *Graphic::MakeBTNWeapon(Point pos)
{
    auto temp = new ButtonMakeWeapon(pos);
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

    auto all_rad_cockr = RadCockroach::GetAll();
    radcockroaches.reserve(all_rad_cockr.size());
    for (size_t i = radcockroaches.size(); i < all_rad_cockr.size(); ++i)
        radcockroaches.push_back(MakeRadCockr(all_rad_cockr[i]));
}

GraphicDoomGuy::GraphicDoomGuy(DoomGuy* guy) : Fl_Box(0,0,0,0){
    resize(
        guy->pos.x, guy->pos.y,
        DOOMGUY_WIDTH, DOOMGUY_HEIGHT
    );

    _state_normal = new Fl_PNG_Image("./PNG/gavkoshmig_1.png");
    _state_little_warning = new Fl_PNG_Image("./PNG/gavkoshmig_2.png");
    _state_warning = new Fl_PNG_Image("./PNG/gavkoshmig_3.png");

    _guy = guy;
}

GraphicDoomGuy::~GraphicDoomGuy(){
    delete _cur_img;
}

void GraphicDoomGuy::UpdateImage(){
    DGSates state = _guy->get_state();

    switch (state){
        case DGSates::NORMAL:
            _cur_img = _state_normal;
            break;
        case DGSates::LITTLE_WARNING:
            _cur_img = _state_little_warning;
            break;
        case DGSates::WARNING:
            _cur_img = _state_warning;
            break;
        default:
            _cur_img = _state_normal;
    }
}

void GraphicDoomGuy::draw(){
    UpdateImage();
    _cur_img->draw(_guy->pos.x - DOOMGUY_WIDTH / 2, _guy->pos.y - DOOMGUY_HEIGHT / 2);
}