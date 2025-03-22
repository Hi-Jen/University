// 아두이노 Mega 2560 보드의 5,6,7번 LED에서 빨, 주, 노, 초, 파, 남, 보라색 순으로 빛나게 하는 과제
// 보드가 노후되어 그런건지 올바른 RGB값인 {255, 0 , 0}(Red)을 입력했지만 출력값은 Yellow ..
// 팀원들과 상의 후 약간의 하드코딩을 하기로 함.
// 아두이노 보드의 출력 RGB값을 기억한 후 대략적인 색깔 순으로 RGB 코드 순서만 바꿔 마무리함.
// 다른 조의 상황도 별반 다를게 없었다.

const int sensorPin = A0;  
const int redPin = 6, greenPin = 7, bluePin = 8;  // LED 

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
    delay(100);  
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
