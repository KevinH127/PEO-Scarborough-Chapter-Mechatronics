// import Servo library
#include <ESP32Servo.h>

// define Joystick Pins
#define buttonPin 25
#define joystickXPin 35
#define joystickYPin 34

bool buttonState = HIGH;
bool buttonToggle = HIGH;

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
int servoXPos = 0;
int servoYPos = 0;
int servoGPos = 0;

// Min/Max Position for all Servos
int servoPos_min = 0;
int servoPos_max = 180;

// Initializing Joystick Values
int joystickXValue = 0;
int joystickYValue = 0;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  servoX.attach(servoXPin, minUs, maxUs);
  servoY.attach(servoYPin, minUs, maxUs);
  servoG.attach(servoGPin, minUs, maxUs);

  servoX.write(servoPos_min);
  servoY.write(servoPos_min);
  servoG.write(servoPos_min);

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
      for (servoGPos = servoPos_min; servoGPos < servoPos_max; servoGPos += 1){
        servoG.write(servoGPos);
        delay(1);
      }  
    }

    // opening hand
    if (!buttonToggle){
      for (servoGPos = servoPos_max; servoGPos > servoPos_min; servoGPos -= 1){
        servoG.write(servoGPos);
        delay(1);
      }
    }

  }

  // moving to the right
  if (joystickXValue > 3000 && 1000 < joystickYValue < 3000){
    if (servoXPos < servoPos_max){
      servoXPos++;
      servoX.write(servoXPos);
    }

    delay(10);
  } 

  // moving left
  if (joystickXValue < 1000 && 1000 < joystickYValue < 3000){
    if (servoXPos > servoPos_min){
      servoXPos--;
      servoX.write(servoXPos);
    }

    delay(10);
  }

  // moving up
  if (1000 < joystickXValue < 3000 && joystickYValue < 1000){
    if (servoYPos > servoPos_min){
      servoYPos--;
      servoY.write(servoYPos);
    }

    delay(10);
  }

  // moving down
  if (1000 < joystickXValue < 3000 && joystickYValue > 3000){
    if (servoYPos < servoPos_max){
      servoYPos++;
      servoY.write(servoYPos);
    }

    delay(10);
  }

}
