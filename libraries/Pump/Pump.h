#ifndef Pump_h
#define Pump_h

#include "Arduino.h"

class Pump
{
  public:
  	Pump(int pin);
  	void turnOn(unsigned long delayInMs = 0);
  	void turnOff(unsigned long delayInMs = 0);
  	unsigned long feedingIntervalInMs;
  	unsigned long feedingDurationInMs;
  	int number;
  	bool isOn;
  	bool isEnabled;
  	unsigned long timePassedSinceLastOn();
  private:
  	int _pin;
  	unsigned long _lastOn;
};

#endif