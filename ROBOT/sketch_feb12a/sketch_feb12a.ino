#include <Servo.h>

Servo serv;

void setup() {
 serv.attach(15);
  pinMode(14,INPUT);
  // put your setup code here, to run once:

}

void loop() {
  if(digitalRead(14)==1){serv.write(160);}
  else if(digitalRead(14)==0){serv.write(30);}
  // put your main code here, to run repeatedly:

}
