// main.cpp
#include "Arduino.h"
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
	LIDARsetup();
	delay(200);
	distFromFloor = LIDARread();
	delay(1);
	//attachInterrupt(button0, wave0Select, RISING); // Interrupt attached to the button connected to pin 2
	//attachInterrupt(button1, wave1Select, RISING); // Interrupt attached to the button connected to pin 3
}

void loop() {
	int last_time = micros();
	int max_time = 0;
	while (1) {
		Serial.print(LIDARread());
		Serial.print(" ");
		for (size_t j = 0; j < 1000; j++) {
			LIDARread();
			if (micros() - last_time > max_time) {
				max_time = micros() - last_time;
			}
			last_time = micros();
		}
		Serial.println(max_time);
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
