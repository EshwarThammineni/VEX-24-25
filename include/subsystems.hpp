#pragma once

#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

//new system needs "inline" and needs to be done in this file rotte
inline pros::MotorGroup intake({10, 19}); //10 is first stage, 18 is second stage
inline pros::Motor lift(15);
inline pros::Motor hooks(19);
inline pros::Motor flexIntake(10);
inline pros::Rotation liftRotationSensor(12);
inline pros::Optical optical_sensor(12);

inline pros::adi::DigitalOut clamp1(1);
inline pros::adi::DigitalOut doinker(7);
inline pros::adi::DigitalOut ptoPiston(2);