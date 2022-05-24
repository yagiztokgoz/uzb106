#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <BMP180.h>
#define MPU 0x68

BMP180 aftermosphere_bmp(BMP180_ULTRAHIGHRES);
 
RF24 radio(PB0, PA4); // CE, CSN on Blue Pill 
const uint64_t address = 0xF0F0F0F0E1LL;
int counter = 0;


int16_t ivmex, ivmey, ivmez, isi, gyx, gyy, gyz;
float pressure;
 

struct MyData 
{
  int counter;
  int16_t ivmex, ivmey, ivmez, isi, gyx, gyy, gyz;
  float pressure;
};
MyData data;
 
void setup() 
{
Wire.begin();
Wire.beginTransmission(MPU);
Wire.write(0);
Wire.endTransmission(true);
aftermosphere_bmp.begin();

Serial.begin(9600);
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter
 
 
}
 
void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  
  data.counter = counter;
  data.ivmex = Wire.read()<<8|Wire.read();
  data.ivmex = data.ivmex % 360;
  
  data.ivmey = Wire.read()<<8|Wire.read();
  data.ivmey = data.ivmey % 360;
  
  data.ivmez = Wire.read()<<8|Wire.read();
  data.ivmez = data.ivmez % 360;
  
  data.isi = Wire.read()<<8|Wire.read();
  data.isi = data.isi / 340.00 + 36.53;
  
  data.gyx = Wire.read()<<8|Wire.read();
  data.gyx = data.gyx % 360;
  
  data.gyy = Wire.read()<<8|Wire.read();
  data.gyy = data.gyy % 360;
  
  data.gyz = Wire.read()<<8|Wire.read();
  data.gyz = data.gyz % 360;

  data.pressure = aftermosphere_bmp.getPressure();
  
  radio.write(&data, sizeof(MyData));
  
  Serial.println("Data Packet Sent");
  Serial.println("");
  
  counter++;
  delay(1000);
}
