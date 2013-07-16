#include <Ethernet.h>
#include <SPI.h>

uint32_t i = 0;
long count = 0;

byte ard_mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x98, 0x19};
byte ard_ip[] = {192, 168, 7, 2};

EthernetServer server = EthernetServer(59000);

void setup()
{
Serial.begin(9600);
 Ethernet.begin(ard_mac, ard_ip);
 Serial.println(Ethernet.localIP());
 
 
 EthernetClient client;
 while(!client){
 client = server.available();
 Serial.println("Waiting for client...");
 delay(1000);
 }
 
 while(client.connected()){
  server.println(i); 
  count++;
 }
 
 Serial.println(count);

}

void loop()
{
  
    
}
