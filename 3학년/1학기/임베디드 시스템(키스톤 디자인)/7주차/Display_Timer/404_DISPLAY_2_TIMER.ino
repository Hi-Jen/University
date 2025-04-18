#include <LiquidCrystal.h>

LiquidCrystal lcd(44, 45, 46, 47, 48, 49);

int month = 4;
int day   = 18;
int hours   = 0;
int minutes = 0;
int seconds = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 1);
  lcd.print("DATE : ");
  if (month < 10) lcd.print('0');
  lcd.print(month);
  lcd.print(" - ");
  if (day < 10) lcd.print('0');
  lcd.print(day);
}

void loop() {
  seconds++;
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
      hours++;
      if (hours >= 24) {
        hours = 0;
        day++;

        lcd.setCursor(0, 1);
        lcd.print("DATE : ");
        if (month < 10) lcd.print('0');
        lcd.print(month);
        lcd.print(" - ");
        if (day < 10) lcd.print('0');
        lcd.print(day);
      }
    }
  }


  lcd.setCursor(0, 0);
  lcd.print("TIME: ");
  if (hours < 10)   lcd.print('0');
  lcd.print(hours);
  lcd.print(':');
  if (minutes < 10) lcd.print('0');
  lcd.print(minutes);
  lcd.print(':');
  if (seconds < 10) lcd.print('0');
  lcd.print(seconds);

  delay(1000);
}
