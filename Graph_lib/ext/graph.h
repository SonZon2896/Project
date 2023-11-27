#ifndef GRAPH_EXT_GUARD
#define GRAPH_EXT_GUARD 1

#include <limits>

#include <Graph_lib/Graph.h>

namespace Graph_lib {

struct Arc : Ellipse
{
  /// center, max and min distance from center,
  /// start and end angles of the curve
  Arc(Point p, int ww, int hh, int alpha, int beta);

  void set_start_angle (int a) { phi1 = a; }

  void set_end_angle (int a) { phi2 = a; }

  int start_angle () const { return phi1; }

  int end_angle () const { return phi2; }

protected:
  void draw_lines () const override;

private:
  int phi1, phi2;
};

/// @class Box -- rectangle with rounded corners
struct Box : Rectangle
{
  Box(Point xy, int ww, int hh, int radius = automatic);
  Box(Point x, Point y, int radius = automatic);

  void set_roundness (int radius);

  int roundness () const { return r; }

protected:
  void draw_lines () const override;

private:
  int r;  // radius of roundness

  enum
  {
    automatic = std::numeric_limits<int>::max()
  };
};

struct Regular_hexagon : Shape
{
  /// with center at @param c and circumcircle radius @param rr
  Regular_hexagon(Point c, int r);

  Point center () const;
  int width () const;
  int height () const;
  int edge () const;  /// hexagon edge length

protected:
  void draw_lines () const override;
};

/// tile a rectangle with regular hexagons
struct Hexagon_tile : Rectangle
{
  Hexagon_tile(Point p, int ww, int hh, int rr);

  void move (int dx, int dy) override;

protected:
  void draw_lines () const override;

private:
  Vector_ref<Regular_hexagon> tile;
};

}  // namespace Graph_lib

#endif  // GRAPH_EXT_GUARD
