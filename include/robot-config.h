using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Left1;
extern motor Left2;
extern motor Left3;
extern motor Right1;
extern motor Right2;
extern motor Right3;
extern motor PTO_Left;
extern motor PTO_Right;
extern motor Intake;
extern controller Controller1;
extern digital_out DigitalOutA;
extern digital_out Elevation;
extern digital_out DigitalOutC;
extern digital_out IntakeElevation;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );