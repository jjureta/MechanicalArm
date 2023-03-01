#ifndef mechanical_arm_hpp
#define mechanical_arm_hpp

#include <Arduino.h>
#include <Servo.h>
#include "joystick.hpp"

struct MovmentDefinition
{
  const uint8_t min_range;
  const uint8_t max_range;
  const uint8_t start_position;

  MovmentDefinition(const uint8_t min_range, const uint8_t max_range, const uint8_t start_position) : min_range(min_range), max_range(max_range), start_position(start_position)
  {
  }
};

class ServoWithJoystick
{
private:
  const MovmentDefinition movment_definition;

  const uint8_t servo_pin;

  Servo servo;

  uint8_t servo_position;

  static const uint8_t movment_step = 2;

protected:
  Joystick &joystick;

public:
  ServoWithJoystick(MovmentDefinition movment_definition, const uint8_t servo_pin, Joystick &joystick);

  void setup();

  void run();

private:
  virtual bool is_joystick_down() = 0;

  virtual bool is_joystick_up() = 0;
};

class ServoWithJoystickDownUp : public ServoWithJoystick
{
public:
  using ServoWithJoystick::ServoWithJoystick;

private:
  virtual bool is_joystick_down()
  {
    return joystick.isDown();
  }

  virtual bool is_joystick_up()
  {
    return joystick.isUp();
  }
};

class ServoWithJoystickLeftRight : public ServoWithJoystick
{
public:
  using ServoWithJoystick::ServoWithJoystick;

private:
  virtual bool is_joystick_down()
  {
    return joystick.isLeft();
  }

  virtual bool is_joystick_up()
  {
    return joystick.isRight();
  }
};

class MechanicalArm
{
private:
  Joystick rightJoystick;
  Joystick leftJoystick;

  ServoWithJoystickLeftRight baseplate;
  ServoWithJoystickLeftRight clampClaw;
  ServoWithJoystickDownUp lowerArm;
  ServoWithJoystickDownUp upperArm;

public:
  MechanicalArm();

  void setup();

  void run();
};

#endif