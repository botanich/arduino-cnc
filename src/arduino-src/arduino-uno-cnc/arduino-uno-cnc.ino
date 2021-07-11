#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int push_button[4] = {0, 1, 10, 13};
int light_diods[3] = {6, 7, 8};
int button_state[4];
bool gotta_stop = false;
bool gotta_start1 = true, gotta_start2 = true;

void dynamic_stop() {
    gotta_stop = false;
    gotta_start1 = true;
    gotta_start2 = true;
    digitalWrite(light_diods[0], LOW);
    digitalWrite(light_diods[1], LOW);
    delay(200);
    digitalWrite(light_diods[2], HIGH);
    lcd.clear();
    lcd.print("Dynamic stop");
    delay(2000);
    digitalWrite(light_diods[2], LOW);
    lcd.clear();
    lcd.print("Stopped");
}

void start_bending() {
    gotta_stop = true;
    gotta_start1 = false;
    digitalWrite(light_diods[0], HIGH);
    lcd.clear();
    lcd.print("Bending");
}

void start_reverse() {
    gotta_stop = true;
    gotta_start2 = false;
    digitalWrite(light_diods[1], HIGH);
    lcd.clear();
    lcd.print("Reverse");
}


void setup() {
  Serial.begin(9600);
  lcd.begin(0, 1);
  for (int i = 0; i < 4; i++) {
    pinMode(push_button[i], INPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(light_diods[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    button_state[i] = digitalRead(push_button[i]);
  }
  
  if (button_state[0] == LOW && button_state[1] == HIGH) {
      if (gotta_start1) {
        start_bending();
      }
  } else if (button_state[2] == LOW && button_state[3] == HIGH) {
      if (gotta_start2) {
        start_reverse();
      }
  } else if (button_state[0] == HIGH && button_state[1] == HIGH ||
      button_state[0] == HIGH && button_state[1] == LOW ||
      button_state[0] == LOW && button_state[1] == LOW) {
        if (gotta_stop) {
          dynamic_stop();
        }
  } else if (button_state[2] == HIGH && button_state[3] == HIGH ||
      button_state[2] == HIGH && button_state[3] == LOW ||
      button_state[2] == LOW && button_state[3] == LOW) {
        if (gotta_stop) {
          dynamic_stop();
        }
  }
  delay(1);        // delay in between reads for stability
}
