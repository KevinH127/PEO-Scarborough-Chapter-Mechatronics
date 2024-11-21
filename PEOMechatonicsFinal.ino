// import Servo library
#include <ESP32Servo.h>

// define Joystick Pins
#define buttonPin 25
#define joystickXPin 35
#define joystickYPin 34

// define LEDS
#define centreLED 13 // blue LED
#define leftLED 27 // green LED
#define rightLED 26 // yellow LED
#define bottomLED 14 // white LED
#define topLED 12 // red LED

bool buttonState = HIGH;
bool buttonToggle = HIGH;
int buttonCount = 0;

// Initializing Servo Motors
Servo servoX; // Servo X is the Base, moving left to right
Servo servoY; // Servo Y is the Arm, moving up and down
Servo servoG; // Servo G is the hand, opening and closing

int minUs = 520;
int maxUs = 2480;

// Defining Servo Pins
int servoXPin = 18;
int servoYPin = 19;
int servoGPin = 21;

// Initializing Servo Positions
int servoXPos = 30;
int servoYPos = 0;
int servoGPos = 0;

// Min/Max Position for all Servos
int servoXPos_min = 10;
int servoXPos_max = 180;

int servoYPos_min = 0;
int servoYPos_max = 180;

int servoGPos_min = 0;
int servoGPos_max = 90;

// Initializing Joystick Values
int joystickXValue = 0;
int joystickYValue = 0;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  // pin mode for LEDS
  pinMode(centreLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(bottomLED, OUTPUT);
  pinMode(topLED, OUTPUT);

  servoX.attach(servoXPin, minUs, maxUs);
  servoY.attach(servoYPin, minUs, maxUs);
  servoG.attach(servoGPin, minUs, maxUs);

  servoX.write(servoXPos_min);
  servoY.write(servoYPos_min);
  servoG.write(servoGPos_min);

  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  joystickXValue = analogRead(joystickXPin);
  joystickYValue = analogRead(joystickYPin);

  if (!buttonState){ 
    // clicking button (closing hand)
    if (buttonToggle){
      buttonCount++;
    
      if (buttonCount % 2 != 0){
        servoG.write(servoGPos_max);
        digitalWrite(centreLED, HIGH);
        delay(1000);
      }  
      
      if (buttonCount % 2 == 0){
        servoG.write(servoGPos_min);
        digitalWrite(centreLED, LOW);
        delay(1000);
      }
    }

  }

  // moving to the right
  if (joystickXValue > 3000 && 1000 < joystickYValue < 3000){
    if (servoXPos < servoXPos_max){
      servoXPos++;
      servoX.write(servoXPos);
    }
    digitalWrite(topLED, HIGH);
    delay(25);
    digitalWrite(topLED, LOW);
  } 

  // moving left
  if (joystickXValue < 1000 && 1000 < joystickYValue < 3000){
    if (servoXPos > servoXPos_min){
      servoXPos--;
      servoX.write(servoXPos);
    }
    digitalWrite(bottomLED, HIGH);
    delay(25);
    digitalWrite(bottomLED, LOW);
  }

  // moving up
  if (1000 < joystickXValue < 3000 && joystickYValue < 1000){
    if (servoYPos > servoYPos_min){
      servoYPos--;
      servoY.write(servoYPos);
    }
    digitalWrite(rightLED, HIGH);
    delay(25);
    digitalWrite(rightLED, LOW);
  }

  // moving down
  if (1000 < joystickXValue < 3000 && joystickYValue > 3000){
    if (servoYPos < servoYPos_max){
      servoYPos++;
      servoY.write(servoYPos);
    }
    digitalWrite(leftLED, HIGH);
    delay(25);
    digitalWrite(leftLED, LOW);
  }

}
