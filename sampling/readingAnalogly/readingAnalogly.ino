#include <Ethernet.h>
#include <SPI.h>

long i = 0;

void setup()
{

i = 0;
Serial.begin(9600);

//1.1v internal reference
analogReference(INTERNAL);
}

void loop()
{
 
  //delay(100);
  Serial.println(analogRead(0));
  //printStatus();
  
  /*
  i++;
  if (millis() > 60000){
  Serial.println((i/60.0));
   delay(1000);
  }
    */
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

