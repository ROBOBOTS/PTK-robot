// Скетч «nrf24_client»
 #include <Wire.h>
// библиотека для работы с модулем GPIO Expander (I²C IO)
#include <GpioExpander.h>
// создаём объект adio класса GpioExpander по адресу 42
GpioExpander adio(42);
 
int data[10];
#include <SPI.h>
#include <RH_NRF24.h>
 
// создаем экземпляр класса для трансивера:
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7);   // для электрической совместимости с Mirf
// RH_NRF24 nrf24(8, 10);  // для Leonardo; также понадобится 
                           // явно определить контакт SS 
// RH_NRF24 nrf24(8, 7);   // для RFM73 на Anarduino Mini
 
void setup() 
Wire.begin();


{
  for(p=0;p<7;p++){data[p]=adio.pinMode(0, INPUT);}
  Serial.begin(9600);
 
  if (!nrf24.init())
    Serial.println("init failed");  //  "инициализация не удалась"
  // по умолчанию после инициализации трансивер настраивается
  // со следующими параметрами: 2,402 ГГц (канал 2), 2 Мбит/сек, 0 дБм
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
    //  "не удалось выполнить функцию setChannel()"
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps,   
      RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
    //  "не удалось выполнить функцию setRF()"
}
 
 
void loop()
{
  for(i=0;i<7;i++){data[i]=map.analogRead(i),0,1023,255,0);}
  Serial.println("Sending to nrf24_server");  //  "Отправка данных...
                                              //  ...на nrf24_server"
  // отправляем сообщение на nrf24_server:
  uint8_t data[] = "Hello World!";  //  "Привет, мир!"
  nrf24.send(data, sizeof(data));
  
  nrf24.waitPacketSent();
  // теперь ждем ответа:
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
 
  if (nrf24.waitAvailableTimeout(500))
  { 
    // ответное сообщение уже должно прийти:   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");  //  "получили ответ: "
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");  //  "не удалось выполнить... 
                                      //  ...функцию recv()"
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running?");
    //  "Ответа нет, nrf24_server вообще запущен?"
  }
  delay(400);
}
