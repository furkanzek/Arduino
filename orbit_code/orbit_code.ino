#include <SoftwareSerial.h>
#include <LoRa.h>

SoftwareSerial hc06(8,7);

void setup(){
  Serial.begin(9600); 
  hc06.begin(9600);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop(){
  if (hc06.available()){ 
    String msg=hc06.readString();
    LoRa.beginPacket();
    LoRa.print(msg);
    LoRa.endPacket();
  }

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      String rcv = LoRa.readString();
      hc06.print(rcv);
      hc06.print("\n");
    }
   }
   
   
   
}
