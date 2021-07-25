#include "Simple_window.h"
#include "Graph.h"

class Group
{
public:
  void add_new_shape(Shape *s) { vs.push_back(s); }
  Shape &get_shape(int i) { return vs[i]; }
  int number_of_shapes() { return vs.size(); }

private:
  Vector_ref<Shape> vs;
};

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};
  int side = 50;

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  Group chessboard;
  Color first{Color::black}, second{Color::white}, temp{Color::black};

  for (int i = 0, count = 0; i < 8; i++)
  {
    temp = first;
    first = second;
    second = temp;
    for (int j = 0; j < 8; j++)
    {
      chessboard.add_new_shape(new Rectangle{Point{100 + side * j, 100 + side * i}, side, side});
      chessboard.get_shape(count).set_fill_color((j % 2 == 0) ? first : second);
      win.attach(chessboard.get_shape(count++));
    }
  }

  win.wait_for_button();
}

/*
  Group shapes;
  for (int i = 10; i < 300; i += 10)
    shapes.add_new_shape(new Circle{center, i});

  int n = shapes.number_of_shapes();
  for (int i = 0; i < n; i++)
  {
    Shape &s = shapes.get_shape(i);
    s.set_color(255-i*4);
    s.set_style(Line_style{Line_style::solid,3});
    win.attach(s);
  }
*/