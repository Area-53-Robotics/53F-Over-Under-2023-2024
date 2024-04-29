/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Administrator                                    */
/*    Created:      Mon Apr 15 2024                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void spinfor(vex::motor& motor, vex::directionType dir, int speed, int duration) {
    if (dir == vex::directionType::fwd) {
        motor.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    } else if (dir == vex::directionType::rev) {
        motor.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
    }
    vex::task::sleep(duration);
    motor.stop();
}

void spinfor(vex::motor_group& motors, vex::directionType dir, int speed, int duration) {
    if (dir == vex::directionType::fwd) {
        motors.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
    } else if (dir == vex::directionType::rev) {
        motors.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
    }
    vex::task::sleep(duration);
    motors.stop();
}

void usercontrol(void) {
  motor_group leftMotors = motor_group(Left1, Left2, Left3, PTO_Left);
  motor_group rightMotors = motor_group(Right1, Right2, Right3, PTO_Right);
  bool reverseDT = false;
      
    while (true) {
      if (Controller1.ButtonA.pressing()) {
        reverseDT = !reverseDT;
          while (Controller1.ButtonA.pressing()) {
            task::sleep(10);
          }
      }

      if (reverseDT == false) {
        leftMotors.spin(directionType::fwd, Controller1.Axis3.position(), velocityUnits::pct);
        rightMotors.spin(directionType::fwd, Controller1.Axis2.position(), velocityUnits::pct);
      }else if (reverseDT == true) {
        leftMotors.spin(directionType::rev, Controller1.Axis3.position(), velocityUnits::pct);
        rightMotors.spin(directionType::rev, Controller1.Axis2.position(), velocityUnits::pct);
      }
      
      if (Controller1.ButtonR1.pressing()) {
        Intake.spin(reverse, 100, pct);
      }else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(forward, 100, pct);
      }else {
        Intake.stop();
      }

      if (Controller1.ButtonB.pressing()) {
        IntakeElevation = !IntakeElevation;
          while (Controller1.ButtonB.pressing()) {
            task::sleep(10);
        }
      }

      if (Controller1.ButtonLeft.pressing()) {
        Elevation = !Elevation;
          while (Controller1.ButtonLeft.pressing()) {
            task::sleep(10);
        }
      }

    task::sleep(10);
  } 
}

void autonomous(void) {
  motor_group leftMotors = motor_group(Left1, Left2, Left3);
  motor_group rightMotors = motor_group(Right1, Right2, Right3);
  motor_group wholeDrivetrain = motor_group(Left1, Left2, Left3, Right1, Right2, Right3);

  spinfor(wholeDrivetrain, forward, 100, 250);
  leftMotors.spin(forward, 80, pct);
  rightMotors.spin(reverse, 80, pct);
  task::sleep(300);
  wholeDrivetrain.stop();
  task::sleep(100);
  spinfor(wholeDrivetrain, forward, 100, 450);
  task::sleep(100);
  leftMotors.spin(reverse, 75, pct);
  rightMotors.spin(forward, 75, pct);
  task::sleep(250);
  wholeDrivetrain.stop();
  spinfor(wholeDrivetrain, forward, 100, 100);
  spinfor(Intake, forward, 100, 400);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  competition usercontrol;
  competition autonomous;
}
