// main.cpp
#include "Arduino.h"
#include "..\lib\LIDARLite.h"
#include "..\lib\wire.h"
#include "Func.h"
#include "Waveforms.h"

int i = 0;
float SPEED_OF_SOUND = 343.0;
int sampleTime;
float distFromFloor;

void setup() {
	analogWriteResolution(12); // set the analog output resolution to 12 bit (4096 levels)
	analogReadResolution(12); // set the analog input resolution to 12 bit
	distFromFloor = LIDARread();
	//attachInterrupt(button0, wave0Select, RISING); // Interrupt attached to the button connected to pin 2
	//attachInterrupt(button1, wave1Select, RISING); // Interrupt attached to the button connected to pin 3
}

void loop() {
	int startTime = micros();
	analogWrite(DAC0, waveformsTable[0][i]); // write the selected waveform on DAC0
	distFromFloor = 3.0;
	sampleTime = ((distFromFloor/SPEED_OF_SOUND)/maxSamplesNum)*1000000.0;
	i++;
	if (i == maxSamplesNum)
		i = 0;
	while(micros()-startTime < sampleTime); // Hold the sample value for the sample time
}
