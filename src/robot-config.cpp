#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Left1 = motor(PORT1, ratio6_1, true);
motor Left2 = motor(PORT11, ratio6_1, true);
motor Left3 = motor(PORT5, ratio6_1, true);
motor Right1 = motor(PORT14, ratio6_1, false);
motor Right2 = motor(PORT12, ratio6_1, false);
motor Right3 = motor(PORT2, ratio6_1, false);
motor PTO_Left = motor(PORT3, ratio6_1, false);
motor PTO_Right = motor(PORT13, ratio6_1, true);
motor Intake = motor(PORT4, ratio6_1, false);
controller Controller1 = controller(primary);
//digital_out DigitalOutA = digital_out(Brain.ThreeWirePort.A);
digital_out Elevation = digital_out(Brain.ThreeWirePort.B);
//digital_out DigitalOutC = digital_out(Brain.ThreeWirePort.C);
digital_out IntakeElevation = digital_out(Brain.ThreeWirePort.A);

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