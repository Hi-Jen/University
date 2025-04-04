#include <EEPROM.h>

int tempPin = 55;
int lightPin = 56;
int speakerPin = 57;

int melodyLength = 19;

int baseMelody[] = {
  659, 494, 523, 587, 523, 494, 440,
  440, 523, 659, 587, 523, 494, 523, 587, 659, 523, 440,
  440
};

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);

  for (int i = 0; i < melodyLength; i++) {
    EEPROM.put(i * sizeof(int), baseMelody[i]);
  }

  delay(500);
}

void loop() {
  int tempValue = analogRead(tempPin);
  int lightValue = analogRead(lightPin);

  Serial.print("Temp: ");
  Serial.print(tempValue);
  Serial.print("  Light: ");
  Serial.println(lightValue);

  if (tempValue >= 170 && lightValue >= 40) {
    for (int i = 0; i < melodyLength; i++) {
      int note;
      EEPROM.get(i * sizeof(int), note);
      if (note > 0) {
        tone(speakerPin, note, 300);
        delay(150);
        noTone(speakerPin);
      } else {
        delay(150);
      }
    }
  }

  delay(1000);
}
