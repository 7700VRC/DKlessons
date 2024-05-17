/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      5/8/2024, 9:18:56 PM                                      */
/*    Description:  V5 Motor testing code                                     */
/*   two options, free speed testing and stall testing                        */
/*   for stall testing motor should be locked with titanium lock bar          */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here
brain  Brain;
controller Controller1 = controller(primary);
motor RM = motor(PORT6, ratio18_1, true);



// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
// Custom functions

void voltDrive(double speed, int wt){
  speed=speed*120;
  RM.spin(fwd,speed,voltageUnits::mV);
  wait(wt, msec);
}

void motorDisplay(int offset, double setSpeed){
  float vM=0.0;
  float speed=0.0;
  float current=0.0;setSpeed=setSpeed*120/1000;
  vM=RM.voltage(voltageUnits::volt);
  speed=RM.velocity(rpm);
  current=RM.current(amp);
  Brain.Screen.printAt(1,offset," %0.1f V set, %0.1f V, %0.1f rpm,  %0.2f  Amps",setSpeed ,vM, speed, current);
}

void tempDisplay(int offset){
  int temp=RM.temperature();
  if (temp>=60) Brain.Screen.setFillColor(red);
  else if (temp>=50) Brain.Screen.setFillColor(yellow);
  else Brain.Screen.setFillColor(green);
Brain.Screen.drawRectangle(1,offset-20,25,25);
  Brain.Screen.setFillColor(transparent);
Brain.Screen.printAt(30,offset,"  %d degrees C ", temp);

}

void runMotorTest(){
  int offset=0;
  float speed=0;
  Brain.Screen.clearScreen();
  // User control code here, inside the loop
  while (speed<100) {
    speed=speed+20;
    offset=offset+20;
    voltDrive(speed, 0);
    wait(3000,msec);
    motorDisplay(offset,speed);
  }
  voltDrive(0,0);
   tempDisplay(offset+25);
  Brain.Screen.printAt(1,180,"Done  push X on the remote to run Test");
  Brain.Screen.printAt(1,220,"Done  push Y on the remote to run stall Test");
}

void stallMotorTest(){
  int offset=0;
  float speed=0;
  Brain.Screen.clearScreen();
  // User control code here, inside the loop
  while (speed<100) {
    speed=speed+20;
    offset=offset+20;
    voltDrive(speed, 0);
    wait(500,msec);
    motorDisplay(offset,speed);
  }
  voltDrive(0,0);
  tempDisplay(offset+25);
  Brain.Screen.printAt(1,180,"Done  push X on the remote to run Test");
  Brain.Screen.printAt(1,220,"Done  push Y on the remote to run stall Test");
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
vexcodeInit( );
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
Controller1.ButtonY.pressed(stallMotorTest);
Brain.Screen.printAt(1,20,"Ready push X on the remote to start Test");
Brain.Screen.printAt(1,60,"  push Y on the remote to run stall Test");
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
