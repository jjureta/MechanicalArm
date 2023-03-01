#include "mechanical_arm.hpp"

#define PRINT_DEBUG(msg) Serial.println(msg);
// #define PRINT_DEBUG(msg) ;

ServoWithJoystick::ServoWithJoystick(MovmentDefinition movment_definition, const uint8_t servo_pin, Joystick &joystick) : movment_definition(movment_definition), servo_pin(servo_pin), joystick(joystick)
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
  bool joystick_activated = is_joystick_up() || is_joystick_down();

  if (is_joystick_up()) // if push the left joystick upward
  {
    PRINT_DEBUG("joystick.up");
    servo_position = servo_position - movment_step;
  }
  else if (is_joystick_down()) // if push the right joystick downward
  {
    PRINT_DEBUG("joystick.down");
    servo_position = servo_position + movment_step;
  }

  if (joystick_activated)
  {
    servo.write(servo_position); // the lower arm will stretch out
    delay(5);

    if (servo_position < movment_definition.min_range) // limit the stretched angle
    {
      servo_position = movment_definition.min_range;
    }
    else if (servo_position > movment_definition.max_range) // limit the retraction angle
    {
      servo_position = movment_definition.max_range;
    }
  }
}

MechanicalArm::MechanicalArm() : rightJoystick(A2, A5, 7), leftJoystick(A3, A4, 8), baseplate(MovmentDefinition(2, 180, 90), A1, rightJoystick), clampClaw(MovmentDefinition(2, 90, 40), 9, leftJoystick), lowerArm(MovmentDefinition(35, 90, 45), 6, leftJoystick), upperArm(MovmentDefinition(40, 160, 90), A0, rightJoystick)
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
