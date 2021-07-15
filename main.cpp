#include "Simple_window.h"
#include "Graph.h"

class Animal
{
public:
  //void set_name(string name) { nm = name; }
  string get_name() const { return nm; }
  virtual string speak() const = 0;
  string animal_speak();

protected:
  //Animal() : nm{"???"} {}
  Animal(string name) : nm{name} {}

private:
  string nm;
};

string Animal::animal_speak()
{
  ostringstream os;
  os << get_name() << " says " << speak();
  return os.str();
}

class Dog : public Animal
{
public:
  //Dog() : Animal() {}
  Dog(string name) : Animal(name) {}
  string speak() const { return "Woof!"; }
};

class Cat : public Animal
{
public:
  //Cat() : Animal() {}
  Cat(string name) : Animal(name) {}
  string speak() const { return "Meow!"; }
};

int main()
{

  Dog aza{"Aza"};
  Cat dusia{"Dusia"};
  //dusia.set_name("Musia");

  cout << aza.animal_speak() << endl;
  cout << dusia.animal_speak() << endl;
}
