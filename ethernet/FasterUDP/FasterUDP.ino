#include <SPI.h>
#include <EthernetUDP.h>
#include "utility/w5100.h"
#include "utility/socket.h"
#include "Ethernet.h"

uint16_t i = 1234;
long packetCount = 0;

byte ard_mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x98, 0x19};
byte ard_ip[] = {192, 168, 7, 2};
byte comp_ip[] = {192, 168, 7, 1};

uint8_t many[1460];


EthernetUDP udp;

void setup()
{
 Serial.begin(9600);
 Ethernet.begin(ard_mac, ard_ip);
 udp.begin(59000);
 Serial.println(Ethernet.localIP());
 Serial.println(UDP_TX_PACKET_MAX_SIZE);
 
 //Serial.print("Divider is: ");
 //Serial.println(SPI.getClockDivider());
 SPI.setClockDivider(0x04);
 //Serial.print("Now it's: ");
 //Serial.print(SPI.getClockDivider());
 //Serial.println(millis());
 
 uint8_t lo = i & 0xFF;
 uint8_t hi = i >> 8;
 
 for (int j = 0; j < 1460; j++){
  
  many[j] = lo; j+=1;
  many[j] = hi;
   
 }
 
}

void loop()
{
  
 while(millis() < 60000){
   udp.beginPacket(comp_ip, 59000);
   //Serial.println("Begin packet!");
   
   
   while(udp._offset < UDP_TX_PACKET_MAX_SIZE){
     
        //Serial.print("TX free size: ");
        //Serial.println(W5100.getTXFreeSize(udp._sock));
     // Serial.print("Written: ");
     //Serial.println(written);
    
    //written += udp.write(lo); 
    //written += udp.write(hi);
    
    W5100.send_data_processing_offset(udp._sock, udp._offset, many, 1460);
    udp._offset +=1460;
    /*W5100.send_data_processing_offset(udp._sock, udp._offset, &hi, 1);  
    udp._offset +=1;
    */
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
