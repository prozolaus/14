#include "Simple_window.h"
#include "Graph.h"

struct Binary_tree : Shape
{
  Binary_tree(int level) : lvl{level} { add_tree(); }
  Binary_tree(int level, int radius) : lvl{level}, r{radius} { add_tree(); }
  Binary_tree(int level, int radius, int vertical_distance) : lvl{level}, r{radius}, s{vertical_distance} { add_tree(); }
  void draw_lines() const override;

protected:
  int get_radius() { return r; }
  Lines &get_lines() { return lines; }

private:
  int lvl, r = 10, s = 50;
  Point btroot{x_max() / 2 - r, r}; // store top-left corner (point for circle)
  Lines lines;
  void add_tree();
};

void Binary_tree::add_tree()
{
  if (lvl > 0)
    add(btroot);

  for (int i = 2; i <= lvl; i++)
  {
    vector<Point> parents;
    for (int k = 0; k < pow(2, i - 2); k++)
      parents.push_back(point(number_of_points() - k - 1));

    for (int j = 0; j < parents.size(); j++)
    {
      Point par_center{parents[j].x + r, parents[j].y + r};
      add(Point{parents[j].x - int(x_max() / pow(2, i)), parents[j].y + s});
      add(Point{parents[j].x + int(x_max() / pow(2, i)), parents[j].y + s});
      lines.add(par_center, Point{point(number_of_points() - 2).x + r, point(number_of_points() - 2).y + r});
      lines.add(par_center, Point{point(number_of_points() - 1).x + r, point(number_of_points() - 1).y + r});
    }
  }
}

void Binary_tree::draw_lines() const
{
  if (color().visibility())
    for (int i = 0; i < number_of_points(); i++)
      fl_arc(point(i).x, point(i).y, r + r, r + r, 0, 360);

  lines.draw();

  if (fill_color().visibility())
  { // fill
    fl_color(fill_color().as_int());
    for (int k = 0; k < number_of_points(); k++)
    {
      const int step = 1;
      for (int i = 0; i < r; i += step)
      {
        double angle = asin((double)i / r);
        int xx = r * cos(angle);
        fl_line(point(k).x + r - xx, point(k).y + r - i, point(k).x + r + xx - 1, point(k).y + r - i);
        fl_line(point(k).x + r - xx, point(k).y + r + i, point(k).x + r + xx - 1, point(k).y + r + i);
      }
    }
  }
}

//---------------------------------------------------------------------------------

struct Triangle_tree : Binary_tree
{
  using Binary_tree::Binary_tree;
  void draw_lines() const override;

private:
  int r = Binary_tree::get_radius();
  Lines &lines = Binary_tree::get_lines();
};

void Triangle_tree::draw_lines() const
{
  Vector_ref<Polygon> vt;
  if (color().visibility())
    for (int i = 0; i < number_of_points(); i++)
    {
      Point center{point(i).x + r, point(i).y + r};
      vt.push_back(new Polygon{Point{center.x, center.y - r},
                               Point{center.x + int(r * cos(210 * M_PI / 180)), center.y - int(r * sin(210 * M_PI / 180))},
                               Point{center.x + int(r * cos(330 * M_PI / 180)), center.y - int(r * sin(330 * M_PI / 180))}});
      vt[i].draw_lines();
    }

  lines.draw();

  if (fill_color().visibility())
  { //fill
    fl_color(fill_color().as_int());
    for (int i = 0; i < number_of_points(); ++i)
    {
      fl_begin_complex_polygon();
      for (int j = 0; j < 3; j++)
        fl_vertex(vt[i].point(j).x, vt[i].point(j).y);
      fl_end_complex_polygon();
    }
    fl_color(color().as_int()); // reset color
  }
}

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  Triangle_tree tt{4, 40, 100};
  tt.set_fill_color(1);
  tt.set_style(Line_style(Line_style::solid,3));
  Shape& shape = tt;
  win.attach(shape);

  win.wait_for_button();
}
