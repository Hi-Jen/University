#include <EEPROM.h>

const int redPin = 6;
const int greenPin = 7;
const int bluePin = 8;
const int buttonPin = 19;

volatile bool interruptFlag = false;
bool reverse = false;
int index = 0;

byte rainbowColors[21] = {
  255,   0, 255,
  125,   100,   125,
 0,   0, 255,
  0, 255, 255,
  0, 255, 116,
255, 255,   0,
255,  90,   0
};

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  for (int i = 0; i < 21; i++) {
    EEPROM.write(i, rainbowColors[i]);
  }

  attachInterrupt(digitalPinToInterrupt(buttonPin), interrupt, FALLING);
  delay(500);
}

void loop() {
  showColor(index);
  delay(1000);

  if (interruptFlag) {
    interruptFlag = false;
    reverse = !reverse;
    Serial.println("버튼이 눌렸습니다 (방향 전환)");
  }

  if (!reverse) {
    index = (index + 1) % 7;
  } else {
    index = (index - 1 + 7) % 7;
  }
}

void showColor(int i) {
  byte b = EEPROM.read(i * 3);
  byte g = EEPROM.read(i * 3 + 1);
  byte r = EEPROM.read(i * 3 + 2);

  Serial.print("Color ");
  Serial.print(i);
  Serial.print(": ");
  Serial.print("R="); Serial.print(r);
  Serial.print(" G="); Serial.print(g);
  Serial.print(" B="); Serial.println(b);

  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void interrupt() {
  static unsigned long lastInterrupt = 0;
  unsigned long now = millis();
  if (now - lastInterrupt > 200) {
    interruptFlag = true;
    lastInterrupt = now;
  }
}
