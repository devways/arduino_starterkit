const int OUTPUT_RED_LED_1 = 10;
const int OUTPUT_RED_LED_2 = 9;
const int OUTPUT_RED_LED_3 = 6;
const int OUTPUT_GREEN_LED_1 = 5;
const int OUTPUT_GREEN_LED_2 = 3;

const int OUTPUT_RED_LED_ARRAY[3] = { OUTPUT_RED_LED_1, OUTPUT_RED_LED_2, OUTPUT_RED_LED_3 };

int red_led_index = 2;

const int INPUT_SWITCH_1 = 4;
const int INPUT_SWITCH_2 = 2;


bool switch_1_pressed = false;
bool switch_2_pressed = false;
bool switch_1_released = false;
bool switch_2_released = false;

bool switch_1_state = false;
bool switch_2_state = false;
bool switch_1_previous_state = false;
bool switch_2_previous_state = false;

unsigned long previous_timestamp_switch_1 = 0;
unsigned long previous_timestamp_switch_2 = 0;

unsigned long int previous_timestamp = 0;
unsigned long int previous_animation_timestamp = 0;

unsigned short int switch_1_pressed_count = 0;
unsigned short int switch_2_pressed_count = 0;
unsigned short int switch_1_long_pressed_count = 0;
unsigned short int switch_2_long_pressed_count = 0;

char mode[100] = "FROM";

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT_RED_LED_1, OUTPUT);
  pinMode(OUTPUT_RED_LED_2, OUTPUT);
  pinMode(OUTPUT_RED_LED_3, OUTPUT);
  pinMode(OUTPUT_GREEN_LED_1, OUTPUT);
  pinMode(OUTPUT_GREEN_LED_2, OUTPUT);

  pinMode(INPUT_SWITCH_1, INPUT);
  pinMode(INPUT_SWITCH_2, INPUT);
}

void loop() {
  switch_1_state = digitalRead(INPUT_SWITCH_1);
  switch_1_previous_state = switch_1_state;
}

/*
 ******************************
  All function for Left Button
 ******************************
*/

void lightUpFromLeftToRight() {
  int previous_red_led_index = red_led_index;

  // futher this condition move in another function use when the switch 1 is click once
  if (switch_1_state == HIGH && switch_1_previous_state == LOW) {
    if (red_led_index < 2) {
      red_led_index++;
    } else {
      red_led_index = 0;
    }
  }
  
  digitalWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], LOW);
  digitalWrite(OUTPUT_RED_LED_ARRAY[red_led_index], HIGH);
}

void lightUpFromLeftToRightContinuous() {
  unsigned long int current_timestamp = millis();
  if (current_timestamp - previous_timestamp >= 1000) {
    int previous_red_led_index = red_led_index;
    if (red_led_index < 2) {
      red_led_index++;
    } else {
      red_led_index = 0;
    }
    digitalWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], LOW);
    digitalWrite(OUTPUT_RED_LED_ARRAY[red_led_index], HIGH);
    previous_timestamp = current_timestamp;
  }
}

int previous_red_led_index = red_led_index;

void lightUpFromLeftToRightContinuousWithTransition() {
  unsigned long int current_timestamp = millis();

  if (current_timestamp - previous_timestamp >= 1000) {
    digitalWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], LOW);
    previous_red_led_index = red_led_index;
    if (red_led_index < 2) {
      red_led_index++;
    } else {
      red_led_index = 0;
    }
    previous_timestamp = current_timestamp;
  }

  int brightness = (current_timestamp - previous_timestamp) / 4;
  int brightnessAdjusted = brightness < 0 ? 0 : brightness > 250 ? 250 : brightness;

  analogWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], 250 - brightnessAdjusted);
  analogWrite(OUTPUT_RED_LED_ARRAY[red_led_index], brightnessAdjusted);
}

void lightUpLeftGreen() {
  digitalWrite(OUTPUT_GREEN_LED_1, HIGH);
}

void lightUpFromLeftToRightContinuousWithTransitionPlusLeftGreen() {
  lightUpFromLeftToRightContinuousWithTransition();
  digitalWrite(OUTPUT_GREEN_LED_1, HIGH);
}

/*
 ******************************
  All function for Right Button
 ******************************
*/

void lightUpFromRightToLeft() {
  int previous_red_led_index = red_led_index;

  // futher this condition move in another function use when the switch 2 is click once
  if (switch_1_state == HIGH && switch_1_previous_state == LOW) {
    if (red_led_index > 0) {
      red_led_index--;
    } else {
      red_led_index = 2;
    }
  }
  
  digitalWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], LOW);
  digitalWrite(OUTPUT_RED_LED_ARRAY[red_led_index], HIGH);
}

void lightUpFromRightToLeftContinuous() {
  unsigned long int current_timestamp = millis();
  if (current_timestamp - previous_timestamp >= 1000) {
    int previous_red_led_index = red_led_index;
    if (red_led_index > 0) {
      red_led_index--;
    } else {
      red_led_index = 2;
    }
    digitalWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], LOW);
    digitalWrite(OUTPUT_RED_LED_ARRAY[red_led_index], HIGH);
    previous_timestamp = current_timestamp;
  }
}

void lightUpFromRightToLeftContinuousWithTransition() {
  unsigned long int current_timestamp = millis();
  if (current_timestamp - previous_timestamp >= 1000) {
    digitalWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], LOW);
    previous_red_led_index = red_led_index;
    if (red_led_index > 0) {
      red_led_index--;
    } else {
      red_led_index = 2;
    }
    previous_timestamp = current_timestamp;
  }

  int brightness = (current_timestamp - previous_timestamp) / 4;
  int brightnessAdjusted = brightness < 0 ? 0 : brightness > 250 ? 250 : brightness;

  analogWrite(OUTPUT_RED_LED_ARRAY[previous_red_led_index], 250 - brightnessAdjusted);
  analogWrite(OUTPUT_RED_LED_ARRAY[red_led_index], brightnessAdjusted);
}

void lightUpRightGreen() {
  digitalWrite(OUTPUT_GREEN_LED_2, HIGH);
}

void lightUpFromRightToLeftContinuousWithTransitionPlusRightGreen() {
  lightUpFromRightToLeftContinuousWithTransition();
  digitalWrite(OUTPUT_GREEN_LED_2, HIGH);
}

/*
 ******************************
  All function for Simultanuous Left & Right Button
 ******************************
*/

int left_red_led_index = 0;
int right_red_led_index = 2;
int previous_left_red_led_index = left_red_led_index;
int previous_right_red_led_index = right_red_led_index;

void lightUpFromOutsideToInside() {
  previous_left_red_led_index = left_red_led_index;
  previous_right_red_led_index = right_red_led_index;

    // futher this condition move in another function use when the switch 1 & 2 is click simultanuous once 
  if (switch_1_state == HIGH && switch_1_previous_state == LOW) {
    int array_length = sizeof(OUTPUT_RED_LED_ARRAY) / sizeof(OUTPUT_RED_LED_ARRAY[0]);
    if (left_red_led_index < (array_length / 2)) {
      left_red_led_index++;
      right_red_led_index--;
    } else {
      left_red_led_index = 0;
      right_red_led_index = array_length - 1;
    }
  }

  digitalWrite(OUTPUT_RED_LED_ARRAY[previous_left_red_led_index], LOW);
  digitalWrite(OUTPUT_RED_LED_ARRAY[previous_right_red_led_index], LOW);
  digitalWrite(OUTPUT_RED_LED_ARRAY[left_red_led_index], HIGH);
  digitalWrite(OUTPUT_RED_LED_ARRAY[right_red_led_index], HIGH);
  
}

void lightUpFromOutsideToInsideContinuous() {
  unsigned long int current_timestamp = millis();
  if (current_timestamp - previous_timestamp >= 1000) {
    previous_left_red_led_index = left_red_led_index;
    previous_right_red_led_index = right_red_led_index;

    int array_length = sizeof(OUTPUT_RED_LED_ARRAY) / sizeof(OUTPUT_RED_LED_ARRAY[0]);
    if (left_red_led_index < (array_length / 2)) {
      left_red_led_index++;
      right_red_led_index--;
    } else {
      left_red_led_index = 0;
      right_red_led_index = array_length - 1;
    }

    digitalWrite(OUTPUT_RED_LED_ARRAY[previous_left_red_led_index], LOW);
    digitalWrite(OUTPUT_RED_LED_ARRAY[previous_right_red_led_index], LOW);
    digitalWrite(OUTPUT_RED_LED_ARRAY[left_red_led_index], HIGH);
    digitalWrite(OUTPUT_RED_LED_ARRAY[right_red_led_index], HIGH);
    previous_timestamp = current_timestamp;
  }
}

void lightUpFromOutsideToInsideContinuousTransition() {
  unsigned long int current_timestamp = millis();
  if (current_timestamp - previous_timestamp >= 1000) {
    analogWrite(OUTPUT_RED_LED_ARRAY[previous_left_red_led_index], 0);
    analogWrite(OUTPUT_RED_LED_ARRAY[previous_right_red_led_index], 0);

    previous_left_red_led_index = left_red_led_index;
    previous_right_red_led_index = right_red_led_index;

    int array_length = sizeof(OUTPUT_RED_LED_ARRAY) / sizeof(OUTPUT_RED_LED_ARRAY[0]);
    if (left_red_led_index < (array_length / 2)) {
      left_red_led_index++;
      right_red_led_index--;
    } else {
      left_red_led_index = 0;
      right_red_led_index = array_length - 1;
    }
    previous_timestamp = current_timestamp;
  }

  int brightness = (current_timestamp - previous_timestamp) / 4;
  int brightnessAdjusted = brightness < 0 ? 0 : brightness > 250 ? 250 : brightness;

  analogWrite(OUTPUT_RED_LED_ARRAY[previous_left_red_led_index], 250 - brightnessAdjusted);
  analogWrite(OUTPUT_RED_LED_ARRAY[previous_right_red_led_index], 250 - brightnessAdjusted);
  analogWrite(OUTPUT_RED_LED_ARRAY[left_red_led_index], brightnessAdjusted);
  analogWrite(OUTPUT_RED_LED_ARRAY[right_red_led_index], brightnessAdjusted);
}

void lightRedPlusGreen() {
  int array_length = sizeof(OUTPUT_RED_LED_ARRAY) / sizeof(OUTPUT_RED_LED_ARRAY[0]);
  for(int i = 0; i < array_length; i++) {
    digitalWrite(OUTPUT_RED_LED_ARRAY[i], HIGH);
  }

  digitalWrite(OUTPUT_GREEN_LED_1, HIGH);
  digitalWrite(OUTPUT_GREEN_LED_2, HIGH);
}

bool brightnessIncrease = true;

void lightRedContinuousTransitionPlusGreen() {
  unsigned long int current_timestamp = millis();
  if (current_timestamp - previous_timestamp >= 1000) {
    brightnessIncrease = !brightnessIncrease;
    previous_timestamp = current_timestamp;
  }

  int brightness = (current_timestamp - previous_timestamp) / 4;
  int brightnessAdjusted = brightness < 0 ? 0 : brightness > 250 ? 250 : brightness;
  int brightnessUsed = brightnessIncrease ? brightnessAdjusted : 250 - brightnessAdjusted;

  int array_length = sizeof(OUTPUT_RED_LED_ARRAY) / sizeof(OUTPUT_RED_LED_ARRAY[0]);
  for(int i = 0; i < array_length; i++) {
    analogWrite(OUTPUT_RED_LED_ARRAY[i], brightnessUsed);
  }

  digitalWrite(OUTPUT_GREEN_LED_1, HIGH);
  digitalWrite(OUTPUT_GREEN_LED_2, HIGH);
}