#ifndef mechanical_arm_hpp
#define mechanical_arm_hpp

#include <Arduino.h>
#include <pins_arduino.h>
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
  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)
  int baseplatePosition = 90, upperArmPosition = 90, lowerArmPosition = 90, pos4 = 40;

  Joystick rightJoystick;
  Joystick leftJoystick;

  ServoWithJoystick leftArm;

  Servo baseplateServo;
  Servo rightSideServo;
  // Servo leftSideServo;
  Servo clampClawServo;

public:
  MechanicalArm();

  void setup();

  void run();

private:
  //claw
  void clampClaw(const Joystick& joystick);
  //******************************************************
  //turn
  void baseplate(const Joystick& joystick);

  //**********************************************************/
  // upper arm
  void upperArm(const Joystick& joystick);

  //*************************************************************/
  // lower arm
  // void lowerArm(const Joystick& joystick);
};

#endif