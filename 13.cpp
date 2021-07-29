#include "Simple_window.h"
#include "Graph.h"

struct Arrow : Line
{
  using Line::Line;
  void draw_lines() const;
};

void Arrow::draw_lines() const
{
  Line::draw_lines();
  // add arrowhead: p2 and two points
  double line_len =
      sqrt(double(pow(point(1).x - point(0).x, 2) + pow(point(1).y - point(0).y, 2))); // length of p1p2

  const double k1 = 25;
  const double k2 = 5;

  // coordinates of the a point on p1p2 with distance 25 from p2
  double pol_x = k1 / line_len * point(0).x + (1 - k1 / line_len) * point(1).x;
  double pol_y = k1 / line_len * point(0).y + (1 - k1 / line_len) * point(1).y;

  // pl is 5 away from p1p2 on the "left", pl_pol is orthogonal to p1p2
  double pl_x = pol_x + k2 / line_len * (point(1).y - point(0).y);
  double pl_y = pol_y + k2 / line_len * (point(0).x - point(1).x);

  // pr is 5 away from p1p2 on the "right", pr_pol is orthogonal to p1p2a
  double pr_x = pol_x + k2 / line_len * (point(0).y - point(1).y);
  double pr_y = pol_y + k2 / line_len * (point(1).x - point(0).x);

  // draw arrowhead - is always filled in line color
  if (color().visibility())
  {
    fl_begin_complex_polygon();
    fl_vertex(point(1).x, point(1).y);
    fl_vertex(pl_x, pl_y);
    fl_vertex(pr_x, pr_y);
    fl_end_complex_polygon();
  }
}

//----------------------------------------------------------------

struct Binary_tree : Shape
{
  Binary_tree(int level) : lvl{level} { add_tree(); }
  Binary_tree(int level, int radius) : lvl{level}, r{radius} { add_tree(); }
  Binary_tree(int level, int radius, int vertical_distance, bool line_type = false, Color line_color = fl_color(), bool arrow_direction = false) : lvl{level}, r{radius}, s{vertical_distance}, ltype{line_type}, lcolor{line_color}, arrowdir{arrow_direction} { add_tree(); }
  void draw_lines() const override;

protected:
  int get_radius() { return r; }
  Vector_ref<Line> &get_lines() { return lines; }

private:
  int lvl, r = 10, s = 50;
  bool ltype = false;    //false - Line, true - Arrow
  bool arrowdir = false; //false - down, true - up
  Color lcolor = fl_color();
  Point btroot{x_max() / 2 - r, r}; // store top-left corner (point for circle)
  Vector_ref<Line> lines;
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
      Point par_center{parents[j].x + r, parents[j].y + r}, pstart, pend;
      add(Point{parents[j].x - int(x_max() / pow(2, i)), parents[j].y + s});
      add(Point{parents[j].x + int(x_max() / pow(2, i)), parents[j].y + s});
      Point p1{point(number_of_points() - 2).x + r, point(number_of_points() - 2).y + r};
      Point p2{point(number_of_points() - 1).x + r, point(number_of_points() - 1).y + r};

      if (ltype == true)
      {
        pstart = (!arrowdir) ? par_center : p1;
        pend = (!arrowdir) ? p1 : par_center;
        lines.push_back(new Arrow{pstart, pend});

        pstart = (!arrowdir) ? par_center : p2;
        pend = (!arrowdir) ? p2 : par_center;
        lines.push_back(new Arrow{pstart, pend});
      }
      else
      {
        lines.push_back(new Line{par_center, p1});
        lines.push_back(new Line{par_center, p2});
      }
      lines[lines.size() - 1].set_color(lcolor);
      lines[lines.size() - 2].set_color(lcolor);
    }
  }
}

void Binary_tree::draw_lines() const
{
  if (color().visibility())
    for (int i = 0; i < number_of_points(); i++)
      fl_arc(point(i).x, point(i).y, r + r, r + r, 0, 360);

  fl_color(lcolor.as_int());
  for (int i = 0; i < lines.size(); i++)
    lines[i].draw();

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

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  Binary_tree bt{7, 8, 100, true, Color::blue, true};
  bt.set_fill_color(1);
  win.attach(bt);

  win.wait_for_button();
}
