/*
This is the aura-meter sketch by Emil Hannes (emilhannes on github)
So you have a LCD I2C, Sonar distance sensor, capacitive touch sensor and passive buzzer connected to the arduino uno r3
first you go into default
mode where the max aura is 3,000-10,000, if you hold the capacitive touch sensor then it goes to high mode
with a maximum aura of 1,000,000 - "fuse broken" (1,000,001)
The buzzer buzzes accordingly aswell.
*/

// include necessary libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// create lcd object
LiquidCrystal_I2C lcd(0x20,16,2); 

// assign all variables
const int buz = 2;
const int cts = 3;
const int trig_pin = 9;
const int echo_pin = 10;
float timing = 0.0;
float distance = 0.0;
int outputValue;
float distanceB = 0.0;
int outputValueB;

// define all pins, initiate lcd and set pins 9 and 10 to low
void setup() {
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(cts, INPUT_PULLUP);
  digitalWrite(trig_pin, LOW);
  digitalWrite(buz, LOW);
  lcd.backlight();
  lcd.init();
  startsound(); // play starting sound
}

void loop() {
  // get ultrasonic reading
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // Measure echo time
  int duration = pulseIn(echo_pin, HIGH);

  // Convert to distance in cm
  distance = duration * 0.034 / 2;

  // print normal readinga
if(digitalRead(cts) == LOW){
   if (distance < 15){ // if you are under 15 cm close to someone
    int maxOutput = random(3000, 10000);
     outputValue = map(distance, 100, 2, 0, maxOutput); // map and constarin values
     outputValue = constrain(outputValue, 0, maxOutput);
     // print everything
   lcd.setCursor(0, 0);
   lcd.print("Aura Level:   ");
   lcd.setCursor(0, 1);
   lcd.print(outputValue);
   lcd.setCursor(4, 1);
   lcd.print("            ");
     //beep
   int beepsB = outputValue / 100;
   tone(buz, 1000);
   delay(beepsB);
   noTone(buz);
   }
 }
else{ // if pressed

  // print everything
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Aura Level:   ");
   lcd.setCursor(0, 1);
   lcd.print("9999999999999999");
   for (int i=100; i>1; i--){ // beep alot
     tone(buz, 3000);
     delay(i);
     noTone(buz);
    }
  // print more to lcd
    lcd.setCursor(0, 1);
    lcd.print("FUSE FAILURE    ");
    delay(1000);
    for(int x=1; x<6; x++){ // beep more
      lcd.setCursor(15, 1);
      lcd.print(x);
      delay(600);
    }
    delay(2); // wait 2 milliseconds
   }
 }


void startsound(){ // start sound function

tone(buz, 500);
delay(10);
noTone(buz);
}
