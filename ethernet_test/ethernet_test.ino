//Naive Ethernet throughput test using builtin Arduino server.println() 
//Will send continuously while client is connected. 
//When client disconnects, prints total values sent. 
//Use this for debugging and sanity checking.
//
//Use with arduinoclient.rb running on host. Some statistics will print to serial monitor. The client will run for 1 minute, then number of values sent will be printed over serial. Non-zero indicates everything is working fine. 

#include <Ethernet.h>
#include <SPI.h>

uint16_t i = 1234; //Send this value over and over. Real ADC values will be 16-bit
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
