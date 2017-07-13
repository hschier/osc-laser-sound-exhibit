// main.cpp
#include "Arduino.h"
#include "DueTimer.h"
#include "Func.h"
#include "Waveforms.h"

int i = 0;
uint32_t SPEED_OF_SOUND = 343000; // in mm per second
float distFromFloor;
uint32_t lambda; // in mm
uint32_t freq = 0; // frequency in mHz
uint32_t lambda_time; // in uS
float sample_freq; // in Hz

void setup() {
	analogWriteResolution(12); // set the analog output resolution to 12 bit
	analogReadResolution(12); // set the analog input resolution to 12 bit
	Serial.begin(115200);
	delay(200);
	distFromFloor = LIDARreadPWM();
	delay(1);
	pinMode(2, INPUT);
	pinMode(13, OUTPUT);
	attachInterrupt(2, LIDAR_Handler, CHANGE);
	Timer0.attachInterrupt(TIMER_handler);
	Timer0.start(100.0);
}

void loop() {
	uint32_t sum = 0;
	for (uint32_t m = 0; m < r_b; m++) {
		sum += readings[m];
	}
	lambda = sum / r_b;
	freq = (1000 * SPEED_OF_SOUND) / lambda; // mHz
	lambda_time = (1000000 * lambda) / SPEED_OF_SOUND;
	sample_freq = ((float)(freq * maxSamplesNum)/1000.0);
	/*
	Serial.print(lambda);
	Serial.print(" ");
	Serial.print(freq);
	Serial.print(" ");
	Serial.print(lambda_time);
	Serial.print(" ");
	Serial.print(sample_freq);
	Serial.print(" ");
	for (uint32_t k = 0; k < lambda / 25; k++) {
		Serial.print("=");
	}
	Serial.println();
	*/

}
