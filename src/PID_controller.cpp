#include <Arduino.h>
#include "Get_readings.h"
#include "PID_controller.h"


int calculate_error(const int digital[10]) {
    // Weights: L3,R3=20, L2,R2=10, L1,R1=5, L0,R0=0; negative for left
    const int weights[8] = {-20, -10, -5, 0, 0, 5, 10, 20};
    int error = 0;
    for (int i = 0; i < 8; i++) {
        error += weights[i] * digital[i+1]; // skip L4 (0) and R4 (9)
    }
    return error;
}

int compute_pid(int error, int previous_error, float Kp, float Kd) {
    int derivative = error - previous_error;
    int pid_output = Kp * error + Kd * derivative;
    return pid_output;
}
