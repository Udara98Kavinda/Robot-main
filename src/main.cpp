#include <Arduino.h>
#include "Get_readings.h"
#include "Motor_control.h"
#include "PID_controller.h"
#include "encoder.h"
#include "buzzer.h"


int thresholds[10];
int readings[10];
int digital[10];
int error = 0;
int previous_error = 0;
int pid_output = 0;
int integral_error = 0;


void setup() {
  pinMode(buzzer,OUTPUT);
  buzzer_on(1,200);
  delay(2000);
  Serial.begin(9600);
  IR_pin_configuration();
  motor_pin_configuration();
  Serial.println("IR sensors calibration started.");
  buzzer_on(3,100);
  //calibrate_IR_sensors(thresholds, 500); // Calibrate IR sensors with 500 samples, store thresholds
  buzzer_on(3,100);
  Serial.println("IR sensors calibration completed.");
 attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), countEncLeft, RISING);
 attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), countEncRight, RISING);
}

void loop() {
  Serial.println("Leftcounter: " + String(encoderCount_Left));
  Serial.println("Rightcounter: " + String(encoderCount_Right));
  read_IR_sensors(readings);
  digitalize_with_calibrated_threshold(readings, thresholds, digital);
  error = calculate_error(digital);
  pid_output = compute_pid(error, previous_error, KP, KD);
  previous_error = error;
  
  forward(100, 100, pid_output); // Use PID output for correction
  
}