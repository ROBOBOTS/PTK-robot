#include <SPI.h>
#include "RF24.h"
RF24 radio(7,8);
const uint64_t pipe = 0xF0F0F0F000LL;
int msg[1];
int potpin_1 = A0;
byte addresses[][6] = {"1Node","2Node"};
int left,right,left_map,right_map;
int control[10];

void setup(void){
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
radio.begin();
radio.openWritingPipe(addresses[1]);
radio.setChannel(0x60);                      //канал
}
void loop() {


left_map=map(analogRead(A0), 0, 930, -255, 255);
right_map=map(analogRead(A1), 0, 930, -255, 255);
control[1] = left_map;
control[2] = right_map;
Serial.println(control[1]);
radio.write(&control,sizeof(control));
}

