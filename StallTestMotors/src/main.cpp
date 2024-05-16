/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RM                   motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RM = motor(PORT6, ratio18_1, false);


void vexcodeInit( void ) {
  // nothing to initialize
}
// Custom functions

void voltDrive(double speed, int wt){
  speed=speed*120;
  RM.spin(forward,speed,voltageUnits::mV);
  wait(wt, msec);
}

void motorDisplay(int offset){
  float vM=0.0;
  float speed=0.0;
  float current=0.0;
  vM=RM.voltage(voltageUnits::mV);
  speed=RM.velocity(rpm);
  current=RM.current(amp);
  Brain.Screen.printAt(1,offset,"V %0.1f  mV,  %0.1f rpm,  %0.2f  Amps",vM,speed,current);
}

void runMotorTest(){
   Brain.Screen.printAt(1,20,"start 2");
  int offset=20;
  float speed=20;
 
  while (speed<=100) {
    
    offset=offset+20;
    voltDrive(speed, 0);
    wait(2000,msec);
    motorDisplay(offset);
    speed=speed+20;
  }
    voltDrive(0, 0);
  Brain.Screen.printAt(1,160,"done");
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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

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
  // User control code here, inside the loop
 Controller1.ButtonX.pressed(runMotorTest);
Brain.Screen.clearScreen();
RM.spin(fwd,100,pct);
wait(1000,msec);
RM.spin(fwd,0,pct);

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
