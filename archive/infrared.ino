#include "stdio.h"

int IR_L = 2;
int IR_R = 3;
int LED = 13;
#define ENL 5
#define ENR 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 4

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);
}

void forward() {
    analogWrite(ENL, 255);
    analogWrite(ENR, 255); 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void test_1() {
  analogWrite(ENL, 80);
  analogWrite(ENR, 0);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void test_2() {
  analogWrite(ENL, 0);
  analogWrite(ENR, 80);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}



void loop() {

    //on black line
  while(digitalRead(IR_L) == 1 && digitalRead(IR_R) == 1){
    digitalWrite(LED, HIGH);
    forward();
  }

  while(digitalRead(IR_L) == 0 && digitalRead(IR_R) == 1){
    digitalWrite(LED, LOW);
    test_2();
  }

  while(digitalRead(IR_L) == 1 && digitalRead(IR_R) == 0){
    digitalWrite(LED, LOW);
    test_1();
  }

}