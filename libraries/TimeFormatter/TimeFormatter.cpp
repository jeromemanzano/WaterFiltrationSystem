#include "Arduino.h"
#include "TimeFormatter.h"

TimeFormatter& TimeFormatter::withSeconds(int seconds)
{
  _seconds = seconds;
  return *this;
}

TimeFormatter& TimeFormatter::withMilliSeconds(unsigned long milliSeconds)
{
  _milliSeconds = milliSeconds;
  return *this;
}

TimeFormatter& TimeFormatter::withMinutes(int minutes)
{
  _minutes = minutes;
  return *this;
}

TimeFormatter& TimeFormatter::withHours(int hours)
{
  _hours = hours;
  return *this;
}

String pad(int value)
{
  if (value > 9)
    return String(value);
  else
    return "0" + String(value);
}

String TimeFormatter::toReadableTime()
{
  unsigned long totalMillis = toMillis();
  int hours = totalMillis / 3600000UL;
  unsigned long remainderHours = totalMillis % 3600000UL;
  int minutes = remainderHours / 60000UL;
  unsigned long remainderMinutes = remainderHours % 60000UL;
  int seconds = remainderMinutes / 1000UL;
  
  return pad(hours) + ":" + pad(minutes) + ":" + pad(seconds);
}

unsigned long TimeFormatter::toMillis()
{
  return 
    (1000UL * 60UL * 60UL * _hours) + 
    (1000UL * 60UL * _minutes) + 
    (1000UL * _seconds) + 
    _milliSeconds;
}