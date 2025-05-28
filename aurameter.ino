/*
This is the aura-meter sketch by Emil Hannes (ratew on github)
So you have a LCD I2C, Sonar distance sensor, capacitive touch sensor
and passive buzzer connected to the arduino uno r3
first you go into default mode where the max aura is 3,000-10,000,
if you touch the sensor then it displays a "glitch" with 99999999 aura,
then it says "fuse failure" and resets
The buzzer buzzes accordingly aswell.
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x20,16,2); 

const int buz = 2;
const int cts = 3;
const int trig_pin = 9;
const int echo_pin = 10;
float timing = 0.0;
float distance = 0.0;
int outputValue;
float distanceB = 0.0;
int outputValueB;

void setup() {
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(cts, INPUT_PULLUP);
  digitalWrite(trig_pin, LOW);
  digitalWrite(buz, LOW);
  lcd.backlight();
  lcd.init();
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // Measure echo time
  int duration = pulseIn(echo_pin, HIGH);

  // Convert to distance in cm
  distance = duration * 0.034 / 2;

if(digitalRead(cts) == LOW){
   if (distance < 15){
    int maxOutput = random(3000, 10000);
     outputValue = map(distance, 100, 2, 0, maxOutput);
     outputValue = constrain(outputValue, 0, maxOutput);
   lcd.setCursor(0, 0);
   lcd.print("Aura Level:   ");
   lcd.setCursor(0, 1);
   lcd.print(outputValue);
   lcd.setCursor(4, 1);
   lcd.print("        ");
   int beepsB = outputValue / 100;
   tone(buz, 1000);
   delay(beepsB);
   noTone(buz);
   }
 }
else{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Aura Level:   ");
   lcd.setCursor(0, 1);
   lcd.print("99999999");
   for (int i=100; i>1; i--){
     tone(buz, 3000);
     delay(i);
     noTone(buz);
    }
    lcd.setCursor(0, 1);
    lcd.print("FUSE FAILURE");
   }
 }


void startsound(){

tone(buz, 500);
delay(10);
noTone(buz);
}
