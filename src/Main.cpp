// main.cpp
#include "Arduino.h"
#include "..\lib\LIDARLite.h"
#include "..\lib\wire.h"
#include "Func.h"
#include "Waveforms.h"

int i = 0;
<<<<<<< HEAD
int sample;
=======
int sampleTime;
float distFromFloor;
>>>>>>> remove-analog-read

void setup() {
	analogWriteResolution(12); // set the analog output resolution to 12 bit (4096 levels)
	analogReadResolution(12); // set the analog input resolution to 12 bit
<<<<<<< HEAD

	attachInterrupt(button0, wave0Select, RISING); // Interrupt attached to the button connected to pin 2
	attachInterrupt(button1, wave1Select, RISING); // Interrupt attached to the button connected to pin 3
=======
	distFromFloor = LIDARread();
	//attachInterrupt(button0, wave0Select, RISING); // Interrupt attached to the button connected to pin 2
	//attachInterrupt(button1, wave1Select, RISING); // Interrupt attached to the button connected to pin 3
>>>>>>> remove-analog-read
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
