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
  pros::Motor Cata(7);
  Cata.move(0);
  pros::Motor InTake(2);

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

//Intake (not main funtion)
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      toggleOuttake = 0;
      toggleIntake++;
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      toggleIntake = 0;
      toggleOuttake++;
    }

//Cata
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      Cata.move(127);
    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      Cata.move(-127);
    }

//Main function for intake (toggle)
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

		pros::delay(10);

  }
}
