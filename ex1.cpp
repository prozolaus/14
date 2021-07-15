#include "Simple_window.h"
#include "Graph.h"

int sgn(double d)
{
  if (d < 0)
    return -1;
  else if (d == 0)
    return 0;
  else
    return 1;
}

vector<Point> coordinates(double a, double b, double m, double n, int N, Point c)
{
  vector<Point> vp;
  double angle;
  int x, y, tempx = 0, tempy = 0;
  for (int i = 0; i < N; i++)
  {
    angle = 2 * M_PI * i / N;
    x = pow(abs(cos(angle)), (2 / m)) * a * sgn(cos(angle));
    y = pow(abs(sin(angle)), (2 / n)) * b * sgn(sin(angle));
    if (tempx == x && tempy == y)
      continue;
    tempx = x;
    tempy = y;
    vp.push_back(Point{x + c.x, y + c.y});
  }
  return vp;
}

struct Smiley : Circle
{
  using Circle::Circle;
  void draw_lines() const override;
};

void Smiley::draw_lines() const
{
  Circle::draw_lines();
  Point fc = Circle::center();   //face center
  int fr = Circle::radius();     //face radius
  int eye_d = fr / 5;            //eye diameter
  int eye_r = eye_d / 2;         //eye radius
  int k = fr / 2.5;              //eyes center position displacement relative to the face center
  Point lec{fc.x - k, fc.y - k}; //lec - left eye center
  Point rec{fc.x + k, fc.y - k}; //rec - right eye center
  //we need to set the top left corners to draw our eyes (circles)
  fl_arc(lec.x - eye_r, lec.y - eye_r, eye_d, eye_d, 0, 360); //draw the left eye
  fl_arc(rec.x - eye_r, rec.y - eye_r, eye_d, eye_d, 0, 360); //draw the right eye
  int w = fr * 1.1;                                           //mouth (ellipse) width
  int h = fr / 2;                                             //mouth (ellipse) height
  int l = fr / 10;                                            //distance from face radius to center of mouth
  fl_arc(fc.x - w / 2, fc.y + l, w, h, 200, 340);             //draw the smile
}

struct Frowny : Circle
{
  using Circle::Circle;
  void draw_lines() const override;
};

void Frowny::draw_lines() const
{
  Circle::draw_lines();
  Point fc = Circle::center();   //face center
  int fr = Circle::radius();     //face radius
  int eye_d = fr / 5;            //eye diameter
  int eye_r = eye_d / 2;         //eye radius
  int k = fr / 2.5;              //eyes center position displacement relative to the face center
  Point lec{fc.x - k, fc.y - k}; //lec - left eye center
  Point rec{fc.x + k, fc.y - k}; //rec - right eye center
  //we need to set the top left corners to draw our eyes (circles)
  fl_arc(lec.x - eye_r, lec.y - eye_r, eye_d, eye_d, 0, 360); //draw the left eye
  fl_arc(rec.x - eye_r, rec.y - eye_r, eye_d, eye_d, 0, 360); //draw the right eye
  int w = fr * 1.1;                                           //mouth (ellipse) width
  int h = fr / 2;                                             //mouth (ellipse) height
  int l = fr / 10 + h / 2;                                    //distance from face radius to center of mouth
  fl_arc(fc.x - w / 2, fc.y + l, w, h, 20, 160);              //draw the frowny smile
}

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  int radius = 150;

  Point sm{center.x - center.x / 2, center.y};
  Smiley smiley{sm, radius};
  win.attach(smiley);

  Ellipse hat_sm{Point{smiley.center().x, smiley.center().y - smiley.radius()}, radius * 1.5, radius / 5};
  win.attach(hat_sm);

  vector<Point> vp = coordinates(100, 100, 4, 4, 200, Point{smiley.center().x, smiley.center().y - smiley.radius() - 100});
  Closed_polyline poly;
  for (Point p : vp)
    poly.add(p);
  win.attach(poly);


  Point fr{center.x + center.x / 2, center.y};
  Frowny frowny{fr, radius};
  win.attach(frowny);

  Ellipse hat_fr{Point{frowny.center().x, frowny.center().y - frowny.radius()}, radius * 1.5, radius / 5};
  win.attach(hat_fr);

  vector<Point> vp2 = coordinates(100, 100, 4, 4, 200, Point{frowny.center().x, frowny.center().y - frowny.radius() - 100});
  Closed_polyline poly2;
  for (Point p : vp2)
    poly2.add(p);
  win.attach(poly2);

  win.wait_for_button();
}
