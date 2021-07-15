#include "Simple_window.h"
#include "Graph.h"

class Animal
{
public:
  string get_name() const { return nm; }
  virtual string speak() const = 0;

protected:
  Animal(string name) : nm{name} {}

private:
  string nm;
};

class Dog : public Animal
{
public:
  Dog(string name) : Animal(name) {}
  string speak() const { return "Woof!"; }
};

class Cat : public Animal
{
public:
  Cat(string name) : Animal(name) {}
  string speak() const { return "Meow!"; }
};

string animal_speak(const Animal &animal)
{
  ostringstream os;
  os << animal.get_name() << " says " << animal.speak();
  return os.str();
}

int main()
{

  Dog aza{"Aza"};
  Cat dusia{"Dusia"};

  cout << animal_speak(aza) << endl;
  cout << animal_speak(dusia) << endl;

}
