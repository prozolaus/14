#include "Simple_window.h"
#include "Graph.h"

struct Striped_rectangle : Rectangle
{
  using Rectangle::Rectangle;
  void draw_lines() const override;

private:
  int h = Rectangle::height();
  int w = Rectangle::width();
};

void Striped_rectangle::draw_lines() const
{
  if (fill_color().visibility())
  { // fill
    fl_color(fill_color().as_int());
    const int step = 2;
    for (int i = step; i < h; i += step)
      fl_line(point(0).x, point(0).y + i, point(0).x + w - 1, point(0).y + i);
  }

  if (color().visibility())
  { // lines on top of fill
    fl_color(color().as_int());
    fl_rect(point(0).x, point(0).y, w, h);
  }
}

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  const int a = 600;
  const int b = 400;
  Striped_rectangle rec{center, a, b};
  rec.move(-a / 2, -b / 2);
  rec.set_fill_color(Color(240));
  win.attach(rec);

  win.wait_for_button();
}
