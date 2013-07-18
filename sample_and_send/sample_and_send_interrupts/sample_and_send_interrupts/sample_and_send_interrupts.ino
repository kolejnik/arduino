#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

#include <SPI.h>
#include <EthernetUDP.h>
#include "utility/w5100.h"
#include "utility/socket.h"
#include "Ethernet.h"

#define capacity 200

byte ard_mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x98, 0x19};
byte ard_ip[] = {192, 168, 7, 2};
byte comp_ip[] = {192, 168, 7, 1};

//uint16_t capacity = 200;
uint8_t many[capacity];
volatile uint8_t written = 0;
uint16_t packetCount = 0;

EthernetUDP udp; 

void setup(){
  
 Serial.begin(9600);
 Ethernet.begin(ard_mac, ard_ip);
 udp.begin(59000);
 Serial.println(Ethernet.localIP());
 Serial.println(UDP_TX_PACKET_MAX_SIZE);
 SPI.setClockDivider(0x04);
 
  // =================================
  // ADC Config
  // =================================
  
  //PRADC -- enable clock
cbi(PRR, PRADC);

//Prescaler: 16
sbi(ADCSRA, ADPS2);
cbi(ADCSRA, ADPS1);
cbi(ADCSRA, ADPS0);

//Free-running mode
cbi(ADCSRB, ADTS0);
cbi(ADCSRB, ADTS1);
cbi(ADCSRB, ADTS2);

//Source: free-running
sbi(ADCSRA, ADATE);

//Interrupts enable
sbi(ADCSRA, ADIE);

//ADC0
cbi(ADMUX, MUX0);
cbi(ADMUX, MUX1);
cbi(ADMUX, MUX2);
cbi(ADMUX, MUX3);

//Avcc -- Internal 5V reference
cbi(ADMUX, REFS1);
sbi(ADMUX, REFS0);

//Disable digital input buffer, save power
//sbi(DIDR0,ADC0D);

sbi(ADCSRA, ADEN); //Enable
sbi(ADCSRA, ADSC); //Initial conversion is slow

//Start first packet  
udp.beginPacket(comp_ip, 59000);  

//Enable interrupts
sei();
}

void loop(){
  
 while(millis() < 60000){
  
  while(written >= capacity){ // Write to buffer
  written = 0;
      if (udp._offset < UDP_TX_PACKET_MAX_SIZE){ //If there is space in the buffer
      //Serial.println("Writing to TX buffer");
       W5100.send_data_processing_offset(udp._sock, udp._offset, many, capacity);
       udp._offset += capacity;
       //Serial.print("Offset: ");
       //Serial.println(udp._offset);
      }
    
      else { //The buffer is full, send packet
       // Serial.println("Sending packet");
        udp.endPacket();
        packetCount++;
        udp.beginPacket(comp_ip, 59000); //begin the next one
      }
    
  }
 
  
 }

//Serial.println(packetCount); 
//Serial.println(UDP_TX_PACKET_MAX_SIZE);
Serial.println(packetCount * (UDP_TX_PACKET_MAX_SIZE/2.0) / 60.0); 
}

ISR(ADC_vect){
  many[written] = ADCL; written++; //Not the best
  many[written] = ADCH; written++; 
  
}
