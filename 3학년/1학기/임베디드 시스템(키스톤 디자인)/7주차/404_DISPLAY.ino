#include <LiquidCrystal.h>

LiquidCrystal lcd(44, 45, 46, 47, 48, 49);

int x = 0;
int y = 0;
int dx = 1;
int dy = 1;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.print("404");
  delay(150);

  x += dx;
  y += dy;

  if (x <= 0 || x >= 13) {
    dx = -dx;
  }

  if (y <= 0 || y >= 1) {
    dy = -dy;
  }
}
