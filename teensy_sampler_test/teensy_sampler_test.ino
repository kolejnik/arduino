/* Use this to test if everything is working correctly. ADC values will be printed to serial console. Running the ruby client on the host is optional: you can just use the Arduino IDE's serial monitor to see the values. 
*/

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

const uint16_t capacity = 128;
long i = 0;
uint16_t written = 0;
uint8_t many[capacity];
long packetCount = 0;
void setup(){
 Serial.begin(9600);  
 
 //PRADC -- enable clock. It doesn't like this so I left it out
//cbi(PRR, PRADC); 

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

}

void loop(){
  
     
     while (!(bit_is_set(ADCSRA, ADIF))){
    //Serial.println("Waiting!");
  }
        
  uint8_t lo = ADCL;
  uint8_t hi = ADCH;
  Serial.println(lo | (hi << 8));
  delay(100);

   //Reset ADIF for next conversion by setting it to 1.
   sbi(ADCSRA, ADIF);
  }
  

