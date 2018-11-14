
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
  
 while (pumpRun == 0 && digitalRead(7)== HIGH){
  delay(250);
  lcd.setCursor(0,0); 
  lcd.printstr("FLOW = ");
  lcd.setCursor(6,0);
  lcd.printstr(" 0.5 ml/m");
  
  if (digitalRead(7) == LOW){
    pumpRun = !pumpRun;
    delay(250);
    break;
  }
  
  lcd.setCursor(0,1); 
  lcd.printstr("PUMP PAUSED ");
  myMotor->release();
  }

   while (pumpRun == 1 && digitalRead(7)== HIGH){
  lcd.setCursor(0,1);
  lcd.printstr("PUMP ENGAGED");
  
  myMotor->step(1, FORWARD, MICROSTEP); 

  /*
  if (digitalRead(12) == LOW){
  pumpRun = !pumpRun;
  lcd.clear();
  delay(250);
  break;
  }
  */
  }
  


  


  
  
  /*for (int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
  {
    lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
    lcd.print(array1[positionCounter1]); // Print a message to the LCD.
    delay(tim); //wait for 250 microseconds
  }
  lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left  corner.
  lcd.setCursor(15,1); // set the cursor to column 15, line 1
  for (int positionCounter = 0; positionCounter < 26; positionCounter++)
  {
    lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
    lcd.print(array2[positionCounter]); // Print a message to the LCD.
    delay(tim); //wait for 250 microseconds
  }
  */
 // lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.

}
/************************************************************/
