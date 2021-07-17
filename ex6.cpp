#include "Simple_window.h"
#include "Graph.h"

struct Striped_Circle : Circle
{
  using Circle::Circle;
  void draw_lines() const override;

private:
  int r = Circle::radius();
};

void Striped_Circle::draw_lines() const
{
  if (color().visibility())
    fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);

  if (fill_color().visibility())
  { // fill
    fl_color(fill_color().as_int());
    const int step = 15;
    for (int i = 0; i < r; i += step)
    {
      double angle = asin((double)i / r);
      int xx = r * cos(angle);
      fl_line(point(0).x + r - xx, point(0).y + r - i, point(0).x + r + xx - 1, point(0).y + r - i);
      fl_line(point(0).x + r - xx, point(0).y + r + i, point(0).x + r + xx - 1, point(0).y + r + i);
    }
  }
}

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  Striped_Circle c{center, 300};
  c.set_fill_color(Color(1));
  win.attach(c);

  win.wait_for_button();
}
