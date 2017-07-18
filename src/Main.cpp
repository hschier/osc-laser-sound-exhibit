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
	pinMode(2, INPUT);
	pinMode(13, OUTPUT);
	pinMode(SWITCH_1_WAVETYPE1, INPUT);
	pinMode(SWITCH_2_WAVETYPE2, INPUT);
	pinMode(SWITCH_8_FLOORMODE, INPUT);
	attachInterrupt(LIDAR_PIN, LIDAR_Handler, CHANGE);
	delay(200);
}

void loop() {
	uint32_t sample_start = micros();
	uint32_t sum = 0;
	for (uint32_t m = 0; m < r_b; m++) sum += readings[m];
	if (valid_target || i > 0) { // advance if valid_target OR finish up wave
		i++;
		if (i >= maxSamplesNum) i = 0;
	}
	// change waveform based on switch position
	uint32_t wavetype = digitalRead(SWITCH_1_WAVETYPE1)
	                  + digitalRead(SWITCH_2_WAVETYPE2) * 2;
	analogWrite(DAC1, waveformsTable[wavetype][i]);
	lambda = sum / r_b;
	// if switch 8 is in the off position, then use from-floor mode (default)
	if (!digitalRead(SWITCH_8_FLOORMODE)) lambda = floor_dist - lambda;
	lambda = ((lambda * 10642) / 10000) - 169; // calibration
	freq = (1000 * SPEED_OF_SOUND) / lambda; // mHz
	lambda_time = (1000000 * lambda) / SPEED_OF_SOUND;
	sample_time = lambda_time / 120;
	while (micros() - sample_start < sample_time); // wait for next sample
}
