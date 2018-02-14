#include <String.h>

double i = 250.30;
void setup() {
  Serial.begin(9600);
}

void loop() {
  String h="";
  h=String(i,2);
  Serial.println(h);
}
