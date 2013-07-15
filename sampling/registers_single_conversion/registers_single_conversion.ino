#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 
long i = 0;

void setup()
{

//pinMode(A0, INPUT);
i = 0;
Serial.begin(9600);

//PRADC -- enable clock
cbi(PRR, PRADC);

//Prescaler: 16
sbi(ADCSRA, ADPS2);
cbi(ADCSRA, ADPS1);
cbi(ADCSRA, ADPS0);

//Free-running mode
//cbi(ADCSRB, ADTS0);
//cbi(ADCSRB, ADTS1);
//cbi(ADCSRB, ADTS2);

//Source: free-running
//sbi(ADCSRA, ADATE);

//ADC0
cbi(ADMUX, MUX0);
cbi(ADMUX, MUX1);
cbi(ADMUX, MUX2);
cbi(ADMUX, MUX3);

//AREF
cbi(ADMUX, REFS1);
cbi(ADMUX, REFS0);

//Disable digital input buffer, save power -- I'm not sure about this
//sbi(DIDR0,ADC0D);

sbi(ADCSRA, ADEN); //Enable
sbi(ADCSRA, ADSC); //Do one conversion. Initial conversion is slower than rest

}

void loop()
{
  
  sbi(ADCSRA, ADSC); //Start
  while( (bit_is_set(ADCSRA, ADSC))){
    
    //Serial.println("Waiting!");

  }
  
  
  uint8_t low = ADCL; uint8_t high = ADCH;
  uint16_t res = (high << 8) | low;
   Serial.println(res);
  //printStatus();
  
  //delay(100);
  
 
  //Measure speed
 /*i++;
  if (millis() > 60000){
    Serial.println((i/60.0));
    delay(1000);
  
  } */
}

void printStatus(){
 
 Serial.println("=======================");
 Serial.print("ADMUX: REFS0: ");
 Serial.print(bit_is_set(ADMUX, REFS0));
 Serial.print(" REFS1: ");
 Serial.print(bit_is_set(ADMUX, REFS1));
 Serial.print(" MUX3: ");
 Serial.print(bit_is_set(ADMUX, MUX3));
 Serial.print(" MUX2: ");
 Serial.print(bit_is_set(ADMUX, MUX2));
 Serial.print(" MUX1: ");
 Serial.println(bit_is_set(ADMUX, MUX1));
 
 //Serial.println("=======================");
 Serial.print("ADCSRA: ADEN: ");
 Serial.print(bit_is_set(ADCSRA, ADEN));
 Serial.print(" ADSC: ");
 Serial.print(bit_is_set(ADCSRA, ADSC));
 Serial.print(" ADATE: ");
 Serial.print(bit_is_set(ADCSRA, ADATE));
 Serial.print(" ADIF: ");
 Serial.print(bit_is_set(ADCSRA, ADIF));
 Serial.print(" ADIE: ");
 Serial.print(bit_is_set(ADCSRA, ADIE));
 Serial.print(" ADPS2: ");
 Serial.print(bit_is_set(ADCSRA, ADPS2));
 Serial.print(" ADPS1: ");
 Serial.print(bit_is_set(ADCSRA, ADPS1));
 Serial.print(" ADPS0: ");
 Serial.println(bit_is_set(ADCSRA, ADPS0));
 //Serial.println("=======================");
 
 Serial.print("ADCSRB: ADTS2: ");
 Serial.print(bit_is_set(ADCSRB, ADTS2));
 Serial.print(" ADTS1: ");
 Serial.print(bit_is_set(ADCSRB, ADTS1));
 Serial.print(" ADTS0: ");
 Serial.println(bit_is_set(ADCSRB, ADTS0));
 
 }

