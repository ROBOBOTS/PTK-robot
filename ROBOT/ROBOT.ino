/*-----------------------------------------Settings-------------------------------------------*/
#define SERIAL 1
#define SPEEDMAX 255
#define SERVOENABLE 0
#define SOUND 0
/*--------------------------------------------------------------------------------------------*/
#define IN1 5//37
#define IN2 6//38
#define IN3 9//39
#define IN4 10//40

#include <SPI.h> 
#include <Mirf.h> 
#include <nRF24L01.h> 
#include <MirfHardwareSpiDriver.h> 
#include <Servo.h> 
 unsigned long dataCheck; 
 int data[31]; 
 int check2; 
Servo servoCam; Servo servo; Servo servo1; Servo servo2; Servo servo3; Servo servo4;

void setup(){ 
 if(SERIAL==1){Serial.begin(9600);} 
 if(SERVOENABLE==1){servoCam.attach(30); servo.attach(31); servo1.attach(38); servo2.attach(35); servo3.attach(33); servo4.attach(32);} 
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
   //   Mirf.csnPin = 53;
  // Mirf.cePin = 16;
 Mirf.spi = &MirfHardwareSpi; 
   Mirf.init(); 
   Mirf.setRADDR((byte *)"serv1"); 
   Mirf.payload = 32; 
   Mirf.config(); 
} 

void loop(){ 
scan();
}
