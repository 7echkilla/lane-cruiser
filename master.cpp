#include <Servo.h>
#define BAUD_RATE 9600

Servo steer;
int xIn, yIn, sel, ang;
char direction[12];

void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(2, INPUT);
    steer.attach(3);

    Serial.begin(BAUD_RATE);
}

void loop() {
    xIn = analogRead(A0);
    yIn = analogRead(A1);
    sel = digitalRead(2);

    sprintf(direction, "%d,%d,%d\n", xIn, yIn, sel);
    Serial.print(direction);
    
    ang = map(xIn, 0, 1023, 0, 180);
    steer.write(ang);

    delay(200);
}