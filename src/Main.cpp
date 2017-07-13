// main.cpp
#include "Arduino.h"
#include "DueTimer.h"
#include "Func.h"
#include "Waveforms.h"

int i = 0;
float SPEED_OF_SOUND = 343000.0; // in mm per second
float distFromFloor;
uint32_t lambda;
float freq = 0; // frequency
uint32_t lambda_time; // in uS

void setup() {
	analogWriteResolution(12); // set the analog output resolution to 12 bit (4096 levels)
	analogReadResolution(12); // set the analog input resolution to 12 bit
	Serial.begin(115200);
	delay(200);
	distFromFloor = LIDARreadPWM();
	delay(1);
	pinMode(2, INPUT);
	attachInterrupt(2, LIDAR_Handler, CHANGE);
}

void loop() {
	int sum = 0;
	for (size_t m = 0; m < r_b; m++) {
		sum += readings[m];
	}
	lambda = ((uint32_t) sum) / r_b;
	Serial.print(lambda);
	Serial.print(" ");
	freq = SPEED_OF_SOUND / (float) lambda;
	Serial.print(freq);
	Serial.print(" ");
	lambda_time = (uint32_t) ((1000000.0 * lambda) / SPEED_OF_SOUND);
	Serial.print(lambda_time);
	Serial.print(" ");
	for (uint32_t k = 0; k < lambda / 25; k++) {
		Serial.print("=");
	}
	Serial.println();
}
