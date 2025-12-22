#include "analog_joystick.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

// Analog joystick config
#define HORZ_PIN A0
#define VERT_PIN A1
#define SEL_PIN 2
#define JOYSTICK_MIN 0      // Default min analog value
#define JOYSTICK_MAX 1023   // Default max analog value
#define DEADZONE 0.12       // Anticipated joystick deadzone [0.0-1.0]

// Bluetooth config
#define RX_PIN 7
#define TX_PIN 8

#define BAUD_RATE 9600

AnalogJoystick analog_joystick(HORZ_PIN, VERT_PIN, SEL_PIN, JOYSTICK_MAX);
SoftwareSerial master_bluetooth(RX_PIN, TX_PIN);

void setup() {
    Serial.begin(BAUD_RATE);
    master_bluetooth.begin(BAUD_RATE);
    delay(1000);    // Wait for bluetooth module to initialise
}

void manual_control() {
    float x_value = analog_joystick.get_x_value();
    float y_value = analog_joystick.get_y_value();    
    int angle = SERVO_MAX / 2;

    // Tank-like movement for spin
    if (fabs(y_value) < DEADZONE) {
        // Steering angle: 0 (left) or 180 (right)
        if (x_value > 0) {
            servo.write(SERVO_MAX);
        } else if (x_value < 0) {
            servo.write(SERVO_MIN);
        } 

        motor_left.drive_motor(x_value);
        motor_right.drive_motor(-x_value);
    } else {
        // Car-like behaviour (forward/backward + steering)
        angle = constrain(round((x_value + 1) * (SERVO_MAX / 2)), SERVO_MIN, SERVO_MAX);
        servo.write(angle);

        // Calculated left/right motor values based on car-behaviour
        float left_value = constrain(y_value + x_value * fabs(y_value), -1.0, 1.0);
        float right_value = constrain(y_value - x_value * fabs(y_value), -1.0, 1.0);

        // Reversed values for backward-diagonal motions
        if (y_value < 0) {
            float temp = left_value;
            left_value = right_value;
            right_value = temp;
        }

        motor_left.drive_motor(left_value);
        motor_right.drive_motor(right_value);
    }
}

int control_mode = 0;
int last_sel_value = HIGH;

void loop() {
    int sel_value = analog_joystick.get_sel_value();
    
    if (sel_value == LOW && last_sel_value == HIGH) {
        // Toggle mode on falling edge joystick selector
        control_mode = !control_mode;
        if (control_mode == LOW) {
            Serial.println("[INFO] Automatic mode");
            master_bluetooth.println("0");
        } else if (control_mode == HIGH) {
            Serial.println("[INFO] Manual mode");
            master_bluetooth.println("1");
        } else {
            Serial.println("[WARN] Undefined mode");
        }
    }

    last_sel_value = sel_value;

    // Ensure state unless toggled
    if (control_mode == LOW) {
        automatic_control();
    } else if (control_mode == HIGH) {
        manual_control();
    }

    delay(100);    
}