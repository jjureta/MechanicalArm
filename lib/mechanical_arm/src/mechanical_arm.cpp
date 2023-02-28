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
  return joystick.isDown();
}

bool is_joystick_right(Joystick& joystick)
{
  return joystick.isUp();
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

MechanicalArm::MechanicalArm() : rightJoystick(A2, A5, 7), leftJoystick(A3, A4, 8), leftArm(is_joystick_down, is_joystick_up, MovmentDefinition(35,90,45), leftJoystick, 6)
{
}

void MechanicalArm::setup()
{
  rightJoystick.setup();
  leftJoystick.setup();

  baseplateServo.attach(A1); // set the control pin of servo 1 to A1
  rightSideServo.attach(A0); // set the control pin of servo 2 to A0
  // leftSideServo.attach(6);   // set the control pin of servo 3 to D6
  clampClawServo.attach(9);  // set the control pin of servo 4 to D9

  // boot posture
  baseplateServo.write(baseplatePosition); // turn servo 1 to 90 degrees
  delay(500);

  rightSideServo.write(upperArmPosition); // turn servo 2 to 90 degrees
  delay(500);

  // leftSideServo.write(lowerArmPosition); // turn servo 3 to 120 degrees
  // delay(500);

  clampClawServo.write(pos4); // turn servo 4 to 35 degrees
  delay(500);

  leftArm.setup();
}

void MechanicalArm::run()
{
  rightJoystick.read();
  leftJoystick.read();

  // claw
  clampClaw(leftJoystick);
  // turn
  baseplate(rightJoystick);
  // upper arm
  upperArm(rightJoystick);
  // lower arm
  // lowerArm(leftJoystick);

  leftArm.run();
}

// claw
void MechanicalArm::clampClaw(const Joystick &joystick)
{
  // claw
  if (joystick.isLeft()) // if push the left joystick to the right
  {
    PRINT_DEBUG("left.left");
    pos4 = pos4 - 2; // angle of servo 4, subtract 2 (change the value you subtract, thus change the closed speed of claw)
    // Serial.println(pos4);

    clampClawServo.write(pos4); //  servo 4 operates the motion and claw is gradually closed.
    delay(5);
    if (pos4 < 2) // if pos4 value subtracts to 2, the claw in 37 degrees we have tested is closed.）
    {             // （should change the value based on the fact）
      pos4 = 2;   // stop subtraction when reduce to 2
    }
  }
  else if (joystick.isRight()) ////if push the left joystick to the left
  {
    PRINT_DEBUG("left.right");
    pos4 = pos4 + 8; // current angle of servo 4 plus 8（change the value you plus, thus change the open speed of claw）
    // Serial.println(pos4);

    clampClawServo.write(pos4); // servo 4 operates the action, claw gradually opens.
    delay(5);
    if (pos4 > 90) // limit the largest angle opened
    {
      pos4 = 90;
    }
  }
}
//******************************************************
// turn
void MechanicalArm::baseplate(const Joystick &joystick)
{
  // Serial.println(pos1);
  if (joystick.isRight()) // if push the right joystick to the right
  {
    PRINT_DEBUG("right.right");
    baseplatePosition = baseplatePosition - 1; // pos1 subtracts 1
    baseplateServo.write(baseplatePosition);   // servo 1 performs the action, the robot arm turns right.
    delay(5);
    if (baseplatePosition < 1) // limit the right turning angle
    {
      baseplatePosition = 1;
    }
  }
  else if (joystick.isLeft()) // if push the right joystick to the left
  {
    PRINT_DEBUG("right.left");
    baseplatePosition = baseplatePosition + 1; // pos1 plus 1
    baseplateServo.write(baseplatePosition);   // the robot arm turns left.
    delay(5);
    if (baseplatePosition > 180) // limit the left turning angle
    {
      baseplatePosition = 180;
    }
  }
}

//**********************************************************/
// upper arm
void MechanicalArm::upperArm(const Joystick &joystick)
{
  if (joystick.isUp()) // if push the right joystick upward
  {
    PRINT_DEBUG("right.up");
    upperArmPosition = upperArmPosition + 1;
    rightSideServo.write(upperArmPosition); // the robot arm will lift
    delay(5);
    if (upperArmPosition < 0) // limit the lifting angle
    {
      upperArmPosition = 0;
    }
  }
  else if (joystick.isDown()) // if push the right joystick downward
  {
    PRINT_DEBUG("right.down");
    upperArmPosition = upperArmPosition - 1;
    rightSideServo.write(upperArmPosition); // the robot arm will go down
    delay(5);
    if (upperArmPosition > 180) // limit the declining angle
    {
      upperArmPosition = 180;
    }
  }
}

//*************************************************************/
// lower 
/*
void MechanicalArm::lowerArm(const Joystick &joystick)
{
  if (joystick.isUp()) // if push the left joystick upward
  {
    PRINT_DEBUG("left.up");
    lowerArmPosition = lowerArmPosition - 1;
    leftSideServo.write(lowerArmPosition); // the lower arm will stretch out
    delay(5);
    if (lowerArmPosition < 35) // limit the stretched angle
    {
      lowerArmPosition = 35;
    }
  }
  else if (joystick.isDown()) // if push the right joystick downward
  {
    PRINT_DEBUG("left.down");
    lowerArmPosition = lowerArmPosition + 1;
    leftSideServo.write(lowerArmPosition); // the lower arm will draw back
    delay(5);
    if (lowerArmPosition > 180) // limit the retraction angle
    {
      lowerArmPosition = 180;
    }
  }
}
*/
