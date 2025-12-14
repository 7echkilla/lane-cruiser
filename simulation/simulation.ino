#include "analog_joystick.h"
#include "infrared_proximity_sensor.h"
#include "ultrasonic_sensor.h"
#include "dc_motor.h"
#include <Arduino.h>
#include <Servo.h>

// Analog joystick config
#define HORZ_PIN A0
#define VERT_PIN A1
#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 1023

// IR sensor config
#define IR_R_PIN A2
#define IR_L_PIN A3 
#define IR_THRESHOLD 400

// Ultrasonic sensor config
#define ECHO_PIN 4
#define TRIG_PIN 5

// DC Motor config
#define MOTOR_LF_PIN 12
#define MOTOR_LB_PIN 13
#define MOTOR_RF_PIN 10
#define MOTOR_RB_PIN 9
#define MOTOR_EN_PIN 11

#define SERVO_PIN 3
#define BAUD_RATE 9600

AnalogJoystick analog_joystick(HORZ_PIN, VERT_PIN, JOYSTICK_MIN, JOYSTICK_MAX);
InfraredProximitySensor ir_left(IR_L_PIN, IR_THRESHOLD), ir_right(IR_R_PIN, IR_THRESHOLD);
UltrasonicSensor ultrasonic_sensor(TRIG_PIN, ECHO_PIN);
DCMotor motor_left(MOTOR_LF_PIN, MOTOR_LB_PIN, MOTOR_EN_PIN), motor_right(MOTOR_RF_PIN, MOTOR_RB_PIN, MOTOR_EN_PIN);
Servo servo;

void setup() {
    pinMode(HORZ_PIN, INPUT);
    pinMode(VERT_PIN, INPUT);

    pinMode(IR_L_PIN, INPUT);
    pinMode(IR_R_PIN, INPUT);

    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    
    servo.attach(SERVO_PIN);
    Serial.begin(BAUD_RATE);
}

void loop() {
    int x_value = analog_joystick.get_x_value();
    int y_value = analog_joystick.get_y_value();

    while (x_value or y_value) {
        Serial.print("X: ");
        Serial.print(x_value);
        Serial.print(", Y: ");
        Serial.println(y_value);
    }
}
