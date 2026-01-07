#include "main.h"

double kp1 = 0.5;
int target1;

//Helpers that make sense when u think of it and are not cooked rotte
void intakeOn(){
    intake.move(127);
}

void intakeOff(){
    intake.move(0);
}

void bottomIntakeOnly(){
    flexIntake.move(127);
}

void bottomOff(){
    flexIntake.move(0);
}

void clampMogo(){
    clamp1.set_value(1);
}

void unclampMogo(){
    clamp1.set_value(0);
}

void doinkerDown(){
    doinker.set_value(1);
}

void doinkerUp(){
    doinker.set_value(0);
}