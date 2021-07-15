#include "Simple_window.h"
#include "Graph.h"

class B1
{
public:
    virtual void vf() { cout << "B1::vf()" << endl; };
    void f() { cout << "B1::f()" << endl; };
};

class D1 : public B1
{
public:
    void vf() override { cout << "D1::vf()" << endl; };
};

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};

    D1 test;
    test.vf();
    test.f();

    //win.wait_for_button();
}
