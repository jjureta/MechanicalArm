#include "joystick.hpp"

Joystick::Joystick(uint8_t x, uint8_t y, uint8_t key)
    : _xPin(x), _yPin(y), _keyPin(key) {
  }

  void Joystick::setup() {
    pinMode(_keyPin, INPUT);
  }

  void Joystick::read() {
    xValue = analogRead(_xPin);       // read the right X value
    yValue = analogRead(_yPin);       //read the right Y value
    keyValue = digitalRead(_keyPin);  //read the right Z value
  }

  int Joystick::getX() const {
    return xValue;
  }

  int Joystick::getY() const {
    return yValue;
  }

  bool Joystick::isKeyDown() const {
    return keyValue == 0;
  }

  bool Joystick::isRight() const {
    return getX() < JOYSTICK_MIN;
  }

  bool Joystick::isLeft() const {
    return getX() > JOYSTICK_MAX;
  }

  bool Joystick::isUp() const {
    return getY() < JOYSTICK_MIN;
  }

  bool Joystick::isDown() const {
    return getY() > JOYSTICK_MAX;
  }