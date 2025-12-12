#include "stdio.h"

int TRIG = 10;
int ECHO = 11;
#define ENL 5
#define ENR 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 4

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

int d_counter() {

    int distance;
    long time;

    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    time = pulseIn(ECHO, HIGH);
    distance = time*0.034/2;

    Serial.print("\n");
    Serial.print("time:");
    Serial.print(time);
    Serial.print(" ns, ");

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");

    return distance;
}

void forward() {
    analogWrite(ENL, 255);
    analogWrite(ENR, 255); 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void test() {
  analogWrite(ENL, 120);
  analogWrite(ENR, 0);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void backward() {
    analogWrite(ENL, 255);
    analogWrite(ENR, 255); 
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void clockwise() {
    analogWrite(ENL, 255);
//    analogWrite(ENR, 255); 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
//    digitalWrite(IN3, LOW);
//    digitalWrite(IN4, HIGH);
}

void anti_clockwise() {
    analogWrite(ENL, 255);
    analogWrite(ENR, 255); 
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void halt() {
    analogWrite(ENL, 0);
    analogWrite(ENR, 0); 
}

void loop() {

    int distance;
    
   while(d_counter() > 0 && d_counter() <= 120) {
       forward();
       if(d_counter() > 120) {
        break;
       }
   }

   test();

}