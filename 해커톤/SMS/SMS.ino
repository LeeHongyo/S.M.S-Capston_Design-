#include <FastLED.h>
#include <NewPing.h>

#define TRIG_LEFT 3
#define ECHO_LEFT 2
#define TRIG_RIGHT 5
#define ECHO_RIGHT 4

#define LED_RIGHT 6
#define NUM_LEDS1 5
#define LED_LEFT 7
#define NUM_LEDS2 5

CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];

NewPing sonarLeft(TRIG_LEFT, ECHO_LEFT, 200);  // 왼쪽 소나
NewPing sonarRight(TRIG_RIGHT, ECHO_RIGHT, 200); // 오른쪽 소나

void setup() {
  FastLED.addLeds<WS2812, LED_RIGHT, GRB>(leds1, NUM_LEDS1);
  FastLED.addLeds<WS2812, LED_LEFT, GRB>(leds2, NUM_LEDS2);

  Serial.begin(9600);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  digitalWrite(LED_RIGHT, LOW);

  // 모든 LED 끄기
  turnOffLEDs();
}

void loop() {
  int leftDistance = sonarLeft.ping_cm();   // 왼쪽 센서로부터 거리 측정
  int rightDistance = sonarRight.ping_cm(); // 오른쪽 센서로부터 거리 측정
  Serial.println(leftDistance);
  Serial.println(rightDistance);
  if (leftDistance < 10 && rightDistance < 10) {
    // 왼쪽과 오른쪽 모두에 물체가 가까이 있을 경우
    turnOnBothLEDs();
  } else if (leftDistance < 10) {
    // 왼쪽에 물체가 가까이 있을 경우
    turnOnLeftLEDs();
  } else if (rightDistance < 10) {
    // 오른쪽에 물체가 가까이 있을 경우
    turnOnRightLEDs();
  } else {
    // 물체가 가까이 있지 않을 경우
    turnOffLEDs();
  }
  delay(100); // 측정 주기를 조절할 수 있습니다.
}

void turnOffLEDs() {
  turnOffLeftLEDs();
  turnOffRightLEDs();
}

void turnOnLeftLEDs() {
  // 왼쪽 LED를 빨간색으로 설정
  for (int i = 0; i < NUM_LEDS1; i++) {
    leds1[i] = CRGB(255, 0, 0);  // 빨간색 (R: 255, G: 0, B: 0)
  }

  // 오른쪽 LED는 꺼진 상태로 유지
  for (int i = 0; i < NUM_LEDS2; i++) {
    leds2[i] = CRGB(0, 0, 0);  // 꺼진 상태 (검정색)
  }

  FastLED.show();  // LED 상태 업데이트
}

void turnOffLeftLEDs() {
  // 왼쪽 LED를 끄는 코드를 추가합니다.
  for (int i = 0; i < NUM_LEDS1; i++) {
    leds1[i] = CRGB(0, 0, 0);  // 왼쪽 LED를 꺼진 상태로 설정합니다. (검정색)
  }
  FastLED.show();  // LED 상태 업데이트
}

void turnOnRightLEDs() {
  // 오른쪽 LED를 빨간색으로 켜는 코드를 추가합니다.
  for (int i = 0; i < NUM_LEDS2; i++) {
    leds2[i] = CRGB(255, 0, 0);  // 빨간색으로 설정합니다.
  }
  FastLED.show();  // LED 상태 업데이트
}

void turnOffRightLEDs() {
  // 오른쪽 LED를 끄는 코드를 추가합니다.
  for (int i = 0; i < NUM_LEDS2; i++) {
    leds2[i] = CRGB(0, 0, 0);  // 오른쪽 LED를 꺼진 상태로 설정합니다. (검정색)
  }
  FastLED.show();  // LED 상태 업데이트
}

void turnOnBothLEDs() {
  // 왼쪽과 오른쪽 LED를 모두 빨간색으로 켜는 코드를 추가합니다.
  for (int i = 0; i < NUM_LEDS1; i++) {
    leds1[i] = CRGB(255, 0, 0);  // 왼쪽 LED를 빨간색으로 설정합니다.
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    leds2[i] = CRGB(255, 0, 0);  // 오른쪽 LED를 빨간색으로 설정합니다.
  }
  FastLED.show();  // LED 상태 업데이트
}