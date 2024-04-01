#include <LiquidCrystal_I2C.h>
#include <Pump.h>
#include <WaterLevelSensor.h>
#include <TimeFormatter.h>

// function prototype, needed when passing class reference
void initializePump(Pump &pump, int number, unsigned long feedingIntervalInMs, unsigned long feedingDurationInMs);
void monitorPump(Pump &pump);

LiquidCrystal_I2C lcd(0x27, 16, 4);  // Change the I2C address if necessary

Pump pump1(6);
Pump pump2(7);
Pump pump3(8);

const int sensor_lcd_row = 0;
WaterLevelSensor sensors[2] = 
{
  WaterLevelSensor(0),
  WaterLevelSensor(12)
};

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 4);
  lcd.backlight();
  
  initializePump(
    pump1, 
    1, // pump number
    TimeFormatter().withHours(0).withSeconds(120).toMillis(), // feeding interval
    TimeFormatter().withSeconds(23).toMillis()); // feeding duration

  initializePump(
    pump2, 
    2, // pump number
    TimeFormatter().withHours(4).toMillis(), // feeding interval
    TimeFormatter().withSeconds(20).toMillis());

  initializePump(
    pump3, 
    3, // pump number
    TimeFormatter().withHours(4).toMillis(), // feeding interval
    TimeFormatter().withSeconds(25).toMillis()); 
}

void loop()
{
  monitorPump(pump1);
  monitorPump(pump2);
  monitorPump(pump3);

  monitorSensors();
  delay(500);
}

void monitorSensors()
{
  for (int i = 0; i < 2; i++) {
    int column = i * 7; // We are displaying all sensors horizontally. Each will occupy 7 characters.
    lcd.setCursor(column, sensor_lcd_row);
    lcd.print("S" + String(i + 1) + ":" + (sensors[i].currentLevel()));
  }
}

void initializePump(Pump &pump, int number, unsigned long feedingIntervalInMs, unsigned long feedingDurationInMs)
{
  pump.feedingIntervalInMs = feedingIntervalInMs;
  pump.feedingDurationInMs = feedingDurationInMs;
  pump.number = number;
  
  lcd.setCursor(0, number);
  lcd.print("P" + String(number) + ": OFF");
}

void monitorPump(Pump &pump)
{
  unsigned long timePassed = pump.timePassedSinceLastOn();

  if (!pump.isOn)
  {
    
    if(timePassed > pump.feedingIntervalInMs)
    {
      pump.turnOn();
      updatePumpStatus(pump.number, "ON");
      return;
    }

    Serial.println(String(pump.feedingIntervalInMs - timePassed));

    updatePumpRemainingTime(pump.number, TimeFormatter().withMilliSeconds(pump.feedingIntervalInMs - timePassed).toReadableTime());
  }
  else
  {
    if(timePassed > pump.feedingDurationInMs)
    {
      pump.turnOff();
      updatePumpStatus(pump.number, "OFF");
      return;
    }
    
    Serial.println(String(pump.feedingDurationInMs - timePassed));
          
    updatePumpRemainingTime(pump.number, TimeFormatter().withMilliSeconds(pump.feedingDurationInMs - timePassed).toReadableTime());
  }
}

void updatePumpStatus(int pumpNumber, String status)
{
  lcd.setCursor(4, pumpNumber);
  // We are adding space to clear the previous timer
  lcd.print(status + "         ");
  
  Serial.println("P" + String(pumpNumber) + "STATUS: " + status);
}

void updatePumpRemainingTime(int pumpNumber, String remainingTime)
{
  lcd.setCursor(8, pumpNumber);
  lcd.print(remainingTime);
    
  Serial.println("P" + String(pumpNumber) + "REMAINING TIME: " + remainingTime);
}
