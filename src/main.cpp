#include "main.h"
#define _USE_MATH_DEFINES 
// #include "lemlib/api.hpp"

pros::MotorGroup left_mg({1, 10}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup right_mg({-11, -20}, pros::MotorGearset::green);

Drivetrain drivetrain(
    &left_mg, // left motor group
    &right_mg, // right motor group
    12.0, // track width (12 inches)
    Omniwheel::NEW_275, // using new 4" omnis
    200, // drivetrain rpm
    2); // horizontal drift (2 is standard for normal drive)

Imu imu(_); 
OdomSensors sensors(nullptr, // vertical tracking wheel 1
                    nullptr, // vertical tracking wheel 2
                    nullptr, // horizontal tracking wheel 1
                    nullptr, // horizontal tracking wheel 2
                    &imu); // inertial sensor

 // --- PID Controllers ---
// Placeholder values - you will need to tune these!
ControllerSettings lateral_controller(10, 0, 3, 3, 1, 100, 3, 500, 20);
ControllerSettings angular_controller(2, 0, 10, 3, 1, 100, 3, 500, 0);

Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {}
	// static bool pressed = false;
// 	bool auton_requested = false;
// 	// pressed = !pressed;
// 	// if (pressed) {
// 	// 	pros::lcd::set_text(2, "I was pressed!");
// 	// } else {
// 	// 	pros::lcd::clear_line(2);
// 	// }
// 	auton_requested = true;
//     if (auton_requested) {
// 		auton_requested = false;
// 		autonomous();
// 	}
// }

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
	// chassis.calibrate();
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
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
//  void drive_inches(double inches, int speed, int timeout_ms) {
// 	pros::MotorGroup left_mg({1, 10}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
// 	pros::MotorGroup right_mg({-11, -20}, pros::MotorGearset::green);

//     // 1. Drivetrain Specifications
//     const double WHEEL_DIAMETER = 2.75; 
//     const double GEAR_RATIO = 1.0;       
    
//     // 2. Math Calculations
//     double circumference = WHEEL_DIAMETER * M_PI;
//     double wheel_rotations = inches / circumference;
//     double motor_degrees = wheel_rotations * 360.0 * GEAR_RATIO;
    
//     // 3. Reset internal encoders
//     left_mg.tare_position();
//     right_mg.tare_position();
    
//     // 4. Command motors to target position
//     left_mg.move_relative(motor_degrees, speed);
//     right_mg.move_relative(motor_degrees, speed);
    
//     // Track how much time has passed
//     int time_elapsed = 0;
    
//     // 5. Added the time_elapsed check to the loop condition
//     while (std::abs(left_mg.get_position() - motor_degrees) > 5 && time_elapsed < timeout_ms) {
//         pros::delay(20);
//         time_elapsed += 20; // Every loop takes 20ms, so add 20 to our timer
//     }
    
//     // Stop the motors firmly
//     left_mg.move_velocity(0);
//     right_mg.move_velocity(0);
// }

// void turn_degrees(double degrees, int speed, int timeout_ms) {
// 	pros::MotorGroup left_mg({1, 10}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
// 	pros::MotorGroup right_mg({-11, -20}, pros::MotorGearset::green);
//     // 1. Robot & Wheel Specifications (Change these to match your robot)
//     const double WHEEL_DIAMETER = 2.75;
//     const double TRACK_WIDTH = 11;     // Distance between left and right wheels in inches
//     const double GEAR_RATIO = 1.0;
    
//     // 2. Turning Math (Arc Length)
//     // The path the wheels draw while turning is a circle with a diameter equal to TRACK_WIDTH
//     double robot_circumference = TRACK_WIDTH * M_PI;
//     double inches_to_travel = robot_circumference * (degrees / 360.0);
    
//     // Convert target inches to motor degrees
//     double wheel_circumference = WHEEL_DIAMETER * M_PI;
//     double motor_degrees = (inches_to_travel / wheel_circumference) * 360.0 * GEAR_RATIO;
    
//     // 3. Reset internal encoders
//     left_mg.tare_position();
//     right_mg.tare_position();
    
//     // 4. Command motors (Opposite directions for a point turn)
//     // For a right turn (+ degrees), left moves forward, right moves backward

// 	left_mg.move_absolute(motor_degrees, speed);
// 	right_mg.move_absolute(-motor_degrees, speed);
    
//     int time_elapsed = 0;
    
//     // 5. Wait until the left motor reaches its target or timeout expires
//     while (std::abs(left_mg.get_position() - motor_degrees) > 5 && time_elapsed < timeout_ms) {
//         pros::delay(20);
//         time_elapsed += 20;
//     }
    
//     // Stop the motors firmly
//     left_mg.move_velocity(0);
//     right_mg.move_velocity(0);
// }

void autonomous() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(24,0,10000);

	// drive_inches(24, 200,3000);
    // pros::delay(200);
	// turn_degrees(90, 200, 6000);
    // drive_inches(5,100,3000);
    // drive_inches(-)
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::MotorGroup left_mg({1, 10}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-11, -20}, pros::MotorGearset::green);


	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0); 

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

        // Left joystick Y-axis controls forward/backward (Linear)
        // int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        
        // // Right joystick X-axis controls left/right (Turning)
        // int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // // Split Arcade Math
        // int left_side_power = power - turn;
        // int right_side_power = power + turn;

        // // Send voltages/power to the motors
        // left_mg.move(left_side_power);
        // right_mg.move(right_side_power);

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			autonomous();
		}
        // Prevent CPU hogging (20ms refresh rate matches the controller data rate)
        pros::delay(20);
    }
}