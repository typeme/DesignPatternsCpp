#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shape {
 public:
  string color;

 public:
  Shape(string color) { this->color = color; }
  Shape(Shape& other) { this->color = other.color; }
  virtual Shape* clone() = 0;
  virtual ~Shape() { cout << "Shape destructor" << endl; }
};

class Circle : public Shape {
 public:
  int radius;

 public:
  Circle(string color, int radius) : Shape(color) { this->radius = radius; }
  Circle(Circle* c) : Shape(c->color) { this->radius = c->radius; }
  Circle* clone() override { return new Circle(this); }
  ~Circle() { cout << "Circle destructor" << endl; }
};

class Rectangle : public Shape {
 public:
  int length;
  int width;

 public:
  Rectangle(string color, int legth, int width) : Shape(color) {
    this->length = legth;
    this->width = width;
  }
  Rectangle(Rectangle* r) : Shape(r->color) {
    this->length = r->length;
    this->width = r->width;
  }
  Rectangle* clone() override { return new Rectangle(this); }
  ~Rectangle() { cout << "Rectangle destructor" << endl; }
};

int main() {
  vector<Shape*> shapes;
  shapes.push_back(new Circle("red", 10));
  shapes.push_back(new Rectangle("blue", 10, 20));
  shapes.push_back(new Circle("green", 20));
  shapes.push_back(new Rectangle("yellow", 30, 40));
  vector<Shape*> new_shapes;
  for (auto shape : shapes) {
    new_shapes.push_back(shape->clone());
  }
}