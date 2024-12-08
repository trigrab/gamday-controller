#include <main.h>

BleGamepad bleGamepad("Gameday Controller", "Fachschaft TF", 100);

void setup() {
    Serial.begin(9600);
  // initialize joystick pins
  for (int i = 0; i < 4; i++) {
    pinMode(joystick_pins[i], INPUT_PULLDOWN);
  }

  // initialize button pins
  for (int i = 0; i < 2; i++) {
    pinMode(button_pins[i], INPUT_PULLDOWN);
  } 
  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setWhichAxes(0, 0, 0, 0, 0, 0, 0, 0);
  bleGamepadConfig.setButtonCount(16);
  bleGamepadConfig.setHatSwitchCount(2);
  // initialize bleGampead
  bleGamepad.begin(&bleGamepadConfig);
  

  Serial.println("Initialized");
}

void loop() {
  if (bleGamepad.isConnected()) {
    updateButtons();
    updateAxis();
    delay(100);
  }
}

void updateButtons() {
  for (int button = 0; button < 2; button++) {
    int input =  digitalRead(button_pins[button]);
    if (input == HIGH) {
      bleGamepad.press(button_mapping[button]);
    }
    else {
      bleGamepad.release(button_mapping[button]);
    }
  }
}

void updateAxis() {
  byte direction = 0;
  if (digitalRead(joystick_pins[0]) == HIGH) {
    direction |= (1 << 0);  // LEFT bit
  }
  if (digitalRead(joystick_pins[1]) == HIGH) {
    direction |= (1 << 1);  // RIGHT bit
  }
  if (digitalRead(joystick_pins[2]) == HIGH) {
    direction |= (1 << 2);  // UP bit
  }
  if (digitalRead(joystick_pins[3]) == HIGH) {
    direction |= (1 << 3);  // DOWN bit
  }

  bleGamepad.setHats(getDirection(direction), getDirection(direction));
}

byte getDirection(byte direction) {
  switch (direction) {
        case 0b0000: return DPAD_CENTERED;
        case 0b0001: return DPAD_LEFT;
        case 0b0010: return DPAD_RIGHT;
        case 0b0100: return DPAD_UP;
        case 0b0101: return DPAD_UP_LEFT;
        case 0b0110: return DPAD_UP_RIGHT;
        case 0b1000: return DPAD_DOWN;
        case 0b1001: return DPAD_DOWN_LEFT;
        case 0b1010: return DPAD_DOWN_RIGHT;
        default: return DPAD_CENTERED;
    }
}