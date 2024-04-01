#ifndef TimeFormatter_h
#define TimeFormatter_h

#include "Arduino.h"

class TimeFormatter
{
  public:
  	TimeFormatter& withSeconds(int seconds);
  	TimeFormatter& withMinutes(int minutes);
  	TimeFormatter& withHours(int hours);
  	TimeFormatter& withMilliSeconds(unsigned long milliSeconds);
  	unsigned long toMillis();
  	String toReadableTime();
  private:
  	int _seconds;
  	int _minutes;
  	int _hours;
  	unsigned long _milliSeconds;
};

#endif