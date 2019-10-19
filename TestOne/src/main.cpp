/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\msara                                            */
/*    Created:      Sat Oct 12 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// grabberML            motor         1
// grabberMR            motor         2
// ElevM                motor         3
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int motorSpeed = 100;
int elevSpeed = 100;

int SpeedController() {
  Brain.Screen.clearLine(2, color::black);
  Brain.Screen.setCursor(2, 0);
  Brain.Screen.print("Starting the Task");
  while (true) {
    if (Controller1.ButtonX.pressing()) {
      motorSpeed += 10;
      elevSpeed += 10;
      Brain.Screen.clearLine(2, color::black);
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Speed Set to %d", motorSpeed);
    }
    if (Controller1.ButtonB.pressing()) {
      motorSpeed -= 10;
      elevSpeed -= 10;
      Brain.Screen.clearLine(2, color::black);
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Speed Set to %d", motorSpeed);
    }
    if (Controller1.ButtonY.pressing() || Controller1.ButtonA.pressing()) {
      motorSpeed = 100;
      elevSpeed = 100;
      Brain.Screen.clearLine(2, color::black);
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Speed Set to %d", motorSpeed);
    }
    vex::task::sleep(50);
    grabberML.setVelocity(motorSpeed, rpm);
    grabberMR.setVelocity(motorSpeed, rpm);
    ElevM.setVelocity(elevSpeed, rpm);
  }
  return 0;
}

void grabberController() {
  if (Controller1.ButtonUp.pressing()) {
    grabberML.spin(forward);
    grabberMR.spin(forward);
  } else if (Controller1.ButtonDown.pressing()) {
    grabberML.spin(reverse);
    grabberMR.spin(reverse);
  } else {
    grabberML.stop();
    grabberMR.stop();
  }
}

void elevatorController() {
  if (Controller1.ButtonRight.pressing()) {
    if (ElevM.position(degrees) < 2100) {
      motorSpeed = 10;
      elevSpeed = 100;
      grabberML.spin(forward);
      grabberMR.spin(forward);
      ElevM.spinToPosition(1100, degrees);
      vex::task::sleep(10);
      grabberML.stop();
      grabberMR.stop();
      motorSpeed = -10;
      vex::task::sleep(100);
      grabberML.spin(forward);
      grabberMR.spin(forward);
      ElevM.spinToPosition(2250, degrees);
      vex::task::sleep(500);
      grabberML.stop();
      grabberMR.stop();
      ElevM.spinToPosition(0, degrees);
    }
  } else if (Controller1.ButtonLeft.pressing()) {
    if (ElevM.position(degrees) > 50) {
      ElevM.spinToPosition(0, degrees);
    }
  } else {
    ElevM.stop();
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.clearLine(1, color::black);
  Brain.Screen.setCursor(1, 0);
  Brain.Screen.print("Prigram Starteed");
  ElevM.setPosition(0, degrees);
  vex::task newtask(SpeedController);

  while (true) {
    grabberController();
    elevatorController();

    if (Controller1.ButtonL1.pressing()) {
      Brain.Screen.clearLine(1, color::black);
      Brain.Screen.setCursor(1, 0);
      Brain.Screen.print("Motor ElevM location : %f ", ElevM.position(degrees));
    }
  }
}
