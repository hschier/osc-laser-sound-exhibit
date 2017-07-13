// main.cpp
#include "Arduino.h"
#include "DueTimer.h"
#include "Func.h"
#include "Waveforms.h"

int i = 0;
float SPEED_OF_SOUND = 343.0;
uint32_t sampleTime;
float distFromFloor;
uint32_t lambda;

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
	while (1) {
		float sum = 0;
		for (size_t m = 0; m < r_b; m++) {
			sum += readings[m];
		}
		lambda = ((uint32_t) sum) / r_b;
		Serial.print(lambda);
		Serial.print(" ");
		//Serial.print(micros());
		for (uint32_t k = 0; k < lambda / 25; k++) {
			Serial.print("=");
		}
		Serial.println();
	}
	int startTime = micros();
	analogWrite(DAC0, waveformsTable[0][i]); // write the selected waveform on DAC0
	distFromFloor = 3.0;
	sampleTime = ((distFromFloor/SPEED_OF_SOUND)/maxSamplesNum)*1000000.0;
	i++;
	if (i == maxSamplesNum)
		i = 0;
	while(micros()-startTime < sampleTime); // Hold the sample value for the sample time
}
