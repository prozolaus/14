#include "Simple_window.h"
#include "Graph.h"

int main()
{
  using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

  Point top_left{0, 0}; //will be top left corner of window
  Point center{x_max() / 2, y_max() / 2};

  Simple_window win{top_left, x_max(), y_max(), "Canvas"};

  Striped_closed_polyline scpoly;

  Point p1{300, 100};
  Point p2{250, 350};
  Point p3{5, 500};
  Point p4{500, 650};
  Point p5{1000, 500};
  Point p6{900, 150};
  Point p7{700, 10};

  scpoly.add(p1);
  scpoly.add(p2);
  scpoly.add(p3);
  scpoly.add(p4);
  scpoly.add(p5);
  scpoly.add(p6);
  scpoly.add(p7);

  scpoly.set_fill_color(Color(1));

  win.attach(scpoly);

  win.wait_for_button();
}

/*
  Point p1{300, 100};
  Point p2{250, 350};
  Point p3{5, 500};
  Point p4{500, 650};
  Point p5{1000, 500};
*/

/*
    cout << "Min y: " << min_y << ", point #" << min_y_p << endl;
    cout << "Max y: " << max_y << ", point #" << max_y_p << endl;
*/

/*
    for (Point p : vpl)
      cout << "vpl: " << p.x << ", " << p.y << endl;

    for (Point p : vpr)
      cout << "vpr: " << p.x << ", " << p.y << endl;
*/
/*
    for (Point p : vpl)
      cout << "sorted vpl: " << p.x << ", " << p.y << endl;

    for (Point p : vpr)
      cout << "sorted vpr: " << p.x << ", " << p.y << endl;

    cout << "vpl.size(): " << vpl.size() << endl;
    cout << "vpr.size(): " << vpr.size() << endl;
*/
/*     
      cout << p1.x << ", " << p1.y << "; ";
      cout << p2.x << ", " << p2.y << "; ";
      cout << vpl[j].x << ", " << vpl[j].y << "; ";
      cout << vpl[j + 1].x << ", " << vpl[j + 1].y << "; ";
      //cout << vpr[k].x << ", " << vpr[k].y << "; ";
      //cout << vpr[k + 1].x << ", " << vpr[k + 1].y << "; ";
      cout << u.first << ", " << u.second << "; ";
*/

//cout << "j++ (no intersect)" << endl;

//cout << "k++ (no intersect)" << endl;

//cout << vplf[count].x << ", " << vplf[count].y << "; ";

//cout << vprf[count].x << ", " << vprf[count].y << endl;
