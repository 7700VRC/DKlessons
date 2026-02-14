/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      1/23/2026, 4:58:45 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <iostream> 
#include <vector>
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

controller Controller1;
brain Brain;

motor RF=motor(PORT20,ratio6_1,false);
motor RM=motor(PORT19,ratio6_1,false);
motor RB=motor(PORT18,ratio6_1,true);
motor LF=motor(PORT11,ratio6_1,true);
motor LM=motor(PORT12,ratio6_1,true);
motor LB=motor(PORT13,ratio6_1,false);
motor Conv=motor(PORT1,ratio6_1,false);
motor TR=motor(PORT10,ratio6_1,false);

inertial gyro=inertial(PORT8);
aivision AV_Camera = aivision(PORT4, aivision::ALL_AIOBJS);

std::vector<int> typeVector;
std::vector<float> xVector;
std::vector<float> yVector;
//const int mobileGoal = 1;
enum gameElements {
  blueBlock,
  redBlock,
};

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

float AV_Handler()
{
  // modified the function to only do actions related to the camera and return x y of the object
  typeVector.clear();
  xVector.clear();
  yVector.clear();
  float centerX;
  float centerY;

  AV_Camera.takeSnapshot(aivision::ALL_AIOBJS);
Brain.Screen.printAt(10, 20, "Objects Found: %d  ", AV_Camera.objectCount);
  for (int object = 0; object < AV_Camera.objectCount; ++object)
  {

    aivision::object currentObject = AV_Camera.objects[object];
Brain.Screen.printAt(10, 50, "Object ID: %d", currentObject.id);
    if (currentObject.id == redBlock)
    {

      typeVector.push_back(0);
      xVector.push_back(currentObject.centerX);
      yVector.push_back(currentObject.centerY);
      //Brain.Screen.printAt(10, 80, "Red Block Found at X: %f Y: %f", currentObject.centerX, currentObject.centerY);
      Brain.Screen.setFillColor(red);
      Brain.Screen.drawCircle(xVector[0], yVector[0], 5);
    }
      else if (currentObject.id == blueBlock)
      {
  
        typeVector.push_back(0);
        xVector.push_back(currentObject.centerX);
        yVector.push_back(currentObject.centerY);
       // Brain.Screen.printAt(10, 110, "Blue Block Found at X: %f Y: %f", currentObject.centerX, currentObject.centerY);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.drawCircle(xVector[0], yVector[0], 5);
      }
      Brain.Screen.setFillColor(transparent);
  }

  if (typeVector.size() != 0)
  {
    std::cout << "Type: " << typeVector[0] << " X: " << xVector[0] << " Y: " << yVector[0] << std::endl;
    centerX = xVector[0];
    centerY = yVector[0];
  }
  else
  {
    std::cout << "--------------No Objects Found------------ " << std::endl;
    centerX = 0;
    centerY = 0;
  }

  return centerX, centerY;
}

void driveToGoal(float targetX, float targetY)
{

  float errorX;
  float errorY;
  float accuracyX = 3.0;
  float accuracyY = 3.0;
  float Kpx = 1.0;
  float Kpy = 1.0;
  float speed;
  float turnSpeed;
  while (true)
  {
    float x, y = AV_Handler();
    if (x == 0.0 or y == 0.0)
      break;
    errorX = targetX - x;
    errorY = targetY - y;
    if (fabs(errorX) < accuracyX and fabs(errorY) < accuracyY)
      break;
    speed = Kpy * errorY;
    if (speed > 100)
      speed = 100;
    if (speed < -100)
      speed = -100;
    turnSpeed = Kpx * errorX;
    if (turnSpeed > 25)
      turnSpeed = 25;
    if (turnSpeed < -25)
      turnSpeed = -25;
    driveVolts(speed - turnSpeed, speed + turnSpeed, 10);
  }
  driveVolts(0, 0, 0);
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
  Brain.Screen.print("Autonomous Running");
  while(true){
    AV_Handler();
 // driveToGoal(150,120);
  wait(10,msec);
  }
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
autonomous();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
