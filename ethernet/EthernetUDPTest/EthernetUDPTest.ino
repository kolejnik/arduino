#include <Ethernet.h>
#include <SPI.h>
#include <EthernetUDP.h>
#include "utility/w5100.h"

uint16_t i = 1234;
int written;
long packetCount = 0;

byte ard_mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x98, 0x19};
byte ard_ip[] = {192, 168, 7, 2};
byte comp_ip[] = {192, 168, 7, 1};

EthernetUDP udp;

void setup()
{
 Serial.begin(9600);
 Ethernet.begin(ard_mac, ard_ip);
 udp.begin(59000);
 Serial.println(Ethernet.localIP());
 Serial.println(UDP_TX_PACKET_MAX_SIZE);
 //Serial.println(millis());
 
 
 while(true){
   udp.beginPacket(comp_ip, 59000);
   //Serial.println("Begin packet!");
   written = 0;
   //Serial.println(written);
   
   while(written < UDP_TX_PACKET_MAX_SIZE){
     
     /*Serial.print("TX free size: ");
     Serial.println(W5100.getTXFreeSize(udp._sock));
     
     Serial.print("UDP TX PACKET MAX SIZE: ");
     Serial.println(UDP_TX_PACKET_MAX_SIZE); 
     */
    uint8_t lo = i & 0xFF;
    uint8_t hi = i >> 8;
         
    written += udp.write(lo); 
    written += udp.write(hi);
    
    /*Serial.print("Written: ");
    Serial.println(written);*/
   }
 
  udp.endPacket();
  packetCount++;
  /*Serial.print("Packets: ");
  Serial.println(packetCount);*/
  
  
}

Serial.println(packetCount); 
Serial.println(packetCount * (UDP_TX_PACKET_MAX_SIZE/2) / 60.0); 

}

void loop()
{
  
    
}
