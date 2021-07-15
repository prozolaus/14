#include "Simple_window.h"
#include "Graph.h"

class B2
{
public:
    virtual void pvf() = 0;
};

class D21 : public B2
{
    string s = "Hello";

public:
    void pvf() override { cout << s << endl; }
};

class D22 : public B2
{
    int i = 100;

public:
    void pvf() override { cout << i << endl; }
};

void f(B2 &b2) { b2.pvf(); }



int main()
{
    D21 first;
    D22 second;

    f(first);
    f(second);
}
