#include "mechanical_arm.hpp"

#define PRINT_DEBUG(msg) Serial.println(msg);
// #define PRINT_DEBUG(msg) ;

bool is_joystick_down(Joystick& joystick)
{
  return joystick.isDown();
}

bool is_joystick_up(Joystick& joystick)
{
  return joystick.isUp();
}

bool is_joystick_left(Joystick& joystick)
{
  return joystick.isLeft();
}

bool is_joystick_right(Joystick& joystick)
{
  return joystick.isRight();
}

ServoWithJoystick::ServoWithJoystick(bool (*is_down) (Joystick& joystick), bool (*is_up) (Joystick& joystick), MovmentDefinition movment_definition, Joystick& joystick, const uint8_t servo_pin) : is_down(is_down), is_up(is_up), movment_definition(movment_definition), joystick(joystick), servo_pin(servo_pin)
{
  servo_position = movment_definition.start_position;
}

void ServoWithJoystick::setup()
{
  servo.attach(servo_pin);

  servo.write(movment_definition.start_position);
  delay(20);
}

void ServoWithJoystick::run()
{
  if (is_up(joystick)) // if push the left joystick upward
  {
    PRINT_DEBUG("left.up");
    servo_position = servo_position - 1;
    servo.write(servo_position); // the lower arm will stretch out
    delay(5);
    if (servo_position < movment_definition.min_range) // limit the stretched angle
    {
      servo_position = movment_definition.min_range;
    }
  }
  else if (is_down(joystick)) // if push the right joystick downward
  {
    PRINT_DEBUG("left.down");
    servo_position = servo_position + 1;
    servo.write(servo_position); // the lower arm will draw back
    delay(5);
    if (servo_position > movment_definition.max_range) // limit the retraction angle
    {
      servo_position = movment_definition.max_range;
    }
  }
}

MechanicalArm::MechanicalArm() : rightJoystick(A2, A5, 7), leftJoystick(A3, A4, 8), baseplate(is_joystick_left, is_joystick_right, MovmentDefinition(2,180,90), rightJoystick, A1), clampClaw(is_joystick_left, is_joystick_right, MovmentDefinition(2,90,40), leftJoystick, 9), lowerArm(is_joystick_down, is_joystick_up, MovmentDefinition(35,90,45), leftJoystick, 6), upperArm(is_joystick_down, is_joystick_up, MovmentDefinition(40,160,90), rightJoystick, A0)
{
}

void MechanicalArm::setup()
{
  rightJoystick.setup();
  leftJoystick.setup();

  baseplate.setup();
  clampClaw.setup();
  lowerArm.setup();
  upperArm.setup();
}

void MechanicalArm::run()
{
  rightJoystick.read();
  leftJoystick.read();

  baseplate.run();
  clampClaw.run();
  lowerArm.run();
  upperArm.run();
}
