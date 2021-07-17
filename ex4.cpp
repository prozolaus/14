#include "Simple_window.h"
#include "Graph.h"

struct Immobile_Circle : Circle
{
  using Circle::Circle;

  void move(int dx, int dy) override {};
};

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  Immobile_Circle c{center,100};
  win.attach(c);

  win.wait_for_button();
  c.move(200,200);
  win.wait_for_button();

}
