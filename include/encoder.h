#ifndef ENCODER_H
#define ENCODER_H

#define ENCODER_LEFT_A 19 // Pin for encoder A
#define ENCODER_LEFT_B 18 // Pin for encoder B
#define ENCODER_RIGHT_A 2 // Pin for encoder A
#define ENCODER_RIGHT_B 3 // Pin for encoder B

extern volatile long encoderCount_Left;
extern volatile long encoderCount_Right;

void countEncLeft();
void countEncRight();

#endif