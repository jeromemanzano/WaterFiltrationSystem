#ifndef WaterLevelSensor_h
#define WaterLevelSensor_h

#include "Arduino.h"

class WaterLevelSensor
{
  public:
  	WaterLevelSensor(int pin);
  	String currentLevel();
  private:
  	int _pin;
};

#endif