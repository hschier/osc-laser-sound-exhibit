// Func.h
#ifndef Func_h
#define Func_h
#include "..\lib\Wire.h"
#include "LIDARLite.h"

LIDARLite LIDAR;

volatile bool valid_target = 0;
volatile uint32_t floor_dist = 0;

int LIDAR_read_count = 0;
volatile int samplePos = 0;
volatile uint32_t Rising_Edge_Time = 0;

// hold the past few readings
volatile uint32_t r_i = 0;
#define r_b 3
volatile uint32_t readings[r_b];

// hold 10 (r100_b) readings, but only take 1 reading out of every 100 (r100_freq)
volatile uint32_t r100_i = 0;
volatile uint32_t r100_c = 0; // readings since last write to readings100
#define r100_b 30
#define r100_freq 200
volatile uint32_t readings100[r100_b];

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

uint32_t Floor_dist(){
    uint32_t floorDepth = 0;
    for (uint32_t v = 0; v < r100_b; v++) {
        if (readings100[v] > floorDepth) {
            floorDepth = readings100[v];
        }
    }
    return floorDepth;
}

void LIDAR_Handler() {
    uint32_t pulsewidth = micros() - Rising_Edge_Time;
    if (digitalRead(2)) {
        Rising_Edge_Time = micros();
    } else if (pulsewidth > 200 && pulsewidth < 8000) {
        floor_dist = Floor_dist();
        if (pulsewidth < floor_dist - 200) {
            valid_target = 1;
            r_i++;
            if (r_i >= r_b) r_i = 0;
            readings[r_i] = pulsewidth;
        } else {
            valid_target = 0;
        }
        r100_c++;
        if (r100_c >= r100_freq) {
            r100_c = 0;
            r100_i++;
            if (r100_i >= r100_b) r100_i = 0;
            readings100[r100_i] = pulsewidth;
        }
    }
}

#endif
