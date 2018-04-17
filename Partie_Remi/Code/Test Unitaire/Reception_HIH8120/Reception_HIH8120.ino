#include <Wire.h>

void setup() {
  Wire.begin();                 //Initialisation du Bus I2C
  Serial.begin(4800);
}

//variable declarations
int lecture = 0 ;
double humiditee = 0; 
String humidite;

void loop() {
  
Wire.beginTransmission(0x27);   //adresse I2C de la serie de capteur HIH8000
Wire.write(byte(0x00));         // Initialisation des mesures par l'envoie de zero bits 
Wire.endTransmission();         //arret de la transmission


delay(100);

Wire.requestFrom(0x27, 4); 
  if (4 <= Wire.available())    // Faire si les 4 bits sont reçue
   { 
      
      lecture = Wire.read();                // Lecture des donnees
      lecture = lecture << 8;               // Lecture des 8 bits de poids fort
      lecture |= Wire.read();               // Comparaison
      humiditee = lecture / 16382.0 * 100.0; //Conversion de l'humidite comme sur la documentation
      humidite = String(humiditee,2);
      Serial.print("Humidite : ");
      Serial.print(humidite);
      Serial.println ("%");
   }
}
   /*
      lecture = 0;//initilizing the lecture to read the temperature values
      /* Temperature is located in next two bytes, padded by two trailing bits */
     /* lecture = Wire.read();
      lecture = lecture << 6;
      lecture |= (Wire.read()>>2);
      temperature = lecture / 16382.0 * 165.0 - 40;//temperature conversion as per documentations...
      temperature1 = String(temperature,2);
      Serial.print("Temperature : ");
      Serial.print(temperature1);
      Serial.print ((char(176)));
      Serial.println ("C");
  }*/
