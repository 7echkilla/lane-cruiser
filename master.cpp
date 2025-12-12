// // master

#include <Servo.h>

#define BAUD_RATE 9600
#define X_PIN A0
#define Y_PIN A1
#define SELECT_PIN 2
#define SERVO_PIN 3
#define MOTOR_LF 12
#define MOTOR_LB 13
#define MOTOR_PWR 11
#define TRIG_PIN 5
#define ECHO_PIN 4
#define IR_L A3
#define IR_R A2

// #define SPEED
#define THRESHOLD 512

int angle;
char direction[12];
Servo steering;

void setup() {
    pinMode(X_PIN, INPUT);
    pinMode(Y_PIN, INPUT);
    pinMode(SELECT_PIN, INPUT);

    steering.attach(SERVO_PIN);

    pinMode(MOTOR_LF, OUTPUT);
    pinMode(MOTOR_LB, OUTPUT);
    pinMode(MOTOR_PWR, OUTPUT);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(IR_L, INPUT);
    pinMode(IR_R, INPUT);

    Serial.begin(BAUD_RATE);
}

// void loop() {
//     int x_in = analogRead(X_PIN);
//     int y_in = analogRead(Y_PIN);
//     int brake = digitalRead(SELECT_PIN);

//     sprintf(direction, "%d,%d,%d\n", x_in, y_in, brake);
//     Serial.print(direction);
    
//     int angle = map(x_in, 0, 1023, 0, 180);
//     steering.write(angle);

//     digitalWrite(MOTOR_LF, HIGH);
//     digitalWrite(MOTOR_LB, LOW);
//     analogWrite(MOTOR_PWR, 10); // 0 -> stop, 255 -> max

//     delay(1000);
// }

// void loop() {
//     // Send a 10 microsecond pulse to trigger the sensor
//     digitalWrite(TRIG_PIN, LOW);  // Make sure the trigger is off
//     delayMicroseconds(2);       
//     digitalWrite(TRIG_PIN, HIGH); // Send pulse
//     delayMicroseconds(10);       
//     digitalWrite(TRIG_PIN, LOW);  // Stop the pulse

//     // Read the duration of the pulse from Echo pin
//     long duration = pulseIn(ECHO_PIN, HIGH);

//     // Calculate the distance (duration in microseconds to centimeters)
//     // Speed of sound is 343 m/s or 0.0343 cm/us
//     int distance = duration * 0.0343 / 2;

//     Serial.print("Distance: ");
//     Serial.print(distance);
//     Serial.println(" cm");

//     delay(500);
// }

void loop() {
    int ir_left_value = analogRead(IR_L);
    int ir_left = (ir_left_value < THRESHOLD) ? 1 : 0;
    int ir_right_value = analogRead(IR_R);
    int ir_right = (ir_right_value < THRESHOLD) ? 1 : 0;

    Serial.print("left: ");
    Serial.print(ir_left);
    Serial.print(", right: ");
    Serial.println(ir_right);

    delay(500);
}