#include "Simple_window.h"
#include "Graph.h"

struct Face : Circle
{
  using Circle::Circle;
  void draw_lines() const override;
  int mouth_width() const { return w; }
  //void put_on_hat() const;

private:
  virtual void draw_mouth() const;

  Point fc = Circle::center(); //face center
  int fr = Circle::radius();   //face radius
  int w = fr * 1.1;            //mouth (ellipse) width
};

void Face::draw_lines() const
{
  Circle::draw_lines();
  int eye_d = fr / 5;            //eye diameter
  int eye_r = eye_d / 2;         //eye radius
  int k = fr / 2.5;              //eyes center position displacement relative to the face center
  Point lec{fc.x - k, fc.y - k}; //lec - left eye center
  Point rec{fc.x + k, fc.y - k}; //rec - right eye center
  //we need to set the top left corners to draw our eyes (circles)
  fl_arc(lec.x - eye_r, lec.y - eye_r, eye_d, eye_d, 0, 360); //draw the left eye
  fl_arc(rec.x - eye_r, rec.y - eye_r, eye_d, eye_d, 0, 360); //draw the right eye
  draw_mouth();
  //put_on_hat();
}

void Face::draw_mouth() const
{
  int l = fr / 2; //distance from face radius to center of mouth
  fl_line(fc.x - w / 2, fc.y + l, fc.x + w / 2, fc.y + l);
}
/*
void Face::put_on_hat() const
{
  Point p1{fc.x - fr * 1.5, fc.y - 0.7 * fr};
  Point p2{fc.x + fr * 1.5, fc.y - 0.7 * fr};
  Point p3{fc.x, fc.y - 2 * fr};

  fl_line(p1.x, p1.y, p2.x, p2.y);
  fl_line(p2.x, p2.y, p3.x, p3.y);
  fl_line(p3.x, p3.y, p1.x, p1.y);
}
*/
//-------------------------------------------------------------------------------------

struct Smiley : Face
{
  using Face::Face;

private:
  void draw_mouth() const override;
};

void Smiley::draw_mouth() const
{
  int fr = Circle::radius();
  Point fc = Circle::center();
  int w = Face::mouth_width();
  int h = fr / 2;                                 //mouth (ellipse) height
  int l = fr / 10;                                //distance from face radius to center of mouth
  fl_arc(fc.x - w / 2, fc.y + l, w, h, 200, 340); //draw the smile
}

struct Frowny : Face
{
  using Face::Face;

private:
  void draw_mouth() const override;
};

void Frowny::draw_mouth() const
{
  int fr = Circle::radius();
  Point fc = Circle::center();
  int w = Face::mouth_width();
  int h = fr / 2;                                //mouth (ellipse) height
  int l = fr / 10 + h / 2;                       //distance from face radius to center of mouth
  fl_arc(fc.x - w / 2, fc.y + l, w, h, 20, 160); //draw the frowny smile
}

struct Hat : Polygon
{
  Hat(Point face_center, int face_radius);
private:
  Point fc;
  int fr;
};

Hat::Hat(Point face_center, int face_radius)
    : fc{face_center}, fr{face_radius}
{
  Point p1{fc.x - fr * 1.5, fc.y - 0.7 * fr};
  Point p2{fc.x + fr * 1.5, fc.y - 0.7 * fr};
  Point p3{fc.x, fc.y - 2 * fr};
  add(p1);
  add(p2);
  add(p3);
}


int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  int radius = 100;

  Point sm{center.x - center.x / 2, center.y};
  Smiley smiley{sm, radius};
  win.attach(smiley);

  Hat hat_sm{sm,radius};
  hat_sm.set_fill_color(Color(1));
  win.attach(hat_sm);

  Point pf{center.x, center.y};
  Face face{pf, radius};
  win.attach(face);

  Hat hat_pf{pf,radius};
  hat_pf.set_fill_color(Color(3));
  win.attach(hat_pf);

  Point fr{center.x + center.x / 2, center.y};
  Frowny frowny{fr, radius};
  win.attach(frowny);

  Hat hat_fr{fr,radius};
  hat_fr.set_fill_color(Color(4));
  win.attach(hat_fr);

  win.wait_for_button();
}
