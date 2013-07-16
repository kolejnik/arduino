#include <SPI.h>
#include <EthernetUDP.h>
#include "utility/w5100.h"
#include "utility/socket.h"
#include "Ethernet.h"
#include "Udp.h"
#include "Dns.h"

uint16_t i = 1234;
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
   Serial.println("Begin packet!");
   
   uint8_t lo = i & 0xFF;
   uint8_t hi = i >> 8;
   
   while(udp._offset < UDP_TX_PACKET_MAX_SIZE){
     
        //Serial.print("TX free size: ");
        //Serial.println(W5100.getTXFreeSize(udp._sock));
     // Serial.print("Written: ");
     //Serial.println(written);
    
    //written += udp.write(lo); 
    //written += udp.write(hi);
    
    W5100.send_data_processing_offset(udp._sock, udp._offset, &lo, 1);
    udp._offset +=1;
    W5100.send_data_processing_offset(udp._sock, udp._offset, &hi, 1);  
    udp._offset +=1;
    
    /*Serial.print("Offset: ");
    Serial.println(udp._offset);*/
     
   }
 
  udp.endPacket();
  packetCount++;
  
  
  //Serial.println("Sending packet!");
}

Serial.println(packetCount); 
Serial.println(packetCount * (UDP_TX_PACKET_MAX_SIZE/2) / 60.0); 

}

void loop()
{
  
    
}
