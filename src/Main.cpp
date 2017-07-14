// Main.cpp
#include "Arduino.h"
#include "Func.h"
#include "Waveforms.h"

int i = 0;
uint32_t SPEED_OF_SOUND = 343000; // in mm per second
uint32_t lambda; // in mm
uint32_t freq = 0; // frequency in mHz
uint32_t lambda_time; // in uS
uint32_t sample_time; // in Hz

void setup() {
	analogWriteResolution(12); // set the analog output resolution to 12 bit
	analogReadResolution(12); // set the analog input resolution to 12 bit
	Serial.begin(115200);
	delay(200);
	delay(1);
	pinMode(2, INPUT);
	pinMode(13, OUTPUT);
	attachInterrupt(2, LIDAR_Handler, CHANGE);
}

void loop() {
	uint32_t sample_start = micros();
	uint32_t sum = 0;
	for (uint32_t m = 0; m < r_b; m++) sum += readings[m];
	if (valid_target || i > 0) { // advance if valid_target OR finish up wave
		i++;
		if (i >= maxSamplesNum) i = 0;
	}
	analogWrite(DAC1, waveformsTable[1][i]);
	lambda = floor_dist - (sum / r_b);
	freq = (1000 * SPEED_OF_SOUND) / lambda; // mHz
	lambda_time = (1000000 * lambda) / SPEED_OF_SOUND;
	sample_time = lambda_time / 120;
	while (micros() - sample_start <= sample_time); // wait for next sample
}
