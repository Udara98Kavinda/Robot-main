#ifndef IR_PANEL_H
#define IR_PANEL_H

#include <Arduino.h>

#define R4 A0
#define R3 A1
#define R2 A2
#define R1 A3
#define R0 A4
#define L0 A5
#define L1 A6
#define L2 A7
#define L3 A8
#define L4 A9

extern const int IR_PINS[10];

void IR_pin_configuration();
void read_IR_sensors(int readings[10]);
void print_IR_readings(const int readings[10]);
void calibrate_IR_sensors(int readings[10], int samples);
void digitalize_with_calibrated_threshold(const int analog_readings[10], const int thresholds[10], int digital[10]);


#endif // IR_PANEL_H
