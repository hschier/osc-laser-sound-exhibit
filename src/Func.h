// Func.h
#ifndef Func_h
#define Func_h
#include "..\lib\Wire.h"
#include "LIDARLite.h"

// DIP-8 Switch pins
#define SWITCH_1_WAVETYPE1 46
#define SWITCH_2_WAVETYPE2 44
// 00 - Sine
// 10 - Triangle
// 01 - Sawtooth
// 11 - Square
#define SWITCH_3_ 42
#define SWITCH_4_ 40
#define SWITCH_5_ 38
#define SWITCH_6_ 36
#define SWITCH_7_ 34
#define SWITCH_8_FLOORMODE 32

#define LIDAR_PIN 2

LIDARLite LIDAR;

volatile bool valid_target = 0;
volatile uint32_t floor_dist = 0;

int LIDAR_read_count = 0;
volatile int samplePos = 0;
volatile uint32_t Rising_Edge_Time = 0;

// hold the past few readings
volatile uint32_t r_i = 0;
#define r_b 4
volatile uint32_t readings[r_b];

// hold (r100_b) readings, but only take 1 reading out of every (r100_freq)
volatile uint32_t r100_i = 0;
volatile uint32_t r100_c = 0; // readings since last write to readings100
#define r100_b 20
#define r100_freq 200
volatile uint32_t readings100[r100_b];
// 1 unit = 1/42mm


uint32_t timer_read(uint32_t timer_no) {
    volatile uint32_t* p = (uint32_t *) (0x40080010 + (0x40 * timer_no));
    return p[0];
}

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

uint32_t Find_Floor_dist(){
    // TODO: improve this function
    // fd is the max distance seen in readings100
    uint32_t fd = 0;
    // iterate through readings100, store the largest value in fd
    for (uint32_t v = 0; v < r100_b; v++) {
        if (readings100[v] > fd) {
            fd = readings100[v];
        }
    }
    return fd;
}

// 1 unit = 1/42mm
void LIDAR_Handler() {
    // assume that it is a falling edge, and save the timestamp
    uint32_t pulsewidth = timer_read(1) - Rising_Edge_Time;

    // if it's a rising edge
    if (digitalRead(2)) {
        // save the timestamp for later to make a pulsewidth on a falling edge
        Rising_Edge_Time = timer_read(1);
        // forget about the stored pulsewidth, it will be overwriten later
        return;
    }

    // we know it's a falling edge, now discard values out of range
    // 1 unit of pulsewidth is 1/42 of a mm
    if (pulsewidth < 200*42 || pulsewidth > 8000*42) return;

    // store the pulse in the readings100 array for wall detection
    // we store any valid value
    r100_c++;
    if (r100_c >= r100_freq) {
        r100_c = 0;
        r100_i++;
        if (r100_i >= r100_b) r100_i = 0;
        readings100[r100_i] = pulsewidth;
    }

    // find the floor distance to discard more invalid readings
    floor_dist = Find_Floor_dist();
    // check if the value is far enough from the floor
    if (pulsewidth < floor_dist - 170*42) {
        // an object is detected, so set the valid_target global
        valid_target = 1;
        // store the pulse in readings
        r_i++;
        if (r_i >= r_b) r_i = 0;
        readings[r_i] = pulsewidth;
    } else {
        // the wall is detected, so no valid target
        valid_target = 0;
    }
}

#endif
