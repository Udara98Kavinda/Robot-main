#include "Motor_control.h"
#include "encoder.h"
#include "action.h"
#include "Get_readings.h"
#include <Arduino.h>

// Array to store detected cross types
char crossArray[50];
int crossIndex = 0;

// Helper: Stop, reverse slowly, then go forward
void handleCrossApproach() {
    stopMotors();
    backward(10, 10, 0); // slow backward
    delay(200);
    stopMotors();
    encoderCount_Left = 0;
    encoderCount_Right = 0;
    forward(100, 100, 0);
    while (encoderCount_Left < 100 && encoderCount_Right < 100) {
        if (encoderCount_Right >= 100) forward(100, 0, 0);
        if (encoderCount_Left >= 100) forward(100, 0, 0);
    }
    stopMotors();
}

// Main cross detection handler
void handleCross(char crossType, bool Lleft = false, bool Lright = false) {
    handleCrossApproach();
    if (crossType == '+' || crossType == 'T') {
        stopMotors();
        // Turn right
        backward(0, 100, 0); // right backward
        forward(100, 0, 0);  // left forward
        delay(500); // adjust as needed for turn
        stopMotors();
        crossArray[crossIndex++] = 'R';
    } else if (crossType == 'L' && Lright) {
        stopMotors();
        // Turn right
        backward(0, 100, 0);
        forward(100, 0, 0);
        delay(500);
        stopMotors();
        crossArray[crossIndex++] = 'R';
    } else if (crossType == 'L' && Lleft) {
        stopMotors();
        // Turn left
        backward(100, 0, 0);
        forward(0, 100, 0);
        delay(500);
        stopMotors();
        crossArray[crossIndex++] = 'L';
    }
}

void handleSpecialCross(const char* crossType, const int analog_readings[9], const int thresholds[9]) {
    int irArray[9];
    // Move a bit forward before checking
    forward(100, 100, 0);
    delay(200);
    stopMotors();
    digitalize_with_calibrated_threshold(analog_readings, thresholds, irArray);

    if (strcmp(crossType, "t_left") == 0) {
        bool tCross = (irArray[3] == 1 || irArray[4] == 1 || irArray[5] == 1);
        bool allZero = (irArray[0] == 0 && irArray[1] == 0 && irArray[2] == 0 && irArray[3] == 0 && irArray[4] == 0 && irArray[5] == 0 && irArray[6] == 0 && irArray[7] == 0 && irArray[8] == 0);
        if (tCross) {
            crossArray[crossIndex++] = 'S';
        } else if (allZero) {
            crossArray[crossIndex++] = 'L';
            // Turn left
            
        }
    } 
    else if (strcmp(crossType, "t_right") == 0) {
        // Move forward and turn right
        //Turn right
    } 
    else if (strcmp(crossType, "cross") == 0) {
        bool allOne = (irArray[0] == 1 && irArray[1] == 1 && irArray[2] == 1 && irArray[3] == 1 && irArray[4] == 1 && irArray[5] == 1 && irArray[6] == 1 && irArray[7] == 1 && irArray[8] == 1);
        bool allZero = (irArray[0] == 0 && irArray[1] == 0 && irArray[2] == 0 && irArray[3] == 0 && irArray[4] == 0 && irArray[5] == 0 && irArray[6] == 0 && irArray[7] == 0 && irArray[8] == 0);
        bool plusCross = (irArray[3] == 1 || irArray[4] == 1 || irArray[5] == 1);
        if (allOne) {
            crossArray[crossIndex++] = 'D';
        } 
        
        else if (allZero) {
            crossArray[crossIndex++] = 'R';
            //Turn right
        } 
        
        else if (plusCross && !allOne) {
            //Turn right
            crossArray[crossIndex++] = 'R';
        }
    }
}

