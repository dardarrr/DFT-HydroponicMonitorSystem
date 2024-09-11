#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#define TRIGGER_PIN 5 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 6 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pin_relay=12;

void setup() {
Serial.begin(9600);
Serial.println(F("ultrasonik test")); // Open serial monitor at 115200 baud to see ping results.
lcd.begin(16,2);
pinMode(pin_relay,OUTPUT);
digitalWrite(pin_relay,HIGH);
lcd.setCursor(1,0); 
lcd.print("Welcome to");
lcd.setCursor(1,1); 
lcd.print("Group 2 RB");
delay(2000);
lcd.clear();
lcd.setCursor(2,0); 
lcd.print("Water Level");
lcd.setCursor(2,1); 
lcd.print("Sensor");
delay(2000);
lcd.clear();
}

void loop() {
delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();
Serial.print("Jarak: ");
 Serial.print(cm);
 Serial.println(" cm"); // Send out the ping, get the results in centimeters.
lcd.setCursor(0,0);  
lcd.print("Kedalaman: ");
if(cm<10){
lcd.setCursor(12,0); 
lcd.print("0");
lcd.setCursor(13,0);
lcd.print(cm); 
delay(500);
}
if(cm>=10){
lcd.setCursor(12,0);
lcd.print(cm); 
}
lcd.setCursor(14,0); 
lcd.print("cm");

if(cm>=15) {
  digitalWrite(pin_relay,LOW);
  lcd.setCursor(3,1);
  lcd.print("POMPA NYALA");
}
if(cm<=10) {
  digitalWrite(pin_relay,HIGH);
  lcd.setCursor(3,1);
  lcd.print("POMPA MATI");
}


}

