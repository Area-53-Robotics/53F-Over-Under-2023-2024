#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include <string>
#include <sys/unistd.h>
#include <unistd.h>

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(7, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);
}

//------------------------------------------------------//

void opcontrol() {
//Variables
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  
  pros::Motor_Group LDriveTrain ({-19, -20, -6});
  pros::Motor_Group RDriveTrain ({8, 9, 10});
  bool toggleDrive = false;
  
  int toggleIntake = 0;
  int toggleOuttake = 0;
  pros::Motor InTake(2);

  pros::Motor FWheel(7);
  FWheel.move(0);
  bool FWheel_toggle = false;

  pros::ADIDigitalOut leftWing('A');
  pros::ADIDigitalOut rightWing('H');
  bool leftWing_State = false;
  bool rightWing_State = false;

while (true) {
//Drive toggle switch
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      toggleDrive = !toggleDrive;
    }

//Drive
   if (toggleDrive == false) {
      RDriveTrain.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
      LDriveTrain.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
   }else if (toggleDrive == true) {
      RDriveTrain.move(-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
      LDriveTrain.move(-master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
   }

//Intake (controller button funtion)
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      toggleOuttake = 0;
      toggleIntake++;
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      toggleIntake = 0;
      toggleOuttake++;
    }

//Fly wheel
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      FWheel_toggle = !FWheel_toggle;
    }

    if (FWheel_toggle == true) {
      FWheel.move(127);
    }else if(FWheel_toggle == false) {
      FWheel.move(0);
    }

//Intake (toggle funtion)
   if (toggleIntake == 1) {
      toggleOuttake = 0;
      InTake.move(-127);
    }else if (toggleOuttake == 1) {
      toggleIntake = 0;
      InTake.move(127);
    }else if (toggleOuttake == 2 ) {
      InTake.move(0);
    }else if (toggleIntake == 2) {
      InTake.move(0);
    }else if (toggleOuttake == 3) {
      toggleOuttake = 1;
    }else if (toggleIntake == 3) {
      toggleIntake = 1;
    }else {
      InTake.move(0);
    }

  //Wings 
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      leftWing_State = !leftWing_State;
    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      rightWing_State = !rightWing_State;
    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      leftWing_State = !leftWing_State;
      rightWing_State = !rightWing_State;
    }

    if (leftWing_State == true) {
      leftWing.set_value(HIGH);
    }else if (leftWing_State == false) {
      leftWing.set_value(LOW);
    }

    if (rightWing_State == true) {
      rightWing.set_value(HIGH);
    }else if (rightWing_State == false) {
      rightWing.set_value(LOW);
    }

    pros::delay(10);
  }
}
