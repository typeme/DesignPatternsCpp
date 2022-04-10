#include <iostream>
#include <thread>
using namespace std;
/**
 * 线程不安全版本的单例模式
 * 缺点:
 * 1. 存在内存泄露的风险
 * 2. 多线程下会有问题
 */

// 懒汉版实现: 运行时才会生成对象
class LazyLoadSingleton {
 private:
  int value;
  // 单例模式不允许clone
  LazyLoadSingleton(LazyLoadSingleton&) = delete;
  // 单例模式不允许赋值
  void operator=(const LazyLoadSingleton&) = delete;
  // constructor 私有
  LazyLoadSingleton(int value) { this->value = value; };

 public:
  // 没有对应的析构 内存会泄露
  static LazyLoadSingleton* singleton;
  ~LazyLoadSingleton(){};
  static LazyLoadSingleton* getInstance(int value) {
    // 线程不安全
    if (singleton == nullptr) {
      singleton = new LazyLoadSingleton(value);
    }
    return singleton;
  }
  int getValue() { return value; }
};

// 饿汉版实现 线程安全
class EagerLoadSingleton {
 private:
  int value;
  // 单例模式不允许clone
  EagerLoadSingleton(EagerLoadSingleton&) = delete;
  // 单例模式不允许赋值
  void operator=(const EagerLoadSingleton&) = delete;
  // constructor 私有
  EagerLoadSingleton(int value) { this->value = value; };

 public:
  // 没有对应的析构 内存会泄露
  static EagerLoadSingleton* singleton;
  ~EagerLoadSingleton() { cout << "123"; };
  static EagerLoadSingleton* getInstance() {
    // 线程安全
    return singleton;
  }
  int getValue() { return value; }
};

LazyLoadSingleton* LazyLoadSingleton::singleton = nullptr;
EagerLoadSingleton* EagerLoadSingleton::singleton = new EagerLoadSingleton(0);

int main() {
  // 线程不安全版
  for (int i = 0; i < 10; i++) {
    thread t([i]() {
      LazyLoadSingleton* s = LazyLoadSingleton::getInstance(i);
      cout << "LazyLoadSingleton: " << s->getValue() << endl;
    });
    t.detach();
  }

  // 线程安全版
  for (int j = 0; j < 10; j++) {
    thread t([]() {
      int a = EagerLoadSingleton::getInstance()->getValue();
      cout << "EagerLoadSingleton: " << a << endl;
    });
    t.detach();
  }
  pthread_exit(NULL);
}
