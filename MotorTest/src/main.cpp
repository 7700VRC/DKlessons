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

motor RM = motor(PORT1, ratio18_1, true);



// VEXcode generated functions

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
  Brain.Screen.setPenColor(white);
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
  
}

// Touch screen menu functions
void drawButtons(){
  // Button 1: Free Speed Test
  Brain.Screen.setFillColor(color::green);
  Brain.Screen.drawRectangle(20, 150, 220, 80);
  Brain.Screen.setPenColor(color::black);
  Brain.Screen.printAt(40, 170, "Free Speed Test");
  
  
  // Button 2: Stall Test
  Brain.Screen.setFillColor(color::red);
  Brain.Screen.drawRectangle(260, 150, 220, 80);
  Brain.Screen.setPenColor(color::white);
  Brain.Screen.printAt(290, 170, "Stall Test");
        Brain.Screen.printAt(290, 190, "Lock motor");
        Brain.Screen.printAt(290, 210, "before testing");

  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(color::white);
}

void showMainMenu(){
  Brain.Screen.clearScreen(color::blue);
  Brain.Screen.setFillColor(color::blue);
  Brain.Screen.setPenColor(color::white);
  Brain.Screen.setFont(mono40);
  
  // Title
 
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(50, 70, "Connect Motor in Port 1");
  Brain.Screen.printAt(50, 90, "Select Test Type");
  
  drawButtons();
}



void handleTouchSelection(){
  
    
  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();
      
      // Check if touch is in Free Speed Test button area
      if(x >= 20 && x <= 240 && y >= 110 && y <= 230){
        // Highlight selected button
        Brain.Screen.setFillColor(color::green);
        Brain.Screen.drawRectangle(20, 110, 220, 80);
        Brain.Screen.setPenColor(color::black);
        Brain.Screen.printAt(40, 155, "Free Speed Test");
       // Brain.Screen.printAt(40, 180, "Test");
        wait(200, msec);
        
        // Run the test
        runMotorTest();
      }
      // Check if touch is in Stall Test button area
      else if(x >= 260 && x <= 480 && y >= 110 && y <= 230){
        // Highlight selected button
        Brain.Screen.setFillColor(color::red);
        Brain.Screen.setPenColor(color::white);
        Brain.Screen.drawRectangle(260, 110, 220, 80);
        Brain.Screen.printAt(290, 155, "Stall Test");
        Brain.Screen.printAt(290, 180, "Lock motor before test");
        wait(200, msec);
        
        // Run the test
        stallMotorTest();
      }
  drawButtons();
  //showMainMenu();
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


Brain.Screen.pressed(handleTouchSelection);

Brain.Screen.clearScreen();

showMainMenu();

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

 Brain.Screen.printAt(290, 180, "Test User Control"); 
 
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
    wait(1010, msec);
  }
}
