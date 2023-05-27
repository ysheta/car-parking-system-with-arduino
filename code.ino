#include <Wire.h>        // include the I2C library
#include <LiquidCrystal_I2C.h>   // include the LCD I2C library
#include <Servo.h>

#define ENTRY_SENSOR 3   // define the digital pin for entry sensor
#define EXIT_SENSOR 4    // define the digital pin for exit sensor
#define SERVO_PIN 9      // define the digital pin for servo motor

#define TOTAL_SLOTS 4    // define the total number of parking slots

LiquidCrystal_I2C lcd(0x27, 16, 2);  // initialize the LCD I2C object

Servo myServo;

int car_count = 0;   // initialize the car count to zero
bool entry_flag = false;  // initialize the entry flag to false
bool exit_flag = false;   // initialize the exit flag to false

void setup() {
  myServo.attach(SERVO_PIN);
  pinMode(ENTRY_SENSOR, INPUT);   // set the entry sensor pin as input
  pinMode(EXIT_SENSOR, INPUT);    // set the exit sensor pin as input
  pinMode(SERVO_PIN, OUTPUT);     // set the servo motor pin as output

  lcd.init();         // initialize the LCD I2C
  lcd.backlight();    // turn on the backlight
  lcd.setCursor(0, 0);   // set the cursor to the first row
  lcd.print("Car Parking");  // print the header
  lcd.setCursor(0, 1);   // set the cursor to the second row
  lcd.print("Available: 4"); // print the available slots
}

void loop() {
  if (digitalRead(ENTRY_SENSOR) == HIGH && !entry_flag) {  // check if the entry sensor is triggered and the flag is false
    if (car_count < TOTAL_SLOTS) {  // check if there is an available parking slot
      digitalWrite(SERVO_PIN, HIGH);  // open the servo motor gate
      delay(500);  // wait for half a second
      digitalWrite(SERVO_PIN, LOW);   // close the servo motor gate
      car_count++;   // increment the car count
      lcd.setCursor(11, 1);   // set the cursor to the second row, column 11
      lcd.print(TOTAL_SLOTS - car_count);  // update the available slots on the LCD

      myServo.write(90); // rotate the servo 90 degrees
      delay(2000); // wait for 2 seconds
      myServo.write(0); // rotate the servo back to 0 degrees

      entry_flag = true;   // set the entry flag to true
    }
  }
  else if (digitalRead(EXIT_SENSOR) == HIGH && !exit_flag) {  // check if the exit sensor is triggered and the flag is false
    if (car_count > 0) {  // check if there is a parked car
      digitalWrite(SERVO_PIN, HIGH);  // open the servo motor gate
      delay(500);  // wait for half a second
      digitalWrite(SERVO_PIN, LOW);   // close the servo motor gate
      car_count--;   // decrement the car count
      lcd.setCursor(11, 1);   // set the
      lcd.print(TOTAL_SLOTS - car_count); // update the available slots on the on the LCD

      myServo.write(90); // rotate the servo 90 degrees
      delay(2000); // wait for 2 seconds
      myServo.write(0); // rotate the servo back to 0 degrees

 exit_flag = true; // set the exit flag to true
 }
 }

 if (digitalRead(ENTRY_SENSOR) == LOW && entry_flag) { // check if the entry sensor is not triggered and the flag is the flag is true
 entry_flag = false; // set the entry flag to false
 }
 if (digitalRead(EXIT_SENSOR) == LOW && exit_flag) { // check if the exit sensor is not triggered and the flag is true
 exit_flag = false; // set the exit flag to false
 }

 lcd.setCursor(0, 1); // set the cursor to the second row
 lcd.print("Total: "); // print the total number of parked cars on the LCD
 lcd.print(car_count); // print the car count on the LCD
 lcd.print(" "); // clear any remaining digits on the LCD
}
