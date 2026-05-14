/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      2/3/2026, 5:25:26 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;

controller Controller1;

motor RF = motor(PORT11, ratio18_1, true);

motor LF = motor(PORT19, ratio18_1, false);

inertial Gyro = inertial(PORT10);

// Global variables
float D = 3.25;       // wheel diameter in inches
float MotorGear = 36; // number of teeth on the gear driven by the motor
float WheelGear = 60; // number of teeth on the gear that drives the wheel
float G = MotorGear / WheelGear;
float PI = 3.14;
int WaitTime = 10; // sets frame rate for processing number is msec so 10 = 100fps, 20 = 50fps

// custom functions

void drive(int lspeed, int rspeed, int wt = WaitTime)
{
  LF.spin(fwd, lspeed, percent);
  RF.spin(fwd, rspeed, percent);
  wait(wt, msec);
}

void driveVolts(int lspeed, int rspeed, int wt = WaitTime)
{
  lspeed = lspeed * 120;
  rspeed = rspeed * 120;

  LF.spin(fwd, lspeed, voltageUnits::mV);
  RF.spin(fwd, rspeed, voltageUnits::mV);

  wait(wt, msec);
}

void driveBrake(){
  LF.stop(brake);  //set up for 2 motor drive
  RF.stop(brake);
}

void driveCoast(){
  LF.stop(coast);  //set up for 2 motor drive
  RF.stop(coast);
}

// Health of the robot functions
int YOFFSET = 20;
int NewLineY = 20;
int LineNumber = 0;
void MotorDisplay(int y, double curr, double temp)
{
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.printAt(5, YOFFSET + LineNumber * NewLineY, "Current: %.1fA", curr);
  if (curr < 1)
    Brain.Screen.setFillColor(green);
  else if (curr >= 1 && curr <= 2.5)
    Brain.Screen.setFillColor(yellow);
  else
    Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(140, YOFFSET + LineNumber * NewLineY - 15, 15, 15);

  Brain.Screen.setFillColor(transparent);
  Brain.Screen.printAt(160, YOFFSET + LineNumber * NewLineY, "Temp: %.1fC", temp);
  if (temp < 45)
    Brain.Screen.setFillColor(green);
  else if (temp <= 50 && temp >= 45)
    // TRUE and TRUE --> True
    // TRUE and FALSE --> False
    // FALSE and FALSE --> False
    Brain.Screen.setFillColor(yellow);
  else
    Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(275, YOFFSET + LineNumber * NewLineY - 15, 15, 15);
  Brain.Screen.setFillColor(transparent);
}

// Displays information on the brain
void Display()
{
  double leftFrontCurr = LF.current(amp);
  double leftFrontTemp = LF.temperature(celsius);

  double rightFrontCurr = RF.current(amp);
  double rightFrontTemp = RF.temperature(celsius);

  LineNumber++;
  if (LF.installed())
  {
    MotorDisplay(0, leftFrontCurr, leftFrontTemp);
    Brain.Screen.printAt(300, YOFFSET + LineNumber * NewLineY, "LeftFront");
  }
  else
  {
    Brain.Screen.setPenColor(red);
    Brain.Screen.printAt(5, YOFFSET + LineNumber * NewLineY, "LeftFront Problem");
    Brain.Screen.setPenColor(white);
  }
  LineNumber++;
  if (RF.installed())
  {
    MotorDisplay(60, rightFrontCurr, rightFrontTemp);
    Brain.Screen.printAt(300, YOFFSET + LineNumber * NewLineY, "RightFront");
  }
  else
  {
    Brain.Screen.setPenColor(red);
    Brain.Screen.printAt(5, YOFFSET + LineNumber * NewLineY, "RightFront Problem");
    Brain.Screen.setPenColor(white);
  }
  LineNumber = 0;
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

void pre_auton(void)
{
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

void autonomous(void)
{
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

void usercontrol(void)
{
  // User control code here, inside the loop
  int count = 0;
  while (true)
  {

    int ls = Controller1.Axis3.position(pct);
    int rs = Controller1.Axis2.position(pct);

    drive(ls, rs, 10);
    count++ ;
    if (count == 100)
    {
      Display();
      count = 0;
    }
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
