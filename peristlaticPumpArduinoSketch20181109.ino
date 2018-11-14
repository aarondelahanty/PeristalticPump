
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
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

/*********************************************************/
void setup()
{

  Serial.begin(9600);      // initialize serial communication:  
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(1);
  myMotor->release();
}

/*********************************************************/
void loop() 
{
  pinMode(7,INPUT_PULLUP);
  int switchVal = digitalRead(7);
  int pumpRun = 0;
 
 // upon initialisation and while pumprun is inactive 
 while (pumpRun == 0 && digitalRead(7)== HIGH){
  delay(250);
  lcd.setCursor(0,0); 
  lcd.printstr("FLOW = ");
  lcd.setCursor(6,0);
  lcd.printstr(" 0.5 ml/m");
   
   
    //toggle pumpRun state when button is depressed
    if (digitalRead(7) == LOW){
      pumpRun = !pumpRun;
      delay(250);
      break;
    }
  
  lcd.setCursor(0,1); 
  lcd.printstr("PUMP PAUSED ");
  myMotor->release();
}

  //While pumprun is active
  while (pumpRun == 1 && digitalRead(7)== HIGH)\{
    lcd.setCursor(0,1);
    lcd.printstr("PUMP ENGAGED");
    myMotor->step(1, FORWARD, MICROSTEP); 

}
