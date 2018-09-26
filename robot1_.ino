// Необходимо установить библиотеку для радиомодуля nRF24
#include <SPI.h>
#include "RF24.h"
#define in1 5
#define in2 6
#define in3 3
#define in4 4
RF24 radio(7,8);
const uint64_t pipe = 0xF0F0F0F000LL;
int data;
int pos;
int fspeed;           // forward speed
int bspeed;           // backward speed
int control[10];
byte addresses[][6] = {"1Node","2Node"}; 
void go(int speed_l, int speed_r) 
{
  boolean r_dir,l_dir;//0-вперед, 1-назад
  if(speed_l<=75&&speed_l>=-75)speed_l=0;
  else if(speed_l>75)l_dir=0;
  else if(speed_l<-75){speed_l=abs(speed_l);l_dir=1;}
  if(speed_r<=75&&speed_r>=-75)speed_r=0;
  else if(speed_r>75)r_dir=0;
  else if(speed_r<-75){speed_r=abs(speed_r);r_dir=1;}
  if(r_dir==0){digitalWrite(in1,0);analogWrite(in2,speed_r);}
  else if(r_dir==1){digitalWrite(in2,0);analogWrite(in1,speed_r);}

  if(l_dir==0){digitalWrite(in3,0);analogWrite(in4,speed_l);}
  else if(l_dir==1){digitalWrite(in4,0);digitalWrite(in3,speed_l);}
} 
void setup()
{
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
delay(50);
radio.begin();
radio.openReadingPipe(1,addresses[1]);
radio.setChannel(0x60);
radio.startListening();
}
//контрол 1 лев
//контрол 2 прав

void loop()
{
if (radio.available())radio.read(control, sizeof(control));
go(control[1],control[2]);
}

