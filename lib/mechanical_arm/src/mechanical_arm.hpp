#ifndef mechanical_arm_hpp
#define mechanical_arm_hpp

#include <Arduino.h>
#include <pins_arduino.h>
#include <Servo.h>
#include "joystick.hpp"

class MechanicalArm {
private:
  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)
  int pos1 = 90, pos2 = 90, pos3 = 90, pos4 = 40;

  Servo baseplateServo;
  Servo rightSideServo;
  Servo leftSideServo;
  Servo clampClawServo;

  Joystick rightJoystick; // (A2, A5, 7);
  Joystick leftJoystick; // (A3, A4, 8);

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
  void lowerArm(const Joystick& joystick);
};

#endif