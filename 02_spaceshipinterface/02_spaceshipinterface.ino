/*
  Arduino Starter Kit example
  Project 2 - Spaceship Interface

  This sketch is written to accompany Project 2 in the Arduino Starter Kit

  Parts required:
  - one green LED
  - two red LEDs
  - pushbutton
  - 10 kilohm resistor
  - three 220 ohm resistors

  created 13 Sep 2012
  by Scott Fitzgerald

  http://www.arduino.cc/starterKit

  This example code is part of the public domain.
*/

int switchState = 0;
int previousSwitchState = 0;
bool blinkState = false;
bool mode = false;
unsigned long previousMillis = 0;

bool buttonIsPressed() {
  if (switchState == true && previousSwitchState == false) {
    return true;
  }
  return false;
}

void changeMode() {
  mode = !mode;
}

void setup() {
  pinMode(2, INPUT);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  switchState = digitalRead(2);

  if (buttonIsPressed()) changeMode();

  if (!mode) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 250) {
       previousMillis = currentMillis;
       blinkState = !blinkState;
    }
    digitalWrite(3, LOW);
    digitalWrite(5, blinkState);
    digitalWrite(4, !blinkState);
  }

  if (previousSwitchState == switchState) return;
  previousSwitchState = switchState;
}
