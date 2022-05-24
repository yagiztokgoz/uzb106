#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
RF24 radio(PB0, PA4); // CE, CSN on Blue Pill
const uint64_t address = 0xF0F0F0F0E1LL;
 
struct MyData 
{
  int counter;
  int16_t ivmex, ivmey, ivmez, isi, gyx, gyy, gyz;
  float pressure;
};
MyData data;
 
void setup() 
{
Serial.begin(9600);
radio.begin();
Serial.print("ADDRESS :");

radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver
}
 
int recvData()
{
  if ( radio.available() ) 
  {
    radio.read(&data, sizeof(MyData));
    return 1;
    }
    return 0;
}
 
 
void loop()
{
  if(recvData())
  {
 
  Serial.println("Data Received:");
  Serial.print("Packet No. = ");
  Serial.println(data.counter);
  
  Serial.print("Temperature = ");
  Serial.print(data.isi);
  Serial.println("*C");
 
  Serial.print("Pressure = ");
  Serial.print(data.pressure);
  Serial.println("hPa");
 
  Serial.print("İvme x = ");
  Serial.println(data.ivmex);

   
  Serial.print("İvme y = ");
  Serial.println(data.ivmey);

   
  Serial.print("İvme z = ");
  Serial.println(data.ivmez);

   
  Serial.print("gy x = ");
  Serial.println(data.gyx);

   
  Serial.print("gy y = ");
  Serial.println(data.gyy);

   
  Serial.print("gy z = ");
  Serial.println(data.gyz);
  


  Serial.println();

  delay(1000);
  }
}
