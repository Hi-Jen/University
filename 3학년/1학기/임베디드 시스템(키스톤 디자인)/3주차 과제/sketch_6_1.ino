const int sensorPin = A0;  
const int redPin = 6, greenPin = 7, bluePin = 8;  

const int colors[][3] = {
    {170, 0, 255}, 
    {255, 0, 0}, 
    {255, 170, 0},  
    {255, 255, 0}, 
    {0, 255, 0}, 
    {0, 0, 255}, 
    {0, 170, 255}  
};

void setup() {
    Serial.begin(9600);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void loop() {
    int sensorValue = analogRead(sensorPin);  // A0 핀 값 읽기 (0~1023)
    int colorIndex = map(sensorValue, 0, 1023, 0, 6);  // 0~1023 → 0~6 매핑
    changeColor(colorIndex);
    delay(100);  // 빠른 변화를 방지하기 위한 딜레이
}

void changeColor(int index) {
    Serial.print(index);
    Serial.print(", ");
    Serial.print(colors[index][0]);
    Serial.print(", ");
    Serial.print(colors[index][1]);
    Serial.print(", ");
    Serial.println(colors[index][2]);
    analogWrite(redPin, colors[index][0]);
    analogWrite(greenPin, colors[index][1]);
    analogWrite(bluePin, colors[index][2]);
}
