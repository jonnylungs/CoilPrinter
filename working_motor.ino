// Stepper motor run code with A4988 driver and LCD code
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Stepper.h>
// Define Pins for Step Motor Driver
#define stepPin 7  // define pin for step
#define dirPin 8   // define pin for direction
#define enPin 9    // define pin for enable ^^ Do I need this?

// Define Buttons for Speed and Direction
#define buttGo 10      // define pin for button input
#define buttSwitch 11  // define pin for button input
#define incSpeed 12    // define button for increasing speed
#define decSpeed 13    // define button for decreeasing speed

// Define LCD pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;  // Adapter Pinout
const int i2c_addr = 0x27;                                                 // Adapter Pinout
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

float resolution = 1.8;
float rpm = 3;
unsigned int pulse_delay;  // Temporary starting value that will change after void setup
bool buttonState = false;
bool onState = false;

// Set up output types
void setup() {
  Serial.begin(9600);  // Change this baud rate to whatever rate the LCD screen runs on - should generally be 9600
  // Set up LCD screen
  pulse_delay = setRPM(rpm);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
  lcd.setCursor(0, 0);
  lcd.print("Current RPM: ");
  lcd.setCursor(12, 0);
  lcd.print(rpm);
  lcd.setCursor(0, 1);
  lcd.print("MOVE RIGHT");

  // Sets up buttons
  pinMode(buttSwitch, INPUT);
  pinMode(buttGo, INPUT);
  pinMode(incSpeed, INPUT);
  pinMode(decSpeed, INPUT);

  // Establish initials
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, HIGH);  // deactivate driver
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  pinMode(stepPin, OUTPUT);
  digitalWrite(enPin, LOW);  // activates driver
}

// Revolutions per second should be able specified to the tenths
// Run code to continual
void loop() {
  // Read Buttons Being Pressed
  int pressSwitch = digitalRead(buttSwitch);
  int pressGo = digitalRead(buttGo);
  int pressInc = digitalRead(incSpeed);
  int pressDec = digitalRead(decSpeed);
  pulse_delay = setRPM(rpm);  //pulse_delay = (rpm * 200)/60;

  if (pressSwitch == HIGH)  // Moves motor Right (Counter-Clockwise)
  {
    if (buttonState == 0) {
      digitalWrite(dirPin, LOW);  // sets direction of the motor turning
      buttonState = 1;
      lcd.setCursor(0, 1);
      lcd.print("MOVING  LEFT");
      delay(500);
    } else {
      if (buttonState == 1) {
        digitalWrite(dirPin, HIGH);  // sets direction of the motor turning
        buttonState = 0;
        lcd.setCursor(0, 1);
        lcd.print("MOVING RIGHT");
        delay(500);
      }
    }
  }
// Both of the next functions move the motor, but switches between Microseconds and Milliseconds in delay time to fit.
  if (pressGo == HIGH && pulse_delay >= 16383)  // Moves motor
  {
      digitalWrite(stepPin, HIGH);  // This LOW to HIGH change is what creates the "Rising Edge" so the easydriver knows when to step.
      delay(pulse_delay/1000);
      digitalWrite(stepPin, LOW);
  }

  if (pressGo == HIGH && pulse_delay < 16383)
  {
      digitalWrite(stepPin, HIGH);  // This LOW to HIGH change is what creates the "Rising Edge" so the easydriver knows when to step.
      delayMicroseconds(pulse_delay);
      digitalWrite(stepPin, LOW);
  }

  if (pressInc == HIGH)  // Increases RPM
  {
    rpm = rpm + 0.01;
    delay(150);
    lcd.setCursor(12, 0);
    lcd.print(rpm);
  }

  if (pressDec == HIGH)  // Decreases RPM
  {
    rpm = rpm - 0.01;
    delay(150);
    lcd.setCursor(12, 0);
    lcd.print(rpm);
  }
}

// Function to get pulse delay time based off of inputted RPM value
float setRPM(float rpm) {
  unsigned int pulsetime = (60000000 / (1600 * rpm));
  return pulsetime;  // Converts to microseconds
}
