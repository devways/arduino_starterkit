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

bool switchRelease = false;
bool switchPressed = false;

int switchState = 0;
int previousSwitchState = 0;
bool blinkState = false;
unsigned long previousBlinkMillis = 0;
unsigned long previousMillis = 0;
unsigned short int clickNumber = 0;
unsigned short int mode = 0;


bool buttonIsPressed() {
  if (switchState == true && previousSwitchState == false) {
    return true;
  }
  return false;
}

bool buttonIsRelease() {
  if (switchState == false && previousSwitchState == true) {
    return true;
  }
  return false;
}

void chooseMode() {
  unsigned long currentMillis = millis();

  if (buttonIsPressed()) {
    Serial.println("print 1");
    // Serial.println(mode);
    if (clickNumber < 2) {
      clickNumber = clickNumber + 1;
      previousMillis = currentMillis;
    }
    switchPressed = true;
    return;
  }
  
  if (switchPressed && buttonIsRelease()) {
    Serial.println("print 2");
    switchPressed = false;
    if (currentMillis - previousMillis >= 300) {
      previousMillis = currentMillis;
      mode = clickNumber;
      clickNumber = 0;
      switchRelease = false;
      return;
    }
    switchRelease = true;
    return;
  }

  if (switchState == true && (currentMillis - previousMillis >= 1000)) {
    // defineMode Long
    Serial.println("print 3");

    previousMillis = currentMillis;
    mode = 3;
    clickNumber = 0;
    switchPressed = false;
    return;
  }

  if (switchRelease && (currentMillis - previousMillis >= 300)) {
    // definemode short (clickNumber)
    Serial.println("print 4");

    previousMillis = currentMillis;
    mode = clickNumber;
    clickNumber = 0;
    switchRelease = false;
    return;
  }
};

void changeMode() {
  // mode = !mode;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  switchState = digitalRead(2);

  chooseMode();

  Serial.print("switchState: ");
  Serial.print(switchState);
  Serial.print(", previousSwitchState: ");
  Serial.print(previousSwitchState);
  Serial.print(", mode: ");
  Serial.println(mode);

  if (buttonIsPressed()) changeMode();

  // if (!mode) {
  //   digitalWrite(3, HIGH);
  //   digitalWrite(5, LOW);
  //   digitalWrite(6, LOW);
  // } else {
  //   unsigned long currentBlinkMillis = millis();
  //   if (currentBlinkMillis - previousBlinkMillis >= 250) {
  //      previousBlinkMillis = currentBlinkMillis;
  //      blinkState = !blinkState;
  //   }
  //   digitalWrite(3, LOW);
  //   digitalWrite(6, blinkState);
  //   digitalWrite(5, !blinkState);
  // }

  switch (mode)
  {
    case 1:
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      break;
    case 2:
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      break;
    case 3:
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      break;
  default:
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    break;
  }

  if (previousSwitchState == switchState) return;
  previousSwitchState = switchState;
}
