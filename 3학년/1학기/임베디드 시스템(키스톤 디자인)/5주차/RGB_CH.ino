#include <EEPROM.h>

int redPin = 6;
int greenPin = 7;
int bluePin = 8;

byte colorValues[9] = {
  255, 0, 0,
  0, 255, 0,
  0, 0, 255
};

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  for (int i = 0; i < 9; i++) {
    EEPROM.write(i, colorValues[i]);
  }

  delay(500);
}

void loop() {
  while(1){
  for (int i = 0; i < 3; i++) {
    byte r = EEPROM.read(i * 3);
    byte g = EEPROM.read(i * 3 + 1);
    byte b = EEPROM.read(i * 3 + 2);

    Serial.print(" ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.println(b);

    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);

    delay(1000);
  }
  }
}
