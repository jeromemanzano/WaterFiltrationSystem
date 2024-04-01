#ifndef Pump_h
#define Pump_h

#include "Arduino.h"

class Pump
{
  public:
  	Pump(int pin);
  	void turnOn();
  	void turnOff();
  	unsigned long feedingIntervalInMs;
  	unsigned long feedingDurationInMs;
  	int number;
  	bool isOn;
  	unsigned long timePassedSinceLastOn();
  private:
  	int _pin;
  	unsigned long _lastOn;
};

#endif