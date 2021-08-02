#include "Simple_window.h"
#include "Graph.h"

class Controller
{
public:
  virtual void on() = 0;
  virtual void off() = 0;
  virtual void set_level(int) = 0;
  virtual void show() = 0;
};

class Sound : public Controller
{
public:
  void on() override { sound_state = true; }
  void off() override { sound_state = false; }
  void set_level(int level) override;
  void show() override;

private:
  bool sound_state = false;
  int sound_level = 0;
};

void Sound::set_level(int level)
{
  if (level < 0 || level > 10)
    error("Sound level must be from 0 to 10 points!");
  else
    sound_level = level;
}

void Sound::show()
{
  cout << "Sound is " << (sound_state ? "on" : "off");
  cout << ".\nVolume level is " << sound_level << ".\n";
}

//------------------------------------------------------------------------

class LC_Controller : public Controller
{
public:
  LC_Controller(Shape &shape) : s{shape} {}
  void on() override;
  void off() override;
  void set_level(int color_level) override;
  void show() override { cout << "Shape color is " << s.color().as_int() << endl; }

private:
  Shape &s;
  bool visibility = true;
  Color clr{s.color()};
};

void LC_Controller::on()
{
  clr.set_visibility(Color::visible);
  s.set_color(clr);
  visibility = true;
}

void LC_Controller::off()
{
  clr.set_visibility(Color::invisible);
  s.set_color(clr);
  visibility = false;
}

void LC_Controller::set_level(int color_level)
{
  if (color_level < 0 || color_level > 255)
    error("Color level must be from 0 to 255 points!");
  else
  {
    clr = color_level;
    clr.set_visibility(visibility ? Color::visible : Color::invisible);
    s.set_color(clr);
  }
}

int main()
{
  /*
  Sound sound;
  sound.on();
  sound.set_level(11);
  sound.show();
*/

  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  Circle c{Point{100, 100}, 100};
  LC_Controller lc{c};
  lc.set_level(Color::blue);
  lc.off();
  lc.set_level(Color::red);
  lc.on();
  //lc.show();

  win.attach(c);
  win.wait_for_button();
}
