#ifndef Func_h
#define Func_h
#include "..\lib\Wire.h"
#include "LIDARLite.h"

LIDARLite LIDAR;

int LIDAR_read_count = 0;
volatile int samplePos = 0;
volatile uint32_t Rising_Edge_Time = 0;
volatile uint32_t r_i = 0;
volatile uint32_t readings[10];
volatile uint32_t r10_i = 0;
volatile uint32_t readings10[10];

int LIDARreadI2C() {
    LIDAR_read_count++;
    if (LIDAR_read_count > 99) {
        LIDAR_read_count = 0;
        return LIDAR.distance();
    } else {
        return LIDAR.distance(0); // no bias correction
    }
}

void LIDARsetup() {
    LIDAR.begin(0, true);
    LIDAR.configure(0);
}

int LIDARreadPWM() {
    return pulseIn(2, HIGH);
}

void LIDAR_Handler() {
    if (digitalRead(2)) {
        Rising_Edge_Time = micros();
    } else {
        if (micros() - Rising_Edge_Time > 200) {
            readings[r_i] = micros() - Rising_Edge_Time;
            if (r_i >= 9) {  // increment or reset r_i
                r_i = 0;
                readings10[r10_i] = readings[9];
                (r10_i >= 9) ? (r10_i = 0) : r10_i++;
            } else {
                r_i++;
            }
        }
    }
}

void TIMER_handler() {

}

#endif
