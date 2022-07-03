/**
 * 适配器模式
 * 将一个类的接口转换成客户希望的另外一个接口。
 * 适配器模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
 */

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

// 圆钉
class RoundPeg {
 private:
  int radius;

 public:
  RoundPeg(int radius) { this->radius = radius; }
  int getRadius() { return radius; }
};

// 圆孔
class RoundHole {
 private:
  int radius;

 public:
  RoundHole(int radius) { this->radius = radius; }
  int getRadius() { return radius; }
  // 圆钉能打在圆孔里的条件是圆孔的半径大于圆钉的半径
  bool fits(RoundPeg peg) { return (peg.getRadius() <= radius); }
};

// 方钉
class SquarePeg {
 private:
  int width;

 public:
  SquarePeg(int width) : width(width) {}
  int getLendth() { return width; }
};

// 适配器 让方钉适配圆孔
class SquarePegAdapter : public RoundPeg {
 private:
  SquarePeg peg;

 public:
  SquarePegAdapter(SquarePeg peg) : RoundPeg(peg.getLendth()), peg(peg) {}
  int getRadius() { return peg.getLendth() * sqrt(2) / 2; }
};
int main() {
  RoundHole round_hold(5);
  RoundPeg round_peg(5);
  SquarePeg square_peg(5);
  SquarePegAdapter square_peg_adapter(square_peg);
  cout << "round_hold.fits(round_peg) = " << round_hold.fits(round_peg) << endl;
  // 类型不匹配 不能通过编译
  // cout << "round_hold.fits(square_peg) = " << round_hold.fits(square_peg) << endl;
  cout << "round_hold.fits(square_peg_adapter) = " << round_hold.fits(square_peg_adapter) << endl;
}