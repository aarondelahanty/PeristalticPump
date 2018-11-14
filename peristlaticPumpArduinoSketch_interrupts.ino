
/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);


// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line 


//Define global variables
const byte interruptPin = 7;
volatile byte state = LOW;
int pumpRun = 0;


/*********************************************************/
void setup()
{

  Serial.begin(9600);      // initialize serial communication:  

  //initialize the lcd
  lcd.init(); 
  lcd.backlight();
  lcd.clear();

  //initialize the stepper
  AFMS.begin();
  myMotor->setSpeed(1);
  myMotor->release();

  //initialize interrup pin
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), pumpRelease, RISING);
  
}

/*********************************************************/

void pumpRelease()
{
  lcd.setCursor(0,1); 
  lcd.printstr("PUMP PAUSED ");
  pumpRun = !pumpRun;
  while (digitalRead(interruptPin)== HIGH)
  {
  myMotor->release();
  }
}

void loop() 
{
 
  int switchVal = digitalRead(interruptPin);
  lcd.setCursor(0,0); 
  lcd.printstr("FLOW = ");
  lcd.setCursor(6,0);
  lcd.printstr(" 0.5 ml/m");

  while (pumpRun == 1 && digitalRead(12)== HIGH){
    lcd.setCursor(0,1);
    lcd.printstr("PUMP ENGAGED");
  
    myMotor->step(1, FORWARD, MICROSTEP); 
  }
}
/************************************************************/
