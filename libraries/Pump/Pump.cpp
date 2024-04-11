#include "Arduino.h"
#include "Pump.h"

Pump::Pump(int pin) : isEnabled(true)
{
  _pin = pin;
  _lastOn = 0UL;
  pinMode(pin, OUTPUT);
  // Turn off the pump by default
  digitalWrite(_pin, HIGH);
}

void Pump::turnOn(unsigned long delayInMs)
{
  if (isOn) return;
  
  delay(delayInMs);
  isOn = true;
  digitalWrite(_pin, LOW);
  _lastOn = millis();  
}

void Pump::turnOff(unsigned long delayInMs)
{
  if (!isOn) return;
  
  delay(delayInMs);
  isOn = false;
  digitalWrite(_pin, HIGH);
}

unsigned long Pump::timePassedSinceLastOn()
{
  return millis() - _lastOn;
}