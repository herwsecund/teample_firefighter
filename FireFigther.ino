#include <Arduino.h>
#include <Servo.h>

// 부저
int buzz = 4;

// 현관문
Servo myServo;
int door_1 = 3;

// 창문
int window_1_o = 6;
int window_1_c = 7;
int window_2_o = 8;
int window_2_c = 9;

// 불꽃감지센서
// 1
int fire1_1 = 16;
int fire1_2 = 17;
int fire1_3 = 18;
// 2
int fire2_1 = 21;
int fire2_2 = 22;
int fire2_3 = 23;
int fire2_4 = 24;
int fire2_5 = 25;
int fire2_6 = 35;
// 3 거실
int fire3_1 = 26;
int fire3_2 = 27;
int fire3_3 = 28;
int fire3_4 = 29;
int fire3_5 = 30;
int fire3_6 = 31;
int fire3_7 = 32;
int fire3_8 = 33;
int fire3_9 = 34;

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);

  pinMode(fire1_1, INPUT_PULLUP);
  pinMode(fire1_2, INPUT_PULLUP);
  pinMode(fire1_3, INPUT_PULLUP);

  pinMode(fire2_1, INPUT);
  pinMode(fire2_2, INPUT);
  pinMode(fire2_3, INPUT);
  pinMode(fire2_4, INPUT);
  pinMode(fire2_5, INPUT);
  pinMode(fire2_6, INPUT);

  pinMode(fire3_1, INPUT);
  pinMode(fire3_2, INPUT);
  pinMode(fire3_3, INPUT);
  pinMode(fire3_4, INPUT);
  pinMode(fire3_5, INPUT);
  pinMode(fire3_6, INPUT);
  pinMode(fire3_7, INPUT);
  pinMode(fire3_8, INPUT);
  pinMode(fire3_9, INPUT);

  myServo.attach(door_1);

  pinMode(window_1_o, OUTPUT);
  pinMode(window_1_c, OUTPUT);
  pinMode(window_2_o, OUTPUT);
  pinMode(window_2_c, OUTPUT);

  pinMode(buzz, OUTPUT);
}

// 화재 발생 확인 초기값
int fire = 0;

bool fireDetected = false;

void loop()
{
  char incomingChar = '\0';

  if (Serial3.available() > 0)
  {
    int incomingInt = Serial3.read();
    incomingChar = (char)incomingInt;
  }

  // 구간 별 화재 센서
  int room_1 = digitalRead(fire1_1) == LOW || digitalRead(fire1_2) == LOW || digitalRead(fire1_3) == LOW;
  int room_2 = digitalRead(fire2_1) == LOW || digitalRead(fire2_2) == LOW || digitalRead(fire2_3) == LOW || digitalRead(fire2_4) == LOW || digitalRead(fire2_5) == LOW || digitalRead(fire2_6) == LOW;
  int room_3 = digitalRead(fire3_1) == LOW || digitalRead(fire3_2) == LOW || digitalRead(fire3_3) == LOW || digitalRead(fire3_4) == LOW || digitalRead(fire3_5) == LOW || digitalRead(fire3_6) == LOW || digitalRead(fire3_7) == LOW || digitalRead(fire3_8) == LOW || digitalRead(fire3_9) == LOW;

  // 화재 센서
  if (room_1 || room_2 || room_3)
  {
    fireDetected = true;

    if (room_1)
    {
      Serial.println("1번방 화재 감지");
      Serial3.println("101"); // 1번방 화재 감지 코드 전송
    }
    if (room_2)
    {
      Serial.println("2번방 화재 감지");
      Serial3.println("102"); // 2번방 화재 감지 코드 전송
    }
    if (room_3)
    {
      Serial.println("3번방 화재 감지");
      Serial3.println("103"); // 3번방 화재 감지 코드 전송
    }
  }

  // 화재 발생
  if (incomingChar == '8')
  { // 화재 진압 or 센서 값 튀었을때 폰으로 복구

    Serial.println("Door Close");
    myServo.write(90); // 90 close 0 open
    delay(1000);

    // 테스트로 인해 주석처리
    // digitalWrite(window_1_c, HIGH); // 창문을 닫습니다. // 시간 추가할것
    // delay(2000);
    // digitalWrite(window_1_c,LOW);
    // delay(100);
    // digitalWrite(window_2_c,HIGH);
    // delay(2000);
    // digitalWrite(window_2_c, LOW);

    digitalWrite(buzz, LOW);
    fireDetected = false;
  }

  if (fireDetected == false && incomingChar == '16')
  { // 화재 확인
    Serial.println("Door Open");

    digitalWrite(buzz, HIGH);
    myServo.write(0); // 90 close 0 open
    delay(1000);
  }

  if (fireDetected) // 화재 시
  {                 // 테스트로 인해 주석처리
    // digitalWrite(window_1_o, HIGH); // 창문을 엽니다. // 시간 추가할것
    // delay(2000);
    // digitalWrite(window_1_o,LOW);
    // delay(100);
    // digitalWrite(window_2_o,HIGH);
    // delay(2000);
    // digitalWrite(window_2_o, LOW);
  }
}
