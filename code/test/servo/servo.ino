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
  digitalWrite(tx,LOW);

  if(digitalRead(startButton)==LOW){switchStatus++;}       //押されたときにaに１を加える
      while(digitalRead(startButton)==LOW){         //離すのを待つ
        if(digitalRead(startButton)==HIGH){break;}  //上りエッジで進む
      }


  int pose = 1;

  if(pose == 1){
      digitalWrite(ledStart,HIGH);
     
      if(switchStatus == 1){
         digitalWrite(tx,HIGH);
        for(int i=0; i<=2; i++){
        digitalWrite(ledStart,HIGH);
         tone(speaker,440);
        delay(150);
        digitalWrite(ledStart,LOW);
         noTone(speaker);
        delay(850);
        }
  
        digitalWrite(ledStart,HIGH);
        tone(speaker,440);
        delay(50);  
        servo.write(30);
        digitalWrite(tx,HIGH);
        delay(1000);

        servo.write(170);
        delay(1000);
        switchStatus++;
         noTone(speaker);
        

        
      }




  }


}
