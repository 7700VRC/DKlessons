/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      1/23/2026, 4:58:45 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

controller Controller1;

motor RF=motor(PORT20,ratio6_1,false);
motor RM=motor(PORT19,ratio6_1,false);
motor RB=motor(PORT18,ratio6_1,true);
motor LF=motor(PORT11,ratio6_1,true);
motor LM=motor(PORT12,ratio6_1,true);
motor LB=motor(PORT13,ratio6_1,false);
motor Conv=motor(PORT1,ratio6_1,false);
motor TR=motor(PORT10,ratio6_1,false);

inertial gyro=inertial(PORT8);

// custom functions

void driveVolts(int lspeed, int rspeed, int wt){
  lspeed=lspeed*120;
 rspeed=rspeed*120;
  LF.spin(fwd,lspeed,voltageUnits::mV);
  LM.spin(fwd,lspeed,voltageUnits::mV);
  LB.spin(fwd,lspeed,voltageUnits::mV);
  RF.spin(fwd,rspeed,voltageUnits::mV);
  RM.spin(fwd,rspeed,voltageUnits::mV);
  RB.spin(fwd,rspeed,voltageUnits::mV);
  wait(wt,msec);
}

void driveBrake(){
LF.stop(brake);  
LM.stop(brake);
LB.stop(brake);
RF.stop(brake);
RM.stop(brake);
RB.stop(brake);  

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
  // User control code here, inside the loop
  while (true) {

    int ls=Controller1.Axis3.position(pct);
    int rs=Controller1.Axis2.position(pct);

    driveVolts(ls,rs,10);
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
