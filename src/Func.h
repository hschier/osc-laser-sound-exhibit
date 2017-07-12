#ifndef Func_h
#define Func_h
#include "..\lib\Wire.h"
#include "LIDARLite.h"

LIDARLite LIDAR;

int LIDAR_read_count = 0;
volatile int samplePos = 0;
volatile uint32_t Rising_Edge_Time = 0;
volatile uint32_t Last_Reading = 0;

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
        Last_Reading = micros() - Rising_Edge_Time;
    }
}

void TIMER_handler() {

}

#endif
