#include "Arduino.h"
#include "WaterLevelSensor.h"

WaterLevelSensor::WaterLevelSensor(int pin)
{
  _pin = pin;
  
  if (pin != -1)
  	pinMode(pin, INPUT);
}

String WaterLevelSensor::currentLevel()
{
  if (_pin == -1)
    return "-";
  
  bool isAboveMinimum = digitalRead(_pin);
  
  if (isAboveMinimum)
    return "OK "; // we need space to clear W in LOW
  else
    return "LOW";
}