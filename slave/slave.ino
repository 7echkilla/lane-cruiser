#include "infrared_proximity_sensor.h"
#include "ultrasonic_sensor.h"
#include "dc_motor.h"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Servo.h>

// IR sensor config
#define IR_R_PIN A2
#define IR_L_PIN A3 
#define IR_THRESHOLD 600    // Positive detection above this value [0-1023]

// Ultrasonic sensor config
#define ECHO_PIN 4
#define TRIG_PIN 5
#define MIN_DISTANCE 10     // Distance for obstacle detection

// DC Motor config
#define MOTOR_LF_PIN 12
#define MOTOR_LB_PIN 13
#define MOTOR_RF_PIN 10
#define MOTOR_RB_PIN 9
#define MOTOR_EN_PIN 11
#define MIN_SPEED 30.0      // Min PWM signal to register motion 
#define MAX_SPEED 250.0     // Max allowable PWM signal

// Servo config
#define SERVO_PIN 3
#define SERVO_MIN 0         // Default min servo range
#define SERVO_MAX 180       // Default max servo range

// Bluetooth config
#define RX_PIN 7
#define TX_PIN 8

#define BAUD_RATE 9600

InfraredProximitySensor ir_left(IR_L_PIN, IR_THRESHOLD), ir_right(IR_R_PIN, IR_THRESHOLD);
UltrasonicSensor ultrasonic_sensor(TRIG_PIN, ECHO_PIN);
DCMotor motor_left(MOTOR_LF_PIN, MOTOR_LB_PIN, MOTOR_EN_PIN, MIN_SPEED, MAX_SPEED);
DCMotor motor_right(MOTOR_RF_PIN, MOTOR_RB_PIN, MOTOR_EN_PIN, MIN_SPEED, MAX_SPEED);
SoftwareSerial slave_bluetooth(RX_PIN, TX_PIN);
Servo servo;

void setup() {
    Servo.attach(SERVO_PIN)
    Serial.begin(BAUD_RATE);
    slave_bluetooth.begin(BAUD_RATE);
    delay(1000);    // Wait for bluetooth module to initialise
}

void automatic_control() {
    int obstacle_distance = ultrasonic_sensor.get_distance();
    bool is_left_white = ir_left.is_white();
    bool is_right_white = ir_right.is_white();
    float drive_value = 0.5;

    // Drive logic
    if (obstacle_distance < MIN_DISTANCE) {
        servo.write(SERVO_MAX / 2);
        motor_left.drive_motor(0.0);
        motor_right.drive_motor(0.0);
    } else {
        if (is_left_white && is_right_white) {
            servo.write(SERVO_MAX / 2);
            motor_left.drive_motor(drive_value);
            motor_right.drive_motor(drive_value);
        } else if (is_left_white && !is_right_white) {
            servo.write(SERVO_MIN);
            motor_left.drive_motor(-drive_value);
            motor_right.drive_motor(drive_value);
        } else if (!is_left_white && is_right_white) {
            servo.write(SERVO_MAX);
            motor_left.drive_motor(drive_value);
            motor_right.drive_motor(-drive_value);
        } else {
            servo.write(SERVO_MAX / 2);
            motor_left.drive_motor(0.0);
            motor_right.drive_motor(0.0);
        }
    }
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

void loop() {
  // Check if data is available from the master
  if (BTSerial.available()) {
    String receivedData = BTSerial.readString(); // Read the incoming data
    Serial.println("Received: " + receivedData);  // Print received data to Serial Monitor
  }
}
