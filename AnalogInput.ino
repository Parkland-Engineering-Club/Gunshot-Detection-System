/*
  Analog Input
  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().
  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground
  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.
  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/AnalogInput
*/
#include <LiquidCrystal.h> //LCD library

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int t1Pin = A0;    // select the input pin for the potentiometer
int t2Pin = A1;    // select the input pin for the potentiometer
int trigger1 = 0;  // variable to store the value coming from sensor 1
int trigger2 = 0;  // variable to store the value coming from sensor 2

void setup() {
  Serial.begin(9600); //initialize the serial
  lcd.begin(16, 2); //initialize the LCD with 16 columns and 2 rows
}

void loop() {
  
  Serial.print("A0 Analog");
  Serial.print("\t\t");
  Serial.println("A1 Analog");
  Serial.print("");
  Serial.print("\t\t");
  Serial.println("A1 Analog");//prints shot count to the serial
  int i = 0;
  while(i < 26) {
    i++;
    // read the value from the sensor:
    trigger1 = analogRead(t1Pin);
    trigger2 = analogRead(t2Pin);
    float v1 = trigger1 * (5.0 / 1023.0);
    float v2 = trigger2 * (5.0 / 1023.0);
    Serial.print(trigger1);
    Serial.print("\t\t\t");
    Serial.println(trigger2);
    lcd.setCursor(0, 0);
    lcd.print("A0"); //diplay alert on LCD
    lcd.setCursor(4, 0);
    lcd.print(trigger1);
    lcd.setCursor(0, 1);
    lcd.print("A1"); //diplay alert on LCD
    lcd.setCursor(4, 1);
    lcd.print(trigger2);
    delay(500); //delay .5 secs
  }
}
