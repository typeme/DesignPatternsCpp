#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

/**
 * 线程安全版本的单例模式
 * 使用互斥锁实现
 */

class Singleton {
 private:
  int value;
  static Singleton* singleton;
  static std::mutex mutex_;

 private:
  Singleton(){};
  Singleton(int value) { this->value = value; };

 public:
  // 单例中 不允许使用克clone
  Singleton(Singleton&) = delete;
  // 单例中 不允许进行赋值
  Singleton& operator=(const Singleton&) = delete;
  // constructor 私有
 public:
  int getValue() { return value; };
  // 加锁版实现
  static Singleton* getInstance(int value) {
    // 线程安全
    if (singleton == nullptr) {
      std::lock_guard<std::mutex> lock(mutex_);  // 加锁
      if (singleton == nullptr) {
        singleton = new Singleton(value);
      }
    }
    return singleton;
  }
};

class StaticSingleton {
 private:
  int value;

 private:
  StaticSingleton(){};
  StaticSingleton(int value) { this->value = value; };

 public:
  // 单例中 不允许使用克clone
  StaticSingleton(StaticSingleton&) = delete;
  // 单例中 不允许进行赋值
  StaticSingleton& operator=(const StaticSingleton&) = delete;
  // constructor 私有
 public:
  int getValue() { return value; };
  // static 实现
  static StaticSingleton* getInstance(int value) {
    // 线程安全
    static StaticSingleton* singleton = new StaticSingleton(value);
    return singleton;
  }
};

Singleton* Singleton::singleton{nullptr};
std::mutex Singleton::mutex_;

int main() {
  for (int i = 0; i < 10; i++) {
    thread t([i]() {
      Singleton* s1 = Singleton::getInstance(i);
      cout << "mutex: " << s1->getValue() << endl;
    });
    t.detach();
  }

  for (int j = 0; j < 10; j++) {
    thread t([j]() {
      StaticSingleton* s2 = StaticSingleton::getInstance(j);
      cout << "static: " << s2->getValue() << endl;
    });
    t.detach();
  }
  pthread_exit(NULL);
  return 0;
}