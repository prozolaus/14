#include "Simple_window.h"
#include "Graph.h"

class B1
{
public:
    virtual void vf() { cout << "B1::vf()" << endl; };
    void f() { cout << "B1::f()" << endl; };
    virtual void pvf() = 0;
};

class D1 : public B1
{
public:
    void vf() override { cout << "D1::vf()" << endl; };
    void f() { cout << "D1::f()" << endl; };
    void pvf() override { cout << "D1::pvf()" << endl; };
};

class D2 : public D1
{
public:
    void pvf() override { cout << "D2::pvf()" << endl; };
};

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};

    //B1 first;
    //first.vf();
    //first.f();

    D1 second;
    second.vf();
    second.f();
    second.pvf();

    D2 third;
    third.vf();
    third.f();
    third.pvf();

    B1 &ref = third;
    ref.vf();
    ref.f();
    ref.pvf();

    //win.wait_for_button();
}
