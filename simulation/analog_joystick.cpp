#include "analog_joystick.h"
#include <Arduino.h>

AnalogJoystick::AnalogJoystick(int x_pin, int y_pin, int min_input, int max_input)
    : _x_pin(x_pin), _y_pin(y_pin), _min_input(min_input), _max_input(max_input) {
}

int AnalogJoystick::get_x_value() {
    int x_value = map(analogRead(_x_pin), _min_input, _max_input, _min_output, _max_output);
    return x_value;
}

int AnalogJoystick::get_y_value() {
    int y_value = map(analogRead(_y_pin), _min_input, _max_input, _min_output, _max_output);
    return y_value;
}