#include <Arduino.h>
#include <BleGamepad.h>
const int joystick_pins[] = {12, 14, 27, 26};
const byte joystick_mapping[] = {DPAD_LEFT, DPAD_RIGHT, DPAD_UP, DPAD_DOWN};
const int button_pins[] = {13, 25};
const int button_mapping[] = {BUTTON_1, BUTTON_2};

void setup();

void loop();

void updateButtons();
void updateAxis(); 
byte getDirection(byte direction);