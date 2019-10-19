/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Sepideh                                          */
/*    Created:      Fri Oct 18 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FrontLeft            motor         1               
// FrontRight           motor         5               
// BackRight            motor         20              
// BackLeft             motor         11              
// LiftLeft             motor         15              
// LiftRight            motor         16              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"


using namespace vex;
int LeftSpeed= 0;
int RightSpeed = 0;


void controlWeels(){
  LeftSpeed = Controller1.Axis3.value() * 3;
  RightSpeed = Controller1.Axis2.value() * 3;


  FrontLeft.setVelocity(LeftSpeed, rpm);
  FrontLeft.spin(forward);
  FrontRight.setVelocity(RightSpeed, rpm);
  FrontRight.spin(forward);
  BackLeft.setVelocity(LeftSpeed, rpm);
  BackLeft.spin(forward);
  BackRight.setVelocity(RightSpeed, rpm);
  BackRight.spin(forward);
  


}

void controlLift(){

  //  Controller1.Axis1.position (degree) < 2100
  // FrontLeft.setVelocity(Controller1.Axis3.position()
    if (Controller1.ButtonL1.pressing()) {
    LiftLeft.spin(forward);
    LiftRight.spin(forward);
  } else if (Controller1.ButtonL2.pressing()) {
    LiftLeft.spin(reverse);
    LiftRight.spin(reverse);
  
  }else {
    LiftLeft.stop();
    LiftRight.stop();
  
  }

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit(); 

  LiftLeft.setVelocity(200,rpm);
  LiftRight.setVelocity(200,rpm);
  


  
   
  while (true) {
    controlLift();
    controlWeels();
    // Brain.Screen.clearLine(1, color::black);
    // Brain.Screen.setCursor(1, 0);
    // Brain.Screen.print(LeftSpeed);
  }  

}
