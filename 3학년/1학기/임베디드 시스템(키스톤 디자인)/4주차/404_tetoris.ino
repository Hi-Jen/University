int speakerPin = 57;  
int buttonPin = 16;   
bool isPlaying = false;  


int tetrisMelody[] = {
  659, 494, 523, 587, 523, 494, 440, 
  440, 523, 659, 587, 523, 494, 523, 587, 659, 523, 440, 
  440};

int noteDuration = 8;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !isPlaying) {  
    isPlaying = true;
    delay(200);  

    for (int thisNote = 0; thisNote < sizeof(tetrisMelody) / sizeof(int); thisNote++) {
      int noteLength = 1000 / noteDuration;
      tone(speakerPin, tetrisMelody[thisNote], noteLength);
      delay(noteLength * 1.3);  
      noTone(speakerPin);
    }

    isPlaying = false;  
  }
}
