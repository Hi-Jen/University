int speakerPin = 57;
int buttonPlay = 21;
int buttonLow = 16;
int buttonHigh = 17;
int potPin = A0;

bool isPlaying = false;
float pitchFactor = 1.0;

int tetrisMelody[] = {
  659, 494, 523, 587, 523, 494, 440, 
  440, 523, 659, 587, 523, 494, 523, 587, 659, 523, 440, 
  440
};

void setup() {
  pinMode(buttonPlay, INPUT_PULLUP);
  pinMode(buttonLow, INPUT_PULLUP);
  pinMode(buttonHigh, INPUT_PULLUP);
  pinMode(potPin, INPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  int noteDuration = map(potValue, 0, 1023, 4, 16);

  if (digitalRead(buttonLow) == LOW) {  
    pitchFactor -= 0.1;
    if (pitchFactor < 0.5) pitchFactor = 0.5;  
    delay(200);
  }

  if (digitalRead(buttonHigh) == LOW) {  
    pitchFactor += 0.1;
    delay(200);
  }

  if (digitalRead(buttonPlay) == LOW && !isPlaying) {  
    isPlaying = true;
    delay(200);

    for (int thisNote = 0; thisNote < sizeof(tetrisMelody) / sizeof(int); thisNote++) {
      int noteLength = 1000 / noteDuration;
      int pitch = tetrisMelody[thisNote] * pitchFactor;

      tone(speakerPin, pitch, noteLength);
      delay(noteLength * 1.3);
      noTone(speakerPin);
    }

    isPlaying = false;
  }
}

