// main.cpp
#include "Arduino.h"
#include "Waveforms.h"
#include "Func.h"

int i = 0;
int sampleTime;
int distFromFloor;

void setup() {
	analogWriteResolution(12); // set the analog output resolution to 12 bit (4096 levels)
	analogReadResolution(12); // set the analog input resolution to 12 bit
	distFromFloor = LIDARread();
	//attachInterrupt(button0, wave0Select, RISING); // Interrupt attached to the button connected to pin 2
	//attachInterrupt(button1, wave1Select, RISING); // Interrupt attached to the button connected to pin 3
}

void loop() {
	analogWrite(DAC0, waveformsTable[0][i]); // write the selected waveform on DAC0
	i++;
	if (i == maxSamplesNum) {

		sampleTime =
		i = 0;
	}
	delayMicroseconds(sampleTime); // Hold the sample value for the sample time
}
