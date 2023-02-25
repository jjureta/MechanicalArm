#ifndef joystick_hpp
#define joystick_hpp

#include <Arduino.h>

class Joystick {
private:
  const uint8_t _xPin, _yPin, _keyPin;
  int xValue, yValue, keyValue;

  static const int JOYSTICK_MIN = 50, JOYSTICK_MAX = 500;

public:
  Joystick(uint8_t x, uint8_t y, uint8_t key);
  void setup();

  void read();

  int getX() const;

  int getY() const;

  bool isKeyDown() const;

  bool isRight() const;

  bool isLeft() const;

  bool isUp() const;

  bool isDown() const;
};

#endif