#include <iostream>
#include <string>
using namespace std;

class Button {
 public:
  virtual void render() = 0;
  virtual void onClick() = 0;
  virtual ~Button() {}
};

class WindowsButton : public Button {
 public:
  ~WindowsButton() {}
  void render() {
    cout << "windows render" << endl;
    return;
  }

  void onClick() {
    cout << "windows onClick" << endl;
    return;
  }
};

class HTMLButton : public Button {
 public:
  ~HTMLButton() {}
  void render() {
    cout << "HTML render" << endl;
    return;
  }

  void onClick() {
    cout << "HTML onClick" << endl;
    return;
  }
};

class Dialog {
 public:
  virtual ~Dialog() {}
  virtual Button* createButton() = 0;

  void render() {
    Button* button = createButton();
    button->onClick();
    button->render();
  }
};

class WindowsDialog : public Dialog {
 public:
  Button* createButton() { return new WindowsButton(); }
};

class WebDialog : public Dialog {
 public:
  Button* createButton() { return new HTMLButton(); }
};

int main() {
  Dialog* a = new WebDialog();
  a->render();
}
