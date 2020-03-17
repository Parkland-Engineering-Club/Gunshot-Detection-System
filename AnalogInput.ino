/*
  Analog Input Testing Code
  Tests analog input by reading an analog sensor on analog pin 0 and 1 and 
  display the value and the voltage of both pins on LCD screen and in the serial 

  Make sure you set the Serial Monitor to 9600 baud 
  
*/
#include <LiquidCrystal.h> //LCD library

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int t1Pin = A0;    // select the input pin for the potentiometer
int t2Pin = A1;    // select the input pin for the potentiometer
float trigger1 = 0;  // variable to store the value coming from sensor 1
float trigger2 = 0;  // variable to store the value coming from sensor 2

void setup() {
  Serial.begin(9600); //initialize the serial
  lcd.begin(16, 2); //initialize the LCD with 16 columns and 2 rows
}

void loop() {
  int i = 0;
  Serial.print("A0 Analog");
  Serial.print("\t");
  Serial.print("A1 Analog"); 
  Serial.print("\t\t");
  Serial.print("A0 Voltage");
  Serial.print("\t");
  Serial.println("A1 Voltage"); 
  while(i < 32) {
    i++;
    // read the value from the sensor:
  trigger1 = analogRead(t1Pin);
  trigger2 = analogRead(t2Pin);
  float v1 = trigger1 * (5.0 / 1023.0);
  float v2 = trigger2 * (5.0 / 1023.0);
  Serial.print(trigger1);
  Serial.print("\t\t");
  Serial.print(trigger2);
  Serial.print("\t\t\t");
  Serial.print(v1);
  Serial.print(" V");
  Serial.print("\t\t");
  Serial.print(v2);
  Serial.println(" V");
  lcd.setCursor(0, 0);
  lcd.print("A0"); //diplay alert on LCD
  lcd.setCursor(3, 0);
  lcd.print(trigger1);
  lcd.setCursor(11, 0);
  lcd.print(v1);
  lcd.setCursor(15, 0);
  lcd.print("V");
  lcd.setCursor(0, 1);
  lcd.print("A1"); //diplay alert on LCD
  lcd.setCursor(3, 1);
  lcd.print(trigger2);
  lcd.setCursor(11, 1);
  lcd.print(v2);
  lcd.setCursor(15, 1);
  lcd.print("V");
  
  delay(500); //delay .5 secs
  lcd.clear();
  }
}
