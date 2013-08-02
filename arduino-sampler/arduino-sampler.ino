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
#include "avr/sleep.h"

#define capacity 1400 //Max. possible with available memory

byte ard_mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x98, 0x19}; //Arduino MAC address
byte ard_ip[] = {192, 168, 7, 2}; //Arduino IP
byte comp_ip[] = {192, 168, 7, 1}; //Computer IP

uint8_t adc_vals[capacity]; //Store ADC values in here
volatile uint16_t written = 0; //Values written to 
uint16_t packetCount = 0; //Packets sent

EthernetUDP udp; 

void setup(){
 Serial.begin(9600);
 Ethernet.begin(ard_mac, ard_ip);
 udp.begin(59000);
 Serial.println(Ethernet.localIP()); //Print IP address so we know everything is working
 Serial.println(UDP_TX_PACKET_MAX_SIZE); 
 SPI.setClockDivider(0x04);
 
  // =================================
  // ADC Config
  // =================================
  
  //PRADC -- enable ADC clock
cbi(PRR, PRADC);

//Prescaler: 16
sbi(ADCSRA, ADPS2);
cbi(ADCSRA, ADPS1);
cbi(ADCSRA, ADPS0);

//Free-running mode
cbi(ADCSRB, ADTS0);
cbi(ADCSRB, ADTS1);
cbi(ADCSRB, ADTS2);

//Trigger source: free-running
sbi(ADCSRA, ADATE);

//ADC interrupt enable
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

//ADC noise reduction mode
cbi(SMCR, SM2);
cbi(SMCR, SM1);
sbi(SMCR, SM0);

//Start first packet  
udp.beginPacket(comp_ip, 59000);  

//Enable interrupts
sei();
}

void loop(){
   
   //Sleep enable
   sbi(SMCR, SE);
   //Sleep
   sleep_cpu();
   //Sleep disable
   cbi(SMCR, SE);
    
}

ISR(ADC_vect){
  if (written < capacity - 1)
  { // Room for 2 more values (1 reading)
  readADC();
  }

  else if (udp._offset < UDP_TX_PACKET_MAX_SIZE - capacity)
  {//Room in the udp buffer?
   writeToBuffer(); 
  }
  
  else{ //No room in UDP buffer, send packet now
    sendData();
  }
  
}

void readADC(){
 cli();
 adc_vals[written] = ADCL; written++; //Must read low value first
 adc_vals[written] = ADCH; written++;  
 sei();
}

void sendData(){ 
 cli();
 udp.endPacket(); 
 packetCount++;
 udp.beginPacket(comp_ip, 59000); //End packet and begin a new one
 sei();
}

void writeToBuffer(){
 
 cli();
 W5100.send_data_processing_offset(udp._sock, udp._offset, adc_vals, capacity);
 udp._offset += capacity;
 written = 0; 
 sei();
  
}
