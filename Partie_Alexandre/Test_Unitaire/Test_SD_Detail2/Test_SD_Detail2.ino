#include <SPI.h>
#include "SDFat.h"
#define SDCS 4
#define BUFFER_SIZE 100
SdFat sd;
uint8_t buf[BUFFER_SIZE];

void setup(){
  SdFile fichier;
  Serial.begin(115200);
  Serial.println("Initialisation SD...");
  if (!sd.begin(SDCS,SPI_HALF_SPEED)){
    Serial.println("Erreur initialisation");
    return;
  }
uint32_t volume = int(sd.vol()->blocksPerCluster());
volume *=sd.vol()->clusterCount();
volume *=512;
Serial.print("Taille du volume: ");
Serial.print(volume/1024/1024);
Serial.println(" Mo");

uint32_t volumelibre = sd.vol()->freeClusterCount();
volumelibre *=int(sd.vol()->blocksPerCluster());
volumelibre *=512;
Serial.print("Espace libre: ");
Serial.print(volumelibre/1024/1024);
Serial.println(" Mo");

Serial.println(" ");
sd.ls("/",LS_SIZE|LS_R);
Serial.println(" ");
if (!fichier.open(&sd, "logo.png", O_READ)){
  Serial.println("Erreur ouverture fichier");
  return;
}

int n = fichier.read(buf, sizeof(buf));
Serial.print(n);
Serial.println(" octet(s) lu(s)");

String myString = String((char *)buf);
myString.trim();

Serial.print("\"");
Serial.print(myString);
Serial.println("\"");

fichier.close();
}    
void loop() {
}

