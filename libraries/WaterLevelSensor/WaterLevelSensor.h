#ifndef WaterLevelSensor_h
#define WaterLevelSensor_h

#include "Arduino.h"

class WaterLevelSensor
{
  public:
  	WaterLevelSensor(int pin = -1);
  	String currentLevel();
	bool isAboveMinimum();
  private:
  	int _pin;
};

#endif