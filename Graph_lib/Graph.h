#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include <cmath>
#include <functional>
#include <string>
#include <vector>

#include "Point.h"
#include "fltk.h"

namespace Graph_lib {

// defense against ill-behaved Linux macros:
#undef major
#undef minor

// error() simply disguises throws:
[[noreturn]] void error (const std::string& msg);
[[noreturn]] void error (const std::string& msg, const std::string& msg2);

int randint (int min, int max);
int randint (int max);

// C++ standard does not define any mathematical constants
// NB! Constants, such as M_PI etc, are not cross-platform
const double pi{std::acos(-1.0)};

struct Color
{
  enum Color_type
  {
    red = FL_RED,
    blue = FL_BLUE,
    green = FL_GREEN,
    yellow = FL_YELLOW,
    white = FL_WHITE,
    black = FL_BLACK,
    magenta = FL_MAGENTA,
    cyan = FL_CYAN,
    dark_red = FL_DARK_RED,
    dark_green = FL_DARK_GREEN,
    dark_yellow = FL_DARK_YELLOW,
    dark_blue = FL_DARK_BLUE,
    dark_magenta = FL_DARK_MAGENTA,
    dark_cyan = FL_DARK_CYAN
  };

  enum Transparency
  {
    invisible = 0,
    visible = 255
  };

  Color(Color_type cc) : c{Fl_Color(cc)}, v{visible} {}

  Color(Color_type cc, Transparency vv) : c{Fl_Color(cc)}, v{static_cast<unsigned char>(vv)} {}

  Color(int cc) : c{Fl_Color(cc)}, v{visible} {}

  Color(Transparency vv) : c{Fl_Color()}, v{static_cast<unsigned char>(vv)} {}

  int as_int () const { return c; }

  char visibility () const { return v; }

  void set_visibility (Transparency vv) { v = vv; }

private:
  Fl_Color c;
  unsigned char v;  // 0 or 1 for now
};

struct Line_style
{
  enum Line_style_type
  {
    solid = FL_SOLID,            // -------
    dash = FL_DASH,              // - - - -
    dot = FL_DOT,                // .......
    dashdot = FL_DASHDOT,        // - . - .
    dashdotdot = FL_DASHDOTDOT,  // -..-..
  };

  Line_style(Line_style_type ss) : s{ss}, w{0} {}

  Line_style(Line_style_type lst, int ww) : s{lst}, w{ww} {}

  Line_style(int ss) : s{ss}, w{0} {}

  int width () const { return w; }

  int style () const { return s; }

private:
  int s;
  int w;
};

class Font
{
public:
  enum Font_type
  {
    helvetica = FL_HELVETICA,
    helvetica_bold = FL_HELVETICA_BOLD,
    helvetica_italic = FL_HELVETICA_ITALIC,
    helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
    courier = FL_COURIER,
    courier_bold = FL_COURIER_BOLD,
    courier_italic = FL_COURIER_ITALIC,
    courier_bold_italic = FL_COURIER_BOLD_ITALIC,
    times = FL_TIMES,
    times_bold = FL_TIMES_BOLD,
    times_italic = FL_TIMES_ITALIC,
    times_bold_italic = FL_TIMES_BOLD_ITALIC,
    symbol = FL_SYMBOL,
    screen = FL_SCREEN,
    screen_bold = FL_SCREEN_BOLD,
    zapf_dingbats = FL_ZAPF_DINGBATS
  };

  Font(Font_type ff) : f{ff} {}

  Font(int ff) : f{ff} {}

  int as_int () const { return f; }

private:
  int f;
};

template <class T> class Vector_ref
{
  std::vector<T*> v;
  std::vector<T*> owned;

public:
  Vector_ref() = default;

  Vector_ref(T* a, T* b = nullptr, T* c = nullptr, T* d = nullptr)
  {
    if (a)
      push_back(a);
    if (b)
      push_back(b);
    if (c)
      push_back(c);
    if (d)
      push_back(d);
  }

  ~Vector_ref() { clear(); }

  void push_back (T& s) { v.push_back(&s); }

  void push_back (T* p)
  {
    v.push_back(p);
    owned.push_back(p);
  }

  void clear ()
  {
    for (unsigned int i = 0; i < owned.size(); ++i)
      delete owned[i];
    owned.clear();
    v.clear();
  }

  // ???void erase(???)

  T& operator[] (int i) { return *v.at(i); }

  const T& operator[] (int i) const { return *v.at(i); }

  int size () const { return v.size(); }
};

class Shape  // deals with color and style, and holds sequence of lines
{
protected:
  void add (Point p) { points.push_back(p); }

  void set_point (int i, Point p) { points[i] = p; }

public:
  Shape() = default;
  Shape(std::initializer_list<Point> lst);  // add() the Points to this Shape

  void draw () const;  // deal with color and draw_lines

protected:
  virtual void draw_lines () const;  // simply draw the appropriate lines

public:
  virtual void move (int dx, int dy);  // move the shape +=dx and +=dy

  void set_color (Color col) { lcolor = col; }

  Color color () const { return lcolor; }

  void set_style (Line_style sty) { ls = sty; }

  Line_style style () const { return ls; }

  void set_fill_color (Color col) { fcolor = col; }

  Color fill_color () const { return fcolor; }

  Point point (int i) const { return points[i]; }

  int number_of_points () const { return int(points.size()); }

  virtual ~Shape() = 0;

  Shape(const Shape&) = delete;  // don't copy Shapes
  Shape& operator= (const Shape&) = delete;

private:
  std::vector<Point> points;  // not used by all shapes
  Color lcolor{static_cast<Color>(fl_color())};
  Line_style ls{0};
  Color fcolor{Color::invisible};
};

using Fct = std::function<double(double)>;

struct Function : Shape
{
  // the function parameters are not stored
  Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
};

struct Line : Shape
{
  Line(Point p1, Point p2)
  {
    add(p1);
    add(p2);
  }
};

struct Rectangle : Shape
{
  Rectangle(Point xy, int ww, int hh) : w{ww}, h{hh}
  {
    if (h <= 0 || w <= 0)
      error("Bad rectangle: non-positive side");
    add(xy);
  }

  Rectangle(Point x, Point y) : w{y.x - x.x}, h{y.y - x.y}
  {
    if (h <= 0 || w <= 0)
      error("Bad rectangle: first point is not top left");
    add(x);
  }

  void draw_lines () const override;

  int height () const { return h; }

  int width () const { return w; }

private:
  int w;  // width
  int h;  // height
};

bool intersect (Point p1, Point p2, Point p3, Point p4);

struct Open_polyline : Shape  // open sequence of lines
{
  using Shape::Shape;

  void add (Point p) { Shape::add(p); }

  void draw_lines () const override;
};

struct Closed_polyline : Open_polyline  // closed sequence of lines
{
  using Open_polyline::Open_polyline;

  void draw_lines () const override;
};

struct Polygon : Closed_polyline  // closed sequence of non-intersecting lines
{
  using Closed_polyline::Closed_polyline;

  void add (Point p);
  void draw_lines () const override;
};

struct Lines : Shape  // indepentdent lines
{
  Lines() {}

  Lines(std::initializer_list<Point> lst) : Shape{lst}
  {
    if (lst.size() % 2)
      error("odd number of points for Lines");
  }

  void draw_lines () const override;

  void add (Point p1, Point p2)
  {
    Shape::add(p1);
    Shape::add(p2);
  }
};

struct Text : Shape
{
  // the point is the bottom left of the first letter
  Text(Point x, const std::string& s) : lab{s} { add(x); }

  void draw_lines () const override;

  void set_label (const std::string& s) { lab = s; }

  std::string label () const { return lab; }

  void set_font (Font f) { fnt = f; }

  Font font () const { return Font{fnt}; }

  void set_font_size (int s) { fnt_sz = s; }

  int font_size () const { return fnt_sz; }

private:
  std::string lab;  // label
  Font fnt{fl_font()};
  int fnt_sz{(14 < fl_size()) ? fl_size() : 14};  // at least 14 point
};

struct Axis : Shape
{
  // representation left public
  enum Orientation
  {
    x,
    y,
    z
  };

  Axis(Orientation d, Point xy, int length, int nummber_of_notches = 0, const std::string& label = "");

  void draw_lines () const override;
  void move (int dx, int dy) override;

  void set_color (Color c);

  Text label;
  Lines notches;
};

struct Circle : Shape
{
  Circle(Point p, int rr)  // center and radius
      : r{rr}
  {
    add(Point{p.x - r, p.y - r});
  }

  void draw_lines () const override;

  Point center () const { return {point(0).x + r, point(0).y + r}; }

  void set_radius (int rr) { r = rr; }

  int radius () const { return r; }

private:
  int r;
};

struct Ellipse : Shape
{
  Ellipse(Point p, int ww, int hh)  // center, min, and max distance from center
      : w{ww}, h{hh}
  {
    add(Point{p.x - ww, p.y - hh});
  }

  void draw_lines () const override;

  Point center () const { return {point(0).x + w, point(0).y + h}; }

  Point focus1 () const;
  Point focus2 () const;

  void set_major (int ww);

  int major () const { return w; }

  void set_minor (int hh);

  int minor () const { return h; }

private:
  int w;
  int h;
};

struct Marked_polyline : Open_polyline
{
  Marked_polyline(const std::string& m) : mark{m}
  {
    if (m == "")
      mark = "*";
  }

  Marked_polyline(const std::string& m, std::initializer_list<Point> lst);

  void draw_lines () const override;

private:
  std::string mark;
};

struct Marks : Marked_polyline
{
  Marks(const std::string& m) : Marked_polyline{m} { set_color(Color{Color::invisible}); }
};

struct Mark : Marks
{
  Mark(Point xy, char c) : Marks{std::string(1, c)} { add(xy); }
};

struct Bad_image : Fl_Image
{
  Bad_image(int h, int w) : Fl_Image{h, w, 0} {}

  void draw (int x, int y, int, int, int, int) override { draw_empty(x, y); }
};

struct Suffix
{
  enum Encoding
  {
    none,
    png,
    jpg,
    gif,
    bmp
  };
};

Suffix::Encoding get_encoding (const std::string& s);

struct Image : Shape
{
  Image(Point xy, const std::string& s, Suffix::Encoding e = Suffix::none);

  ~Image() { delete p; }

  void draw_lines () const override;

  void set_mask (Point xy, int ww, int hh)
  {
    w = ww;
    h = hh;
    cx = xy.x;
    cy = xy.y;
  }

  void move (int dx, int dy) override
  {
    Shape::move(dx, dy);
    p->draw(point(0).x, point(0).y);
  }

private:
  int w, h, cx, cy;  // define "masking box" within image relative to position (cx,cy)
  Fl_Image* p;
  Text fn;
};

}  // namespace Graph_lib

#endif  // GRAPH_GUARD
