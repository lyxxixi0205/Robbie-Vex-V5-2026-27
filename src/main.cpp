#include "main.h"
#define _USE_MATH_DEFINES 
// #include "lemlib/api.hpp"
pros::Controller robbie(pros::E_CONTROLLER_MASTER); 
pros::MotorGroup left_mg({-10, 9}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup right_mg({1, -2}, pros::MotorGearset::green);
pros::ADIDigitalOut claw('G'); // Create a pneumatic in port A
pros::MotorGroup lift({-8, 7}, pros::MotorGearset::green);
// bool isSkillsRun = false;

Drivetrain drivetrain(
    &left_mg, // left motor group
    &right_mg, // right motor group
    11.5, // track width (12 inches)
    Omniwheel::NEW_275, // using new 4" omnis
    220, // drivetrain rpm
    2); // horizontal drift (2 is standard for normal drive)

Imu imu(20); 
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
	chassis.calibrate();
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
    // chassis.setPose(-0.1, 62.5, 180);
    // chassis.moveToPoint(0, 12.6, 4950/.);
    pros::lcd::set_text(1, "Auton Started");
    
    chassis.setPose(-62.5, -11.4, 132);
    chassis.moveToPoint(-52.5, -20.3, 1850);
    chassis.waitUntilDone();
    claw.set_value(false);
    
    // clamp.set_value
    

    
    // 	
    //   right_mg.move_velocity(-100);
    //   left_mg.move_velocity(-100);
    //   pros::delay(500);
    //   right_mg.move_velocity(100);
    //   left_mg.move_velocity(100);
    // 	pros::delay(500);
    // 	right_mg.move_velocity(-100);
    //   left_mg.move_velocity(-100);
}

// Routine: Red Left

// chassis.setPose(-62.5, -9, 135);
// chassis.moveToPoint(-51.6, -20.4, 2100, {.maxSpeed = 70});
// chassis.moveToPoint(-60.5, -10.9, 1700, {.forwards = false});
// chassis.turnToPoint(-47.7, 30, 1250);
// chassis.moveToPoint(-10.1, 13.1, 5450);

    // chassis.setPose(-62.5, -6.6, 90);
    // chassis.moveToPoint(0.2, -11.5, 6050);

    // chassis.setPose(-62.5, 0, -90);
    // chassis.moveToPoint(-57.7, 0, 1100, {.forwards = false, .minSpeed = 100});
    // chassis.moveToPoint(-63.4, 0, 1100);
    // chassis.moveToPoint(-46.3, 0, 2050, {.forwards = false});
    // chassis.turnToHeading(179, 1100);
    // chassis.moveToPoint(-47.7, -16, 2050); 
    // chassis.setPose(0, 0, 0);
    // chassis.moveToPoint(24,0,10000);
    // chassis.turnToHeading(-90,5000);
    // chassis.moveToPoint(24,10,10000);

    // bool isRedAlliance = true; // Red alliance match side
    //  // Autonomous skills challenge mode
    // bool distanceClear = true; // Distance sensor > 10 inches clear

// // Routine: Red Left
// if (isSkillsRun){
//     chassis.setPose(-62.5, -0.06, -90);
//     chassis.moveToPoint(-55, 0, 1350, {.forwards = false, .minSpeed = 100});
//     chassis.moveToPoint(-62.5, 0, 1250, {.minSpeed = 100});
//     chassis.moveToPoint(-47, 0, 1900, {.forwards = false, .minSpeed = 80});
//     chassis.turnToHeading(-181, 1100, {.minSpeed = 100});
//     chassis.moveToPoint(-48.2, -15.6, 2050);
//     chassis.moveToPoint(-48.2, -8.8, 1200, {.forwards = false});
//     chassis.turnToHeading(88, 1100, {.minSpeed = 114});
//     chassis.moveToPoint(-35, -10, 1850, {.minSpeed = 100});
//     chassis.turnToHeading(181, 1100, {.minSpeed = 100});
//     chassis.moveToPoint(-35, -61, 5050);
//     chassis.turnToHeading(-90, 1100, {.minSpeed = 100});
//     chassis.moveToPoint(-66.3, -60.1, 3350);
//     chassis.moveToPoint(-53.3, -59.7, 1700, {.forwards = false});
//     chassis.turnToHeading(-20, 1000);
//     chassis.moveToPoint(-50.6, -31.7, 3100, {.minSpeed = 80});
//     chassis.moveToPoint(-53.1, -61.8, 3200, {.forwards = false});
//     chassis.turnToHeading(-91, 1100);
//     chassis.moveToPoint(-66, -60.6, 1800);
//     }else{



  
	// drive_inches(24, 200,3000);
    // pros::delay(200);
	// turn_degrees(90, 200, 6000);
    // drive_inches(5,100,3000);
    // drive_inches(-)


/**7l
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
	 // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	// pros::MotorGroup left_mg({1, 10}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	// pros::MotorGroup right_mg({-11, -20}, pros::MotorGearset::green);

    while (true) {
        //arcade drive
        int leftY = robbie.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = robbie.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        chassis.arcade(leftY, rightX);
        
        //tank drive
        // int leftY = robbie.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // int rightY = robbie.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // chassis.tank(leftY, rightY);
        // CLAW CONTROLS
        if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            claw.set_value(true);
            robbie.set_text(0, 0, "L1 PRESSED");
        }
        else if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            claw.set_value(false);
            robbie.set_text(0, 0, "L2 PRESSED");
        }
        // LIFT CONTROLS
        if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            lift.move(70);
        }
        else if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            lift.move(-70);
        }
        else {
            lift.brake();
        }

        

        pros::delay(20);
    }
}
//     int leftY = robbie.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    //     int rightX = robbie.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //     // move the robot
    //     chassis.arcade(leftY, rightX);

    //     if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
	// 		lift.move(127);
	// 		robbie.set_text(0, 0, "R1 PRESSED");
	// 	}
	// 	else if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
	// 		lift.move(-127);
	// 		robbie.set_text(0, 0, "R2 PRESSED");
	// 	}
	// 	else {
	// 		lift.move(0);
	// 	}
    //     if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
	// 		claw.set_value(true);   // Open claw
	// 		robbie.set_text(0, 0, "L1 PRESSED");
	// 	}
	// 	else if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
	// 		claw.set_value(false);  // Close claw
	// 		robbie.set_text(0, 0, "L2 PRESSED");
	// 	}
    //     // Left joystick Y-axis controls forward/backward (Linear)
    //     // int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        
    //     // // Right joystick X-axis controls left/right (Turning)
    //     // int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //     // // Split Arcade Math
    //     // int left_side_power = power - turn;
    //     // int right_side_power = power + turn;

    //     // // Send voltages/power to the motors
    //     // left_mg.move(left_side_power);
    //     // right_mg.move(right_side_power);

		
    //     // if (robbie.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    //     //     lift.move(200);
    //     // }else if (pros::E_CONTROLLER_DIGITAL_R2){
    //     //     lift.move(-200);
    //     // }else{
    //     //     lift.move(0);
    //     // }
    //     // bool isSkillsRun = false;
    //     if (robbie.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
    //         isSkillsRun = true;
    //         autonomous();
    //     }
        
    //     if (robbie.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    //         isSkillsRun = false;
    //         autonomous();
    //     }
    //     // if(robbie.get_digital_new_press)
    //     // claw_pneumatic.set_value(true); // Extend
    //     // claw_pneumatic.set_value(false); // Retract
    //     // Prevent CPU hogging (20ms refresh rate matches the controller data rate)
    //     pros::delay(20);
    // }