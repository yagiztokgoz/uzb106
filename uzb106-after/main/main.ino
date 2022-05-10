#include<Wire.h>
#define MPU 0x68
#include <BMP180.h>

int16_t ivmeX,ivmeY,ivmeZ,IsI,GyX,GyY,GyZ;
BMP180 myBMP(BMP180_ULTRAHIGHRES);

void setup(){


 /* mpu */  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
  Serial.begin(9600); /* BMP için de geçerli */

     while (myBMP.begin() != true)
  {
    Serial.println(F("BMP KABLOLARINDA SIKINTI VAR. KONTROL EDİN."));
    delay(5000);
  }
}

  /* mpu */

void loop(){
  mpu_data();
  
  Serial.print("ivmeX = "); Serial.print(ivmeX);
  Serial.print(" | ivmeY = "); Serial.print(ivmeY);
  Serial.print(" | ivmeZ = "); Serial.print(ivmeZ);
  Serial.print(" | Sicaklik = "); Serial.print(IsI/340.00+36.53);  
  Serial.print(" | GyroX = "); Serial.print(GyX);
  Serial.print(" | GyroY = "); Serial.print(GyY);
  Serial.print(" | GyroZ = "); Serial.println(GyZ);
  delay(333);

  bmp_data();
  buzzer_play();
  }


void mpu_data(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // mpu6050 nin ilk sensör verisinin adresi.
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true); //0X3B den başlayan 14 bitlik veri istendi. İçinde tüm değerlerimiz var.
  
  ivmeX=Wire.read()<<8|Wire.read();   
  ivmeY=Wire.read()<<8|Wire.read(); 
  ivmeZ=Wire.read()<<8|Wire.read(); 
  IsI=Wire.read()<<8|Wire.read(); 
  GyX=Wire.read()<<8|Wire.read(); 
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();

  
 
}
  
  
void buzzer_play(){
  
   
  tone(PA8, 1000, 500); // I/O pin A8
  
  delay(1000);
  }

void bmp_data(){


  int pressure;

  pressure = myBMP.getPressure();
  Serial.print(" | Rüstem = "); Serial.println(pressure);

  /*
  Serial.print(F("Temperature.......: ")); Serial.print(myBMP.getTemperature(), 1); Serial.println(F(" +-1.0C"));
  Serial.print(F("Pressure..........: ")); Serial.print(myBMP.getPressure());       Serial.println(F(" +-100Pa"));
  Serial.print(F("See level pressure: ")); Serial.print(myBMP.getSeaLevelPressure(115)); Serial.println(F(" Pa"));
  */
  }


  
