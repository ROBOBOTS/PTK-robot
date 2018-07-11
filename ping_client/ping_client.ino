/**
 * A Mirf example to test the latency between two Ardunio.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 * Note: To see best case latency comment out all Serial.println
 * statements not displaying the result and load 
 * 'ping_server_interupt' on the server.
 */
#include <Wire.h>
#include <GpioExpander.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
int data[31];
GpioExpander adio(0x14);
void setup(){
  Serial.begin(9600);
  Wire.begin();
   
   
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = 32;
  Mirf.config();
  Serial.println("Beginning ... "); 
}

void loop(){
  adio.analogRead(1);
  adio.analogRead(2);
  adio.analogRead(3);
  adio.analogRead(5);
  data[1]=analogRead(A0);
  data[3]=analogRead(A1);
  unsigned long time = millis();
  Mirf.setTADDR((byte *)"serv1");
  Mirf.send((byte *)&data);
  while(Mirf.isSending()){
  }
  Serial.println("Finished sending");
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
  Mirf.getData((byte *) &data);
  delay(1);
} 
  
  
  
