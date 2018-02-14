#include <Wire.h>

void setup() {
  Wire.begin();//initilizing i2c
  Serial.begin(4800);
}

//variable declarations
int reading = 0 ;
double humidity = 0 , temperature = 0 ; 
String temperature1,humidite;

void loop() {
  
Wire.beginTransmission(0x27); //adresse I2C de la serie de capteur HIH8000
Wire.write(byte(0x00));       // Initialisation des mesures par l'envoie de zero bits 
Wire.endTransmission();       //arret de la transmission


delay(100);

Wire.requestFrom(0x27, 4); 
  if (4 <= Wire.available())    // Faire si les 4 bits sont reçue
   { 
      /* Humidity is located in first two bytes */
      reading = Wire.read();  // receive high byte (overwrites previous reading)
      reading = reading << 8;// shift high byte to be high 8 bits
      reading |= Wire.read(); // receive low byte as lower 8 bits
      humidity = reading / 16382.0 * 100.0; //humidity conversion as per the documentation
      humidite = String(humidity,2);
      Serial.print("Humidite : ");
      Serial.print(humidite);
      Serial.println ("%");
      reading = 0;//initilizing the reading to read the temperature values
      /* Temperature is located in next two bytes, padded by two trailing bits */
      reading = Wire.read();
      reading = reading << 6;
      reading |= (Wire.read()>>2);
      temperature = reading / 16382.0 * 165.0 - 40;//temperature conversion as per documentations...
      temperature1 = String(temperature,2);
      Serial.print("Temperature : ");
      Serial.print(temperature1);
      Serial.print ((char(176)));
      Serial.println ("C");
  }
}
