#include "Simple_window.h"
#include "Graph.h"

struct Octagon : Closed_polyline
{
    Octagon(Point center, int radius);

private:
    Point c;
    int R;
    Point coords(const double &angle);
};

Octagon::Octagon(Point center, int radius)
    : c{center},  R{radius}
{
    int step = round(360 / 8);
    for (double i = 0; i < 360; i += step)
        add(coords(i));
}

Point Octagon::coords(const double &angle)
{
    int x = round(R * cos(angle * M_PI / 180));
    int y = round(R * sin(angle * M_PI / 180));
    return Point{c.x + x, c.y - y};
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 1366;
    const int height = 768;
    Simple_window win{top_left, width, height, "Canvas"};
    int thickness = 5;
    Line_style lst{Line_style::solid, thickness};
    Point center{x_max() / 2, y_max() / 2};
    const int radius = 300;

    Octagon o{center, radius};

    //o.add(Point{10,10});
    //o.set_color(Color::dark_blue);
    //Color col = o.color();
    //cout << col.as_int() << endl;
    //o.move(100,100);
    //o.set_style(lst);
    
    win.attach(o);
    win.wait_for_button();
}