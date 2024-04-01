#include "Arduino.h"
#include "Pump.h"

Pump::Pump(int pin)
{
  _pin = pin;
  _lastOn = 0UL;
  pinMode(pin, OUTPUT);
}

void Pump::turnOn()
{
  if (isOn) return;
  
  isOn = true;
  digitalWrite(_pin, HIGH);
  _lastOn = millis();  
}

void Pump::turnOff()
{
  if (!isOn) return;
  
  isOn = false;
  digitalWrite(_pin, LOW);
}

unsigned long Pump::timePassedSinceLastOn()
{
  return millis() - _lastOn;
}