 
#define PIN 13

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  int hoge; 
  hoge=digitalRead(0);
  Serial.println(hoge);
  // put your main code here, to run repeatedly:
  tone(PIN,100000);

}
