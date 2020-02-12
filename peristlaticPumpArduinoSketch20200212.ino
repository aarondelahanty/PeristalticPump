
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
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// Variable for the button's current state.
// button_mode = 1 when the button is up, and 0 when the button is pressed.
// This variable is 'static' and persists because it is declared outside of a function.
int button_mode = 1;

//define pump state (independent of button mode)
int pumpRun = 0;

/*********************************************************/
void setup()
{

  Serial.begin(9600);      // initialize serial communication:
  // Set Digital pin 7 to an input so it can monitor the button.
  pinMode(7, INPUT_PULLUP);


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


  // Check Digital pin 7 to see if it's pressed.
  if ((digitalRead(7) == HIGH) && (button_mode == 1) )
  {

    // Button was up before, but is pressed now. Set the button to pressed
    // and report that to the serial monitor.
    button_mode = 0; // Button is pressed.
    pumpRun = ! pumpRun;
    Serial.println("Button has been pressed.");
    Serial.println(pumpRun);
  }


  else if ((digitalRead(7) == LOW) && (button_mode == 0) )
  {
    // Button was down before, but is released now. Set the button to
    // released and report that to the serial monitor.
    button_mode = 1; // Button is released.
    Serial.println("Button has been released");
  }

  delay(10);
  //small delay to account for button bounce.

  if (pumpRun == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print(1);
    myMotor->step(1, FORWARD,MICROSTEP);
    //add delay to pump at even slower flowrates
    delay(100);
  }
  else if (pumpRun==0)
  {
  myMotor->release();
  Serial.println("Stepper released");
  }

}
