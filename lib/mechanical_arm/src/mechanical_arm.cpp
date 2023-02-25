#include "mechanical_arm.hpp"

// #define PRINT_DEBUG(msg) Serial.println(msg);
#define PRINT_DEBUG(msg) ;

MechanicalArm::MechanicalArm() : rightJoystick(A2, A5, 7), leftJoystick(A3, A4, 8) {

}

void MechanicalArm::setup() {
    baseplateServo.attach(A1);  // set the control pin of servo 1 to A1
    rightSideServo.attach(A0);  // set the control pin of servo 2 to A0
    leftSideServo.attach(6);    //set the control pin of servo 3 to D6
    clampClawServo.attach(9);   // set the control pin of servo 4 to D9

    // boot posture
    baseplateServo.write(pos1);  //turn servo 1 to 90 degrees
    delay(500);

    rightSideServo.write(pos2);  // turn servo 2 to 90 degrees
    delay(500);

    leftSideServo.write(pos3);  // turn servo 3 to 120 degrees
    delay(500);

    clampClawServo.write(pos4);  // turn servo 4 to 35 degrees
    delay(500);

    rightJoystick.setup();
    leftJoystick.setup();
  }

  void MechanicalArm::run() {
    rightJoystick.read();
    leftJoystick.read();

    //claw
    clampClaw(leftJoystick);
    //turn
    baseplate(rightJoystick);
    //upper arm
    upperArm(rightJoystick);
    //lower arm
    lowerArm(leftJoystick);
  }

  //claw
  void MechanicalArm::clampClaw(const Joystick& joystick) {
    //claw
    if (joystick.isLeft())  // if push the left joystick to the right
    {
      PRINT_DEBUG("left.left");
      pos4 = pos4 - 2;  // angle of servo 4, subtract 2 (change the value you subtract, thus change the closed speed of claw)
      //Serial.println(pos4);

      clampClawServo.write(pos4);  //  servo 4 operates the motion and claw is gradually closed.
      delay(5);
      if (pos4 < 2)  // if pos4 value subtracts to 2, the claw in 37 degrees we have tested is closed.）
      {              //（should change the value based on the fact）
        pos4 = 2;    //stop subtraction when reduce to 2
      }
    } else if (joystick.isRight())  ////if push the left joystick to the left
    {
      PRINT_DEBUG("left.right");
      pos4 = pos4 + 8;  //current angle of servo 4 plus 8（change the value you plus, thus change the open speed of claw）
      //Serial.println(pos4);

      clampClawServo.write(pos4);  // servo 4 operates the action, claw gradually opens.
      delay(5);
      if (pos4 > 90)  //limit the largest angle opened
      {
        pos4 = 90;
      }
    }
  }
  //******************************************************
  //turn
  void MechanicalArm::baseplate(const Joystick& joystick) {
    // Serial.println(pos1);
    if (joystick.isRight())  //if push the right joystick to the right
    {
      PRINT_DEBUG("right.right");
      pos1 = pos1 - 1;             //pos1 subtracts 1
      baseplateServo.write(pos1);  // servo 1 performs the action, the robot arm turns right.
      delay(5);
      if (pos1 < 1)  // limit the right turning angle
      {
        pos1 = 1;
      }
    } else if (joystick.isLeft())  // if push the right joystick to the left
    {
      PRINT_DEBUG("right.left");
      pos1 = pos1 + 1;             //pos1 plus 1
      baseplateServo.write(pos1);  //the robot arm turns left.
      delay(5);
      if (pos1 > 180)  //limit the left turning angle
      {
        pos1 = 180;
      }
    }
  }

  //**********************************************************/
  // upper arm
  void MechanicalArm::upperArm(const Joystick& joystick) {
    if (joystick.isUp())  // if push the right joystick upward
    {
      PRINT_DEBUG("right.up");
      pos2 = pos2 - 1;
      rightSideServo.write(pos2);  // the robot arm will lift
      delay(5);
      if (pos2 < 0)  // limit the lifting angle
      {
        pos2 = 0;
      }
    } else if (joystick.isDown())  // if push the right joystick downward
    {
      PRINT_DEBUG("right.down");
      pos2 = pos2 + 1;
      rightSideServo.write(pos2);  // the robot arm will go down
      delay(5);
      if (pos2 > 180)  // limit the declining angle
      {
        pos2 = 180;
      }
    }
  }

  //*************************************************************/
  // lower arm
  void MechanicalArm::lowerArm(const Joystick& joystick) {
    if (joystick.isUp())  // if push the left joystick upward
    {
      PRINT_DEBUG("left.up");
      pos3 = pos3 - 1;
      leftSideServo.write(pos3);  // the lower arm will stretch out
      delay(5);
      if (pos3 < 35)  // limit the stretched angle
      {
        pos3 = 35;
      }
    } else if (joystick.isDown())  // if push the right joystick downward
    {
      PRINT_DEBUG("left.down");
      pos3 = pos3 + 1;
      leftSideServo.write(pos3);  // the lower arm will draw back
      delay(5);
      if (pos3 > 180)  // limit the retraction angle
      {
        pos3 = 180;
      }
    }
  }