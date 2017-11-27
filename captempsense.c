#include <CapacitiveSensor.h>

int led = 12;  //change '42' to any desired pin...
long time = 0;
int state = HIGH;

boolean yes;
boolean previous = false;

int debounce = 200;
int ThermistorPin = 1;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired// To add more sensors...//CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
   Serial.begin(9600);
   pinMode(led, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
long total1 =  cs_4_2.capacitiveSensor(30);
    
    if (total1 > 60){yes = true;}
    else {yes = false;}    

              if(yes==true && millis() - time>debounce)
              state = HIGH;
          else state = LOW; 
   
          
   
      digitalWrite(led, state);
     // previous = yes;
      
      //Serial.println(millis()-time);
      delay(10);

      if(state ==HIGH) {
      Vo = analogRead(ThermistorPin);
      R2 = R1 * (1023.0 / (float)Vo - 1.0);
      logR2 = log(R2);
      T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
      Tc = T - 273.15;
      Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");   

  delay(500);
     }
}