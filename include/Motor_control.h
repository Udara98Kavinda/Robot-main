#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Define motor control pins
#define LM_EN 6
#define LM_BW 26
#define LM_FW 28
#define RM_EN 7
#define RM_BW 22
#define RM_FW 24


void motor_pin_configuration();
void setMotorSpeed(int leftSpeed, int rightSpeed, int error);
void forward(int leftSpeed, int rightSpeed, int error);
void backward(int leftSpeed, int rightSpeed, int error);
void stopMotors();

#endif // MOTOR_CONTROL_H
