#include <iostream>
#include <string>
using namespace std;

// 抽象类
class Builder {
 public:
  virtual void setSize() = 0;
  virtual void setLocation() = 0;
  virtual void getHouse() = 0;
  virtual ~Builder() = default;
};

class House {
 private:
  int size;
  string location;

 public:
  void setSize(int size) { this->size = size; }
  void setLocation(string location) { this->location = location; }
  void getHouse() {
    cout << "size: " << size << endl;
    cout << "location: " << location << endl;
  }
};

// 大House
class BigHouseBuilder : public Builder {
 private:
  House* house;

 public:
  BigHouseBuilder() { house = new House(); }
  void setSize() override {
    cout << "big size" << endl;
    house->setSize(100);
  }
  void setLocation() override {
    cout << "great location" << endl;
    house->setLocation("great location");
  }
  void getHouse() override { cout << "get big house" << endl; }
  ~BigHouseBuilder() = default;
};

// 小House
class SmallHouseBuilder : public Builder {
 private:
  House* house;

 public:
  SmallHouseBuilder() { house = new House(); }
  void setSize() override {
    cout << "small size" << endl;
    house->setSize(10);
  }
  void setLocation() override {
    cout << "bad location" << endl;
    house->setLocation("bad location");
  }
  void getHouse() override { cout << "get small house" << endl; }
  ~SmallHouseBuilder() = default;
};

// 指导者类 并不是必须的
class HouseDirector {
 public:
  void BuildBigHouse(Builder* builder) {
    builder->setSize();
    builder->setLocation();
  }
  void BuildSmallHouse(Builder* builder) {
    builder->setSize();
    builder->setLocation();
  }
};

int main() {
  Builder* bigBuilder = new BigHouseBuilder();
  Builder* smallBuilder = new SmallHouseBuilder();
  HouseDirector* director = new HouseDirector();
  director->BuildBigHouse(bigBuilder);
  director->BuildSmallHouse(smallBuilder);
  bigBuilder->getHouse();
  smallBuilder->getHouse();
  return 0;
}