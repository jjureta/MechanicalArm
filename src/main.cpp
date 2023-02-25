/***
 * See doc: https://wiki.keyestudio.com/Ks0198_keyestudio_4DOF_Robot_Mechanical_Arm_Kit_for_Arduino_DIY
 */

#include <Arduino.h>
#include <mechanical_arm.hpp>

#define PRINT_DEBUG(msg) Serial.println(msg);
// #define PRINT_DEBUG(msg) ;

MechanicalArm mechanicalArm;

int s1, s2, s3, s4;
int jiyi1[20];  //define 4 array, separately used to save the angle of four servo.
int jiyi2[20];  // （array length is 20，namely can save angle data of 0~20 servo）
int jiyi3[20];  //if need to save more data, just change the number 20 to be more larger number.
int jiyi4[20];
int i = 0;  // for loop
int j = 0;  //  save the last value of i

void print(int x, int y, int z) {
  Serial.print(x);
  Serial.print("\t");

  Serial.print(y);
  Serial.print("\t");

  Serial.print(z);
  Serial.print("\t");
}

void print(int x1, int y1, int z1, int x2, int y2, int z2) {
  print(x1, y1, z1);
  print(x2, y2, z2);

  Serial.println();
}

void setup() {
  mechanicalArm.setup();
  Serial.begin(9600);  // set the baud rate to 9600
}

void loop() {
  PRINT_DEBUG("*** test test ***")
  mechanicalArm.run();
  delay(5);
  // print(x1, y1, z1, x2, y2, z2);

  //delay(5)  ;// delay, used to reduce the joystick value read, that is reduce the whole speed.
  /*if(z1==1)   // if the joystick right key is pressed
  {
    delay(10);  // delay for eliminating shake 
    if(z1==1)   // judge again if the right key is pressed
    {
      s1=baseplateServo.read();  // read the angle value of servo 1 and assign it to s1
      delay(100);
      Serial.println(s1); // print out the angle value of servo 1 on the serial monitor
      s2=rightSideServo.read();  //  read the angle value of servo 2 and assign it to s2
      delay(100);
      Serial.println(s2);
      s3=leftSideServo.read();   //  read the angle value of servo 3 and assign it to s3
      delay(100);
      Serial.println(s3);
    
      clampClowServo.read();   // read the angle value of servo 4 and assign it to s4 
      delay(100);
      Serial.println(s4);
       
      jiyi1[i]=s1;  // Save the read servo value to the array sequentially
      jiyi2[i]=s2;
      jiyi3[i]=s3;
      jiyi4[i]=s4;
      i++;   //i plus 1
      j=i;   // assign the last value of i to j
      delay(100);  // delay 100ms
      Serial.println(i);  // print out the value i
    }
  }
  if(z2==1) //  if the left joystick key is pressed
  {
    delay(10);  // delay for eliminating shake 
    if(z2==1)   //judge again if the left key is pressed 
    {
      pos1 = baseplateServo.read();  // memorize the angle value of 4 servo posture
      pos2 = rightSideServo.read();
      pos3 = leftSideServo.read();
      pos4 = clampClowServo.read();
      
      while(z2==1)  // loop, make the arm repeat the action.
      {
        for(int k=1;k<j;k++)  //for loop, perform all the stored actions.
        {
          if(pos1<jiyi1[k])   // if the current servo 1 angle is less than the value stored in array 1.
          {
            while(pos1<jiyi1[k])  //while loop, make servo turn to the position of value stored in the array.
            {
              baseplateServo.write(pos1);  //servo 1 performs the action 
              delay(5);   //delay 5ms，controlling the servo rotating speed.
              pos1++;   //pos1 plus 1
              //Serial.println(pos1);
            }
          }
          else   //if the current servo 1 angle is greater than the value stored in array 1.
          {
           while(pos1>jiyi1[k])    //while loop, make servo turn to the position of value stored in the array.
            {
              baseplateServo.write(pos1);  //servo 1 performs the action
              delay(5);   //delay 5ms，controlling the servo rotating speed.
              pos1--;   //pos1 subtracts 1
              //Serial.println(pos1);
            }
          }*/
  //***************************************************************
  //the explanation is the same as the previous servo.
  /*if(pos2<jiyi2[k])
          {
            while(pos2<jiyi2[k])
            {
              rightSideServo.write(pos2);
              delay(5);
              pos2++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos2>jiyi2[k])
            {
              rightSideServo.write(pos2);
              delay(5);
              pos2--;
              //Serial.println(pos1);
            }
          }*/
  //*********************************************
  //the explanation is the same as the previous servo.
  /*if(pos3<jiyi3[k])
          {
            while(pos3<jiyi3[k])
            {
              leftSideServo.write(pos3);
              delay(5);
              pos3++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos3>jiyi3[k])
            {
              leftSideServo.write(pos3);
              delay(5);
              pos3--;
              //Serial.println(pos1);
            }
          }*/
  //*********************************************
  //the explanation is the same as the previous servo.
  /*if(pos4<jiyi4[k])
          {
            while(pos4<jiyi4[k])
            {
          
          clampClowServo.write(pos4);
              delay(5);
              pos4++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos4>jiyi4[k])
            {
          
          clampClowServo.write(pos4);
              delay(5);
              pos4--;
              //Serial.println(pos1);
            }
          }
        }*/
  //************************************************************
  // for exiting the loop
  /*z1 = digitalRead(right_key);  // read the right Z value
            if(z1==1)  // if the right key is pressed
            {
              delay(10);  //eliminate the shake
              if(z1==1)  // if the key z1 is pressed
              {
                pos1=jiyi1[(j-1)];  // assign the last angle value saved in array to pos
                pos2=jiyi2[(j-1)];  // for exiting the loop, still access to joystick control.
                pos3=jiyi3[(j-1)];  
                pos4=jiyi4[(j-1)];
                i=0;  // assign i as 0，prepare for saving the angle value using array
                z2=0; // assign z2 as 0，for exiting the while loop
                break;  //exit the current loop
              }
            }*/
  //********************************************************
  /*      }
    }
  }
 */
}
