void scan(){
 if(!Mirf.isSending() && Mirf.dataReady()){ 
   Mirf.getData((byte *) &data); 
 if(SERIAL==1){Serial.println(data[1]);}
   Mirf.setTADDR((byte *)"clie1"); 
   Mirf.send((byte *)&data); 
 //if(SPEEDMAX!=255){map(data[1],0,255,0,SPEEDMAX);map(data[3],0,255,0,SPEEDMAX);}
 if(data[1]<450){motorGo(0,1,map(data[1],450,0,0,255));}
 else if(data[1]>550){motorGo(0,0,map(data[1],550,1024,0,255));}
 
 if(data[3]<450){motorGo1(1,1,map(data[3],450,0,0,255));}
 else if(data[3]>550){motorGo1(1,0,map(data[3],550,1024,0,255));}
 //if(SERVOENABLE==1){servoCam.write(data[8]); servo.write(data[9]); servo1.write(data[10]); servo2.write(data[11]); servo3.write(data[12]); servo4.write(data[13]);}

} 
}
void motorOff(int motor)
{ 

}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
 if(motor==0&&direct==0){digitalWrite(IN1,0);analogWrite(IN2,pwm);}
  else if(motor==0&&direct==1){digitalWrite(IN2,0);analogWrite(IN1,pwm);}
  else if(motor==1&&direct==0){digitalWrite(IN3,0);analogWrite(IN4,pwm);}
  else if(motor==1&&direct==1){digitalWrite(IN4,0);analogWrite(IN3,pwm);} 
}
void motorGo1(uint8_t motor, uint8_t direct, uint8_t pwm)
{
 if(motor==0&&direct==0){digitalWrite(IN1,0);analogWrite(IN2,pwm);}
  else if(motor==0&&direct==1){digitalWrite(IN2,0);analogWrite(IN1,pwm);}
  else if(motor==1&&direct==0){digitalWrite(IN3,0);analogWrite(IN4,pwm);}
  else if(motor==1&&direct==1){digitalWrite(IN4,0);analogWrite(IN3,pwm);} 
}
