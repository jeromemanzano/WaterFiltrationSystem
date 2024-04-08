#include <LiquidCrystal_I2C.h>
#include <Pump.h>
#include <WaterLevelSensor.h>
#include <TimeFormatter.h>

const int sensor_lcd_row = 0;
 // delay between turning on/off the pump. This is to prevent multiple pumps from turning on/off at the same time
const unsigned long toggle_delay_ms = 2000;

// function prototype, needed when passing class reference
void initializePump(Pump &pump, int number, unsigned long feedingIntervalInMs, unsigned long feedingDurationInMs);
void monitorPump(Pump &pump);
void updatePumpStatus(Pump &pump, bool turnOn);

LiquidCrystal_I2C _lcd(0x27, 16, 4);  // Change the I2C address if necessary

Pump _pump1(6);
Pump _pump2(7);
Pump _pump3(8);

WaterLevelSensor _sensor1 = WaterLevelSensor(0);

void setup()
{
  Serial.begin(9600);

  _lcd.begin(16, 4);
  _lcd.backlight();
  
  initializePump(
    _pump1, 
    1, // pump number
    TimeFormatter().withHours(0).withSeconds(120).toMillis(), // feeding interval
    TimeFormatter().withSeconds(23).toMillis()); // feeding duration

  initializePump(
    _pump2, 
    2, // pump number
    TimeFormatter().withHours(4).toMillis(), // feeding interval
    TimeFormatter().withSeconds(20).toMillis());

  initializePump(
    _pump3, 
    3, // pump number
    TimeFormatter().withHours(4).toMillis(), // feeding interval
    TimeFormatter().withSeconds(25).toMillis()); 
}

void loop()
{
  monitorPump(_pump1);
  monitorPump(_pump2);
  monitorPump(_pump3);

  monitorSensors();
  delay(500);
}

void monitorSensors()
{
  _lcd.setCursor(0, sensor_lcd_row);
  _lcd.print("S1:" + _sensor1.currentLevel());

  if (!_sensor1.isAboveMinimum())
  {
    _pump2.isEnabled = false;
    _pump3.isEnabled = false;
  }
}

void initializePump(Pump &pump, int number, unsigned long feedingIntervalInMs, unsigned long feedingDurationInMs)
{
  pump.feedingIntervalInMs = feedingIntervalInMs;
  pump.feedingDurationInMs = feedingDurationInMs;
  pump.number = number;
  
  _lcd.setCursor(0, number);
  _lcd.print("P" + String(number) + ": OFF");
}

void monitorPump(Pump &pump)
{
  if (!pump.isEnabled)
  {
    if (pump.isOn)
    {
      updatePumpStatus(pump, false);
    }
    // This will prevent the pump from turning on and timer from starting
    return;
  }

  unsigned long timePassed = pump.timePassedSinceLastOn();

  if (!pump.isOn)
  {
    if(timePassed > pump.feedingIntervalInMs)
    {
      updatePumpStatus(pump, true);
      return;
    }

    updatePumpRemainingTime(pump.number, TimeFormatter().withMilliSeconds(pump.feedingIntervalInMs - timePassed).toReadableTime());
  }
  else
  {
    if(timePassed > pump.feedingDurationInMs)
    {
      updatePumpStatus(pump, false);
      return;
    }
    
    updatePumpRemainingTime(pump.number, TimeFormatter().withMilliSeconds(pump.feedingDurationInMs - timePassed).toReadableTime());
  }
}

void updatePumpStatus(Pump &pump, bool turnOn)
{
  _lcd.setCursor(4, pump.number);

  if (turnOn)
  {
    pump.turnOn(toggle_delay_ms);
      
    // We are adding space to clear the previous timer
    _lcd.print("ON");
  }
  else
  {
    pump.turnOff();
    _lcd.print("OFF");
  }
  
  updatePumpRemainingTime(pump.number, "--:--:--");
}

/**
 * Updates the display with the remaining time for the pump to change its status
 * @param pumpNumber The pump number
 * @param remainingTime The remaining time in HH:MM:SS format
 */
void updatePumpRemainingTime(int pumpNumber, String remainingTime)
{
  _lcd.setCursor(8, pumpNumber);
  _lcd.print(remainingTime);
    
  Serial.println("P" + String(pumpNumber) + "REMAINING TIME: " + remainingTime);
}
