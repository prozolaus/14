#include "Simple_window.h"
#include "Graph.h"

struct Iterator
{
  virtual double *next() = 0;
};

struct Vector_iterator : Iterator
{
  Vector_iterator(const vector<double> &vdd) : vd{vdd} {}
  double *next() override;

private:
  vector<double> vd;
  double *ptr = &vd[0], *ptr0 = &vd[0];
};

double *Vector_iterator::next()
{
  return (vd.size() <= (ptr - ptr0)) ? nullptr : ptr++;
}

//---------------------------------------------------------------------------------------------

struct List_iterator : Iterator
{
  List_iterator(initializer_list<double> &vdd) : li{vdd} {}
  double *next() override;

private:
  vector<double> li;
  double *ptr0 = &li[0];
  double *ptr = ptr0; 
  
};

double *List_iterator::next()
{
  return (li.size() <= (ptr - ptr0)) ? nullptr : ptr++;
}


void print(Iterator &iter)
{
  double *ptr;
  while (true)
  {
    ptr = iter.next();
    if (ptr == nullptr)
      break;
    else
      cout << *ptr << "; ";
  }
  cout << endl;
}

int main()
{
  //vector<double> vd{9, 8, 7, 6, 5};
  //Vector_iterator vi = vd;
  //print(vi);

  initializer_list<double> list{9, 8, 7, 6, 5};
  List_iterator li = list;
  //cout << *list.begin() << endl;
  print(li);

}
