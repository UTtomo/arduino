#include <Servo.h>



int speaker = 7;
int ledStart = 8;
int startButton = 10;
int tx= 13;

Servo servo;
int angle=50;
int switchStatus = 0;


void setup() {
  // put your setup code here, to run once:
  servo.attach(5);
  
  pinMode(speaker,OUTPUT);
  pinMode(ledStart,OUTPUT);
  pinMode(startButton,INPUT);
  pinMode(tx,OUTPUT);

digitalWrite(tx,LOW);
servo.write(170);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(170);
  delay(500);
  servo.write(30);
  delay(500);
}
