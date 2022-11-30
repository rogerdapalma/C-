 
#include <LiquidCrystal.h>  
  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  
// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A10;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 2; // Analog output pin that the LED is attached to

int potencia;
int fonte = A12;
int terra = A8;
int terraa = 52;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
  
void setup()   
{  
   Serial.begin(9600);
  pinMode(fonte, OUTPUT);
  pinMode(terra, OUTPUT);
  pinMode(terraa, OUTPUT);
  pinMode(analogOutPin, OUTPUT);


  digitalWrite(fonte, HIGH);
  digitalWrite(terra, LOW);
  digitalWrite(terraa, LOW);
 
}  
  
void loop()  
{  
 
 // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1022, 0, 100);
  potencia = map(sensorValue, 0, 1022, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, potencia);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print(" Potência = ");
  Serial.println(outputValue);
 lcd.clear();
 lcd.begin(16, 2);  

 lcd.setCursor(1,0);  
 lcd.print("Goog Breathing"); 
 
 lcd.setCursor(0,1);  
 lcd.print("Potencia");  
 lcd.setCursor(13,1);  
 lcd.print("%"); 
 lcd.setCursor(10,1);  
 lcd.print(outputValue);  

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(80);
}
