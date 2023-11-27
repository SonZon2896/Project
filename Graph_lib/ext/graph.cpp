#include <array>
#include <cmath>

#include "graph.h"

namespace Graph_lib {

Arc::Arc(Point p, int ww, int hh, int alpha, int beta)
    : Ellipse{p, ww, hh}, phi1{alpha}, phi2{beta}
{
}

void Arc::draw_lines() const
{
  int w = major(), h = minor();

  if (fill_color().visibility())  // fill
  {
    fl_color(fill_color().as_int());
    fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, phi1, phi2);
    fl_color(color().as_int());  // reset color
  }

  if (color().visibility())
    fl_arc(point(0).x, point(0).y, w + w, h + h, phi1, phi2);
}

Box::Box(Point xy, int ww, int hh, int radius)
    : Rectangle{xy, ww, hh}, r{radius}
{
  if (r < 0)
    error("Bad box: negative round radius");

  if (r == automatic)
    r = int(0.1 * std::min(ww, hh));
}

Box::Box(Point x, Point y, int radius) : Rectangle{x, y}, r{radius}
{
  if (r < 0)
    error("Bad box: negative round radius");

  if (r == automatic)
    r = int(0.1 * std::min(width(), height()));
}

void Box::draw_lines() const
{
  Point p = point(0);
  int w = width();
  int h = height();

  if (fill_color().visibility())  // fill
  {
    fl_color(fill_color().as_int());
    fl_pie(p.x, p.y, r + r - 1, r + r - 1, 90, 180);
    fl_rectf(p.x + r - 1, p.y, w - 2 * r + 2, r);
    fl_pie(p.x + w - 2 * r, p.y, r + r - 1, r + r - 1, 0, 90);

    fl_rectf(p.x, p.y + r - 1, w, h - 2 * r + 2);

    fl_pie(p.x + w - 2 * r, p.y + h - 2 * r, r + r - 1, r + r - 1, 270,
           360);
    fl_rectf(p.x + r - 1, p.y + h - r, w - 2 * r + 2, r);
    fl_pie(p.x, p.y + h - 2 * r, r + r - 1, r + r - 1, 180, 270);
    fl_color(color().as_int());  // reset color
  }

  if (color().visibility())
  {
    fl_arc(p.x, p.y, r + r, r + r, 90, 180);
    fl_line(p.x + r, p.y, p.x + w - r, p.y);

    fl_arc(p.x + w - 2 * r, p.y, r + r, r + r, 0, 90);
    fl_line(p.x + w, p.y + r, p.x + w, p.y + h - r);

    fl_arc(p.x + w - 2 * r, p.y + h - 2 * r, r + r, r + r, 270, 360);
    fl_line(p.x + w - r, p.y + h, p.x + r, p.y + h);

    fl_arc(p.x, p.y + h - 2 * r, r + r, r + r, 180, 270);
    fl_line(p.x, p.y + h - r, p.x, p.y + r);
  }
}

void Box::set_roundness(int radius)
{
  if (r < 0)
    error("Bad box: negative round radius");

  r = radius;
}

Regular_hexagon::Regular_hexagon(Point c, int r)
{
  constexpr int n = 6;  // number of vertices

  for (int i = 0; i < n; ++i)
  {
    Point p;
    double phi = 2 * pi * i / n;

    p.x = c.x + round(r * cos(phi));
    p.y = c.y + round(r * sin(phi));

    add(p);
  }
}

Point Regular_hexagon::center() const
{
  return {(point(0).x + point(3).x) / 2, point(0).y};
}

int Regular_hexagon::width() const { return point(0).x - point(3).x; }

int Regular_hexagon::height() const { return point(1).y - point(5).y; }

int Regular_hexagon::edge() const { return point(1).x - point(2).x; }

void Regular_hexagon::draw_lines() const
{
  if (fill_color().visibility())
  {
    fl_color(fill_color().as_int());
    fl_begin_complex_polygon();
    for (int i = 0; i < number_of_points(); ++i)
    {
      fl_vertex(point(i).x, point(i).y);
    }
    fl_end_complex_polygon();
    fl_color(color().as_int());  // reset color
  }

  if (color().visibility())
  {
    Shape::draw_lines();

    // draw closing line
    fl_line(point(number_of_points() - 1).x,
            point(number_of_points() - 1).y, point(0).x, point(0).y);
  }
}

Hexagon_tile::Hexagon_tile(Point p, int ww, int hh, int rr)
    : Rectangle{p, ww, hh}
{
  std::array<Color, 3> colors{Color::dark_cyan, Color::dark_magenta,
                              Color::dark_yellow};
  Regular_hexagon h{Point{0, 0}, rr};

  const int x_max = point(0).x + width() - h.width() / 2;
  const int y_max = point(0).y + height() - h.height() / 2;
  const int dx = h.width() + h.edge();
  const int dy = h.height() / 2;

  int y = point(0).y + dy;
  for (int i = 0; y <= y_max; ++i, y += dy)
  {
    int x = point(0).x + h.width() / 2;
    if (i % 2)
      x += dx / 2;

    for (; x <= x_max; x += dx)
    {
      tile.push_back(new Regular_hexagon{Point{x, y}, rr});
      tile[tile.size() - 1].set_fill_color(colors[i % colors.size()]);
    }
  }

  set_color(Color::invisible);
}

void Hexagon_tile::move(int dx, int dy)
{
  Rectangle::move(dx, dy);
  for (int i = 0; i < tile.size(); ++i)
    tile[i].move(dx, dy);
}

void Hexagon_tile::draw_lines() const
{
  Rectangle::draw_lines();
  for (int i = 0; i < tile.size(); ++i)
    tile[i].draw();
}

}  // namespace Graph_lib
