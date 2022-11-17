#ifndef ledClass_h
#define ledClass_h

class ledClass {
public:

  ledClass(int pin);
  void ledFunction(int blinkRate);
  void onFunction();
  void offFunction();
private:

  int _pin;
};
#endif
