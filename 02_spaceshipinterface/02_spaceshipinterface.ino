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

unsigned long previous_detection_end_timestamp = 0;

unsigned long int previous_timestamp = 0;
unsigned long int previous_animation_timestamp = 0;

bool switch_detection_end = false;
int switch_1_short_press_count = 0;
int switch_2_short_press_count = 0;
int switch_1_long_press_count = 0;
int switch_2_long_press_count = 0;
bool switch_1_previous_type_of_press_is_short = true;
bool switch_2_previous_type_of_press_is_short = true;
bool switch_1_long_activated = false;
bool switch_2_long_activated = false;

int mode = 0;

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
  switch_2_state = digitalRead(INPUT_SWITCH_2);

  // switch_1_detection();
  switch_detection(
    &switch_1_state,
    &switch_1_previous_state,
    &switch_1_pressed,
    &switch_1_released,
    &switch_1_long_activated, 
    &switch_1_short_press_count,
    &switch_1_long_press_count,
    &previous_timestamp_switch_1,
    &switch_1_previous_type_of_press_is_short
  );

  switch_detection(
    &switch_2_state,
    &switch_2_previous_state,
    &switch_2_pressed,
    &switch_2_released,
    &switch_2_long_activated, 
    &switch_2_short_press_count,
    &switch_2_long_press_count,
    &previous_timestamp_switch_2,
    &switch_2_previous_type_of_press_is_short
  );

  switch_actions();

  switch (mode)
  {
    case 1:
      lightUpFromOutsideToInside();
      break;
    case 2:
      lightUpFromOutsideToInsideContinuousTransition();
      break;
    case 3:
      lightUpFromOutsideToInsideContinuous();
      break;
    case 4:
      lightRedContinuousTransitionPlusGreen();
      break;
    case 5:
      lightRedPlusGreen();
      break;
    case 6:
      lightUpFromLeftToRight();
      break;
    case 7:
      lightUpFromLeftToRightContinuousWithTransition();
      break;
    case 8:
      lightUpFromLeftToRightContinuous();
      break;
    case 9:
      lightUpFromLeftToRightContinuousWithTransitionPlusLeftGreen();
      break;
    case 10:
      lightUpLeftGreen();
      break;
    case 11:
      lightUpFromRightToLeft();
      break;
    case 12:
      lightUpFromRightToLeftContinuousWithTransition();
      break;
    case 13:
      lightUpFromRightToLeftContinuous();
      break;
    case 14:
      lightUpFromRightToLeftContinuousWithTransitionPlusRightGreen();
      break;
    case 15:
      lightUpRightGreen();
      break;
  default:
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    break;
  }

  switch_1_previous_state = switch_1_state;
  switch_2_previous_state = switch_2_state;
}

/*
 ******************************
  All function for Left Button
 ******************************
*/

void actionLightUpFromLeftToRight() {
  if (red_led_index < 2) {
    red_led_index++;
  } else {
    red_led_index = 0;
  }
}

void lightUpFromLeftToRight() {
  int previous_red_led_index = red_led_index;
  
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

void actionLightUpFromRightToLeft() {
  if (red_led_index > 0) {
    red_led_index--;
  } else {
    red_led_index = 2;
  }
}

void lightUpFromRightToLeft() {
  int previous_red_led_index = red_led_index;
  
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

void actionLightUpFromOutsideToInside() {
  int array_length = sizeof(OUTPUT_RED_LED_ARRAY) / sizeof(OUTPUT_RED_LED_ARRAY[0]);
  if (left_red_led_index < (array_length / 2)) {
    left_red_led_index++;
    right_red_led_index--;
  } else {
    left_red_led_index = 0;
    right_red_led_index = array_length - 1;
  }
}

void lightUpFromOutsideToInside() {
  previous_left_red_led_index = left_red_led_index;
  previous_right_red_led_index = right_red_led_index;

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

void resetLightUp() {
  int array_length = sizeof(OUTPUT_RED_LED_ARRAY) / sizeof(OUTPUT_RED_LED_ARRAY[0]);
  for(int i = 0; i < array_length; i++) {
    digitalWrite(OUTPUT_RED_LED_ARRAY[i], LOW);
  }
  digitalWrite(OUTPUT_GREEN_LED_1, LOW);
  digitalWrite(OUTPUT_GREEN_LED_2, LOW);
}

void switch_detection(
  bool *switch_state,
  bool *switch_previous_state,
  bool *switch_pressed,
  bool *switch_release,
  bool *switch_long_activated,
  int *switch_short_press_count,
  int *switch_long_press_count,
  unsigned long *previous_timestamp_switch,
  bool *switch_previous_type_of_press_is_short
  ) {
  unsigned long int current_timestamp_switch = millis();

  // switch 1 is pressed
  if (*switch_state == true && *switch_previous_state == false) {
    switch_detection_end = false;
    *previous_timestamp_switch = current_timestamp_switch;
    *switch_pressed = true;
    *switch_release = false;
  }

  // switch 1 is release
  if (*switch_state == false && *switch_previous_state == true) {
    if (*switch_previous_type_of_press_is_short && *switch_short_press_count < 2) {
      (*switch_short_press_count)++;
    } else if (!*switch_previous_type_of_press_is_short && *switch_long_activated && *switch_long_press_count < 2) {
      *switch_long_activated = false;
      (*switch_long_press_count)++;

    }
    *switch_pressed = false;
    *switch_release = true;
    *previous_timestamp_switch = current_timestamp_switch;
  }

  // switch 1 is currently pressed for more than 1000ms
  if (*switch_state == true && (current_timestamp_switch - *previous_timestamp_switch >= 1000)) {
    // prevent use of short press after long press
    *switch_previous_type_of_press_is_short = false;
    // prevent a short press after long detected as long press
    *switch_long_activated = true;
  }

  // switch 1 has been released and 300ms has been passed since release
  // theorically the sequence of input is end
  if (*switch_release == true && (current_timestamp_switch - *previous_timestamp_switch >= 300)) {
    switch_detection_end = true;
    *switch_release = false;
    previous_detection_end_timestamp = current_timestamp_switch;
  }
}

void switch_actions() {
  unsigned long int current_detection_end_timestamp = millis();

  if (switch_detection_end && (current_detection_end_timestamp - previous_detection_end_timestamp >= 300)) {
    resetLightUp();

    if (switch_1_short_press_count == 1 && switch_2_short_press_count == 1) {
      actionLightUpFromOutsideToInside();
      mode = 1;
    } else if (switch_1_short_press_count == 2 && switch_2_short_press_count == 2 && switch_1_long_press_count == 1 && switch_2_long_press_count == 1) {
      mode = 2;
    } else if (switch_1_short_press_count == 2 && switch_2_short_press_count == 2) {
      mode = 3;
    } else if (switch_1_long_press_count == 1 && switch_2_long_press_count == 1) {
      mode = 4;
    } else if (switch_1_long_press_count == 2 && switch_2_long_press_count == 2) {
      mode = 5;
    } else if (switch_1_short_press_count == 1) {
      actionLightUpFromLeftToRight();
      mode = 6;
    } else if (switch_1_short_press_count == 2 && switch_1_long_press_count == 1) {
      mode = 7;
    } else if (switch_1_short_press_count == 2) {
      mode = 8;
    } else if (switch_1_long_press_count == 1) {
      mode = 9;
    } else if (switch_1_long_press_count == 2) {
      mode = 10;
    } else if (switch_2_short_press_count == 1) {
      actionLightUpFromRightToLeft();
      mode = 11;
    } else if (switch_2_short_press_count == 2 && switch_2_long_press_count == 1) {
      mode = 12;
    } else if (switch_2_short_press_count == 2) {
      mode = 13;
    } else if (switch_2_long_press_count == 1) {
      mode = 14;
    } else if (switch_2_long_press_count == 2) {
      mode = 15;
    }
    
    switch_1_short_press_count = 0;
    switch_1_long_press_count = 0;
    switch_1_long_activated = false;
    switch_1_previous_type_of_press_is_short = true;

    switch_2_short_press_count = 0;
    switch_2_long_press_count = 0;
    switch_2_long_activated = false;
    switch_2_previous_type_of_press_is_short = true;

    switch_detection_end = false;
  }
}