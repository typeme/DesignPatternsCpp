#include <iostream>
using namespace std;
class Button {
 public:
  virtual void click() = 0;
  virtual ~Button() = default;
};

class CheckBox {
 public:
  virtual void check() = 0;
  virtual ~CheckBox() = default;
};

class WinButton : public Button {
 public:
  void click() { cout << "win button click" << endl; }
  ~WinButton() = default;
};

class WinCheckBox : public CheckBox {
 public:
  void check() { cout << "win checkbox check" << endl; }
  ~WinCheckBox() = default;
};

class MacButton : public Button {
 public:
  void click() { cout << "mac button click" << endl; }
  ~MacButton() = default;
};

class MacCheckBox : public CheckBox {
 public:
  void check() { cout << "mac checkbox check" << endl; }
  ~MacCheckBox() = default;
};

class GUIFactory {
 public:
  virtual Button* CreateButtion() = 0;
  virtual CheckBox* CreateCheckBox() = 0;
  virtual ~GUIFactory() = default;
};

class MacGUIFactory : public GUIFactory {
 public:
  Button* CreateButtion() override { return new MacButton(); }

  CheckBox* CreateCheckBox() override { return new MacCheckBox(); }
  ~MacGUIFactory() = default;
};
class WinGUIFactory : public GUIFactory {
 public:
  Button* CreateButtion() override { return new WinButton(); }

  CheckBox* CreateCheckBox() override { return new WinCheckBox(); }
  ~WinGUIFactory() = default;
};

int main() {
  GUIFactory* factory = new WinGUIFactory();
  Button* button = factory->CreateButtion();
  button->click();
  CheckBox* checkbox = factory->CreateCheckBox();
  checkbox->check();
  delete button;
  delete checkbox;
  delete factory;
  return 0;
}
