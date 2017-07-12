// main.cpp
#include "Arduino.h"
#include "DueTimer.h"
#include "Func.h"
#include "Waveforms.h"

int i = 0;
float SPEED_OF_SOUND = 343.0;
int sampleTime;
float distFromFloor;

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
		Serial.print(Last_Reading);
		Serial.print(" ");
		Serial.println(micros());
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
