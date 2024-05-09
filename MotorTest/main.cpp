/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      5/8/2024, 9:18:56 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here
brain  Brain;
controller Controller1 = controller(primary);
motor RM = motor(PORT2, ratio18_1, true);

// Custom functions

void voltDrive(double speed, int wt){
  speed=speed*120;
  RM.spin(fwd,speed,voltageUnits::mV);
  wait(wt, msec);
}

void motorDisplay(int offset){
  float vM=0.0;
  float speed=0.0;
  float current=0.0;
  vM=RM.voltage(voltageUnits::mV);
  speed=RM.velocity(rpm);
  current=RM.current(amp);
  Brain.Screen.printAt(1,offset,"mVolts %0.1f  Speed %0.1f rpm, Current  %0.2f  Amps");
}

void runMotorTest(){
  int offset=0;
  float speed=0;
  // User control code here, inside the loop
  while (1) {
    speed=speed+20;
    offset=offset+20;
    if (speed>100) break;
    voltDrive(speed, 0);
    wait(2000,msec);
    motorDisplay(offset);
  }
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
Brain.Screen.clearScreen();
Controller1.ButtonX.pressed(runMotorTest);
  // User control code here, inside the loop
  while (1) {
   wait(20,msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
