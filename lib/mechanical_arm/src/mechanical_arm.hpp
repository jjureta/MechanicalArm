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

class ServoWithJoystick {
private:
  bool (*is_down) (Joystick& joystick);
  bool (*is_up) (Joystick& joystick);

  const MovmentDefinition movment_definition;
  Joystick& joystick;

  const uint8_t servo_pin;

  Servo servo;

  uint8_t servo_position;

public:
  ServoWithJoystick(bool (*is_down) (Joystick& joystick), bool (*is_up) (Joystick& joystick), MovmentDefinition movment_definition, Joystick& joystick, const uint8_t servo_pin);

  void setup();

  void run();
};

class MechanicalArm {
private:
  Joystick rightJoystick;
  Joystick leftJoystick;

  ServoWithJoystick baseplate;
  ServoWithJoystick clampClaw;
  ServoWithJoystick lowerArm;
  ServoWithJoystick upperArm;

public:
  MechanicalArm();

  void setup();

  void run();
};

#endif