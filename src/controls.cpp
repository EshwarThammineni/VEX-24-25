#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/misc.h"
#include "subsystems.hpp"

//new control system via state change cuz i read its better
bool state = false;
bool state1 = false;

void clampControl(){
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
        state = !state;
    }
    clamp1.set_value(state);
}

void intakeControl(){
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
        intake.move(127);
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intake.move(-127);
    } else {
        intake.move(0);
    }
}


//old lady brown code idk if this works with new version
double integralSum = 0;  // Renamed from 'integral'

void liftControl() {
    const double kP = 0.375;  // Proportional constant
    const double kI = 0;      // Integral constant
    const double kD = 1.5;    // Derivative constant

    static int currentState = 0;
    static bool yButtonPressed = false;
    static double previousError = 0;
    double targetPosition = 0; 

    const double tolerance = 10;  // Allowable error range for stopping
    const int maxSpeed = 227;     // Clamp motor velocity
    const int minSpeed = 0;       // Minimum motor speed to prevent jitter

    // Y button state machine
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (!yButtonPressed) {
            currentState = (currentState + 1) % 3; // Cycle through 3 states
            yButtonPressed = true;
            pros::lcd::print(0, "State: %d", currentState);
        }
    } else {
        yButtonPressed = false;
    }

    // Set target position based on current state
    switch (currentState) {
        case 1: // Loading position
            targetPosition = 270;
            pros::lcd::print(0, "Moving to loading");
            break;
        case 2: // Scoring position
            targetPosition = 1400;
            pros::lcd::print(0, "Moving to scoring");
            break;
        default: // Zero position
            targetPosition = 0;
            pros::lcd::print(0, "At zero");
            break;
    }

    // Get current position of the arm
    double currentPosition = lift.get_position();

    // Calculate the PID output to adjust motor speed
    double error = targetPosition - currentPosition;

    // Only accumulate integralSum if within a reasonable range to prevent wind-up
    if (abs(error) < 50) {
        integralSum += error;
    } else {
        integralSum = 0;
    }

    double derivative = error - previousError;
    previousError = error;

    // Calculate the PID output
    double output = kP * error + kI * integralSum + kD * derivative;

    // Apply a minimum speed threshold to prevent jitter near zero
    if (abs(output) < minSpeed && abs(error) > tolerance) {
        output = (output > 0) ? minSpeed : -minSpeed;
    }
    double pidOutput = output;

    // Stop the motor if within tolerance range
    if (abs(targetPosition - currentPosition) <= tolerance) {
        lift.move_velocity(0);  // Stop the motor
        integralSum = 0;        // Reset integral term
        previousError = 0;      // Reset error to avoid overshooting
    } else {
        lift.move_velocity(pidOutput);
    }
}


//expiramental idk if this works
void RedcheckColorAndAdjustSpeedRed() {
    optical_sensor.set_led_pwm(100); // Ensure the LED is on for color detection
    pros::c::optical_rgb_s_t color = optical_sensor.get_rgb();
    
    /*if (color.red >= 5 && color.red <= 15) {
        // Red value is within the range, run at normal speed
        hooks.move_velocity(600);
    } else if (color.blue > color.red) {
        // Blue detected, slow down
        pros::Task::delay(110);
        hooks.move_velocity(-600);
        pros::Task::delay(100);
        hooks.move_velocity(600);
    }
        */
}
   
/*void OpticalSensor() {

    while (true) {
        optical_sensor.set_led_pwm(100);
        int32_t disable_guestures();
        int32_t proximity = optical_sensor.get_proximity();
        if (proximity > 1){
            hooks.move_velocity(600);
        } 
        pros::delay(200);
    }
  }*/

void doinkerControl(){
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        state1 = !state1;
    }
    doinker.set_value(state1);
}
