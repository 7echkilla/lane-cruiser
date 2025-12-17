#include "analog_joystick.h"
#include <Arduino.h>

AnalogJoystick::AnalogJoystick(int x_pin, int y_pin, int sel_pin, int min_input, int max_input)
    : _x_pin(x_pin), _y_pin(y_pin), _sel_pin(sel_pin), _min_input(min_input), _max_input(max_input) {
}

// Convert 0/1023 analog input to -1/1
float AnalogJoystick::get_x_value() {
    float x_value = (analogRead(_x_pin) - (_max_input / 2)) / (_max_input / 2);
    return x_value;
}

float AnalogJoystick::get_y_value() {
    float y_value = (analogRead(_y_pin) - (_max_input / 2)) / (_max_input / 2);
    return y_value;
}

int AnalogJoystick::get_sel_value() {
    return digitalRead(_sel_pin);
}