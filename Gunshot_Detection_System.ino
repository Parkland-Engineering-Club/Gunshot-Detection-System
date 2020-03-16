/*

  The LCD circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   10K pententiometer: //For contrast
    ends to +5V and ground
    wiper to LCD VO pin (pin 3)

   clap switch 1 LED to digital pin 10
   clap switch 2 LED to digital pin 9
   reset button to digital pin 8
   clap switch 1 input to digital pin 7
   clap switch 2 input to digital pin 6

*/
#include <LiquidCrystal.h> //LCD library

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int inPinS1 = A0/*6*/, inPinS2 = A1/*7*/, resetButtonPin = 8, ledPinS1 = 10, ledPinS2 = 9; //define all pins
int shotCount = 0, valueS1 = 0, valueS2 = 0;
bool eventS1 = 0, eventS2 = 0, eventMain = 0; //declare bools
unsigned long timePassed; //declares timer var

/* -------------------------------------------
 * Set the lowest trigger value here (max: 1032 = 5V)*/
const int triggerVal = 1032;
/* ------------------------------------------- */


/*The setup() function runs once, after each powerup or reset of the Arduino board */
void setup() {
  Serial.begin(9600); //initialize the serial
  lcd.begin(16, 2); //initialize the LCD with 16 columns and 2 rows
  /*For digital input pins:
  pinMode(inPinS1, INPUT); //set pins from the clap switch to input
  pinMode(inPinS2, INPUT);*/
  pinMode(resetButtonPin, INPUT);
  pinMode(ledPinS1, OUTPUT); //set the led indicators to outputs
  pinMode(ledPinS2, OUTPUT);
  lcd.setCursor(3, 0); //set the LCD cursor 5 columns in on the first line
  lcd.print("Parkland"); //plug
  lcd.setCursor(0, 1);
  lcd.print("Engineering Club");
  Serial.println("Parkland Engineering Club"); //print plug in serial
  delay(1750); //wait for 1750 ms
  lcd.clear(); //clear the lcd
  lcd.setCursor(4, 0);
  lcd.print("Gunshot"); //logo screen
  lcd.setCursor(0, 1);
  lcd.print("Detection System");
  Serial.println("Gunshot Detection System");
  delay(1750); //wait for 1750 ms
  lcd.clear();
  lcd.print("System Normal"); //this is what will be displayed while the system is waiting for an event
  delay(700); //wait for 700 ms
  timePassed = millis();
}
/*The loop() function runs continuosly until interupted or turned off*/
void loop() {
  while (digitalRead(resetButtonPin) == LOW) { //this loop will run until the reset button is pressed
    while (eventMain == 0 && digitalRead(resetButtonPin) == LOW) { //runs until both sensors are triggered
      Serial.println("System Waiting"); //this is what will be displayed every second while the system is waiting for an event
      while (millis() - timePassed < 1000 && eventMain == 0 && digitalRead(resetButtonPin) == LOW) { //resets the sensors every second
        /*For digital input pins:
         * 
        if (inPinS1 == HIGH) { //check if sensor 1 detects gunshot
          eventS1 = 1;
          Serial.println("Event Detected at Sensor 1"); //logs sensor 1 event into serial
          digitalWrite(ledPinS1, HIGH); //turns on the led
          timePassed = millis(); //starts the clock
        }*/
        valueS1 = analogRead(inPinS1);
        if (valueS1 >= triggerVal) { //check if sensor 1 detects gunshot
          eventS1 = 1;
          Serial.println("Event Detected at Sensor 1"); //logs sensor 1 event into serial
          digitalWrite(ledPinS1, HIGH); //turns on the led
          timePassed = millis(); //starts the clock
        }
        /*For digital input pins:
         * 
        if (inPinS2 == HIGH) {
          eventS2 = 1;
          Serial.println("Event Detected at Sensor 2"); //logs sensor 2 event into serial
          digitalWrite(ledPinS2, HIGH);
          timePassed = millis(); //starts the clock
        }*/
        valueS2 = analogRead(inPinS2);
        if (valueS2 >= triggerVal) { //check if sensor 1 detects gunshot
          eventS2 = 1;
          Serial.println("Event Detected at Sensor 1"); //logs sensor 1 event into serial
          digitalWrite(ledPinS2, HIGH);
          timePassed = millis(); //starts the clock
        }
        if (eventS1 == 1 && eventS2 == 1) { //if both events are triggered
          Serial.println("Main event triggered"); //logs main event into serial
          eventMain = 1;
          eventS1 = 0;
          eventS2 = 0;
        }
      }
      timePassed = millis(); //resets the clock
      eventS1 = 0;
      eventS2 = 0;
    }
    ++shotCount;
    if (shotCount = 1) {
      lcd.setCursor(0, 0);
      lcd.print("Shots Detected"); //diplay alert on LCD
      lcd.setCursor(0, 1);
      lcd.print("Shots:");
      lcd.setCursor(7, 1); //sets the cursor to the position that will be used until reset
    }
    lcd.print(shotCount); //updates shot count on LCD
    Serial.print("Shots Count: "); //prints shot count to the serial
    Serial.println(shotCount);
    eventMain = 0; //resets the bools
    eventS1 = 0;
    eventS2 = 0;
    digitalWrite(ledPinS1, LOW); //turns off the indicator LEDs
    digitalWrite(ledPinS2, LOW);
  }
  /* Everything below is part of the reset sequence */
  eventS1 = 0; //resets all the variables
  eventS2 = 0;
  eventMain = 0;
  shotCount = 0;
  digitalWrite(ledPinS1, LOW); //turns off the indicator LEDs
  digitalWrite(ledPinS2, LOW);
  lcd.clear();
  lcd.home(); //sets the cursor to (0,0)
  lcd.print("System Reset");
  Serial.println("------Reset-----"); //logs the reset to the serial
  delay(500);
  lcd.clear();
  lcd.print("System Normal");
}
