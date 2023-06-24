#ifndef MyClass_h
#define MyClass_h
#include <Arduino.h>

class MyClass {
  public:
    MyClass(int pin);
    void on();
    void off();
    void blink(int blinking);
  private:
    int _pin;
};

#endif
