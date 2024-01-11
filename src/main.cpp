#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include <string>
#include <sys/unistd.h>
#include <unistd.h>
//testing for save
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(7, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 * 
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *huhuhuhuhuhuhuhuhuh
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
//Variables
  pros::Motor_Group Reset ({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20});
  bool ResetSwitch = false;

  pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::Motor_Group LDriveTrain ({-19, -20, -6});
  pros::Motor_Group RDriveTrain ({8, 9, 10});

  int LDriveTrainTEMP;
  int RDriveTrainTEMP;
  pros::Motor L1 {20};
  pros::Motor L2 {6};
  pros::Motor L3 {19};
  pros::Motor R1 {8};
  pros::Motor R2 {9};
  pros::Motor R3 {10};


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

//Motor Temprature
    //Left DriveTrain
      //LDriveTrainTEMP = (L1.get_temperature() + L2.get_temperature() + L3.get_temperature()) / 3; 
      //master.set_text(0, 25, "hi");
    //Right DriveTrain
      //RDriveTrainTEMP = (R1.get_temperature() + R2.get_temperature() + R3.get_temperature()) / 3; 
      //master.set_text(1, 0, "Hello");
    //Cata
      

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


//Reset switch
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      ResetSwitch = !ResetSwitch;
    }

    if (ResetSwitch == true) {
      Reset.move(0);
      pros::lcd::set_text(1, "PAUSE MOTORS --> ON (Down)");
    }else {
      ResetSwitch = false;
      pros::lcd::set_text(1, "PAUSE MOTORS --> OFF (Down)");
    }

//Small animation

		pros::delay(10);

  }
}
