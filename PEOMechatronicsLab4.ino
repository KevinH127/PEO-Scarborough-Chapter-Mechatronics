
#define buttonPin 25 // pressing down on joystick
#define centreLED 13 // blue LED
#define leftLED 27 // green LED
#define rightLED 26 // yellow LED
#define bottomLED 14 // white LED
#define topLED 12 // red LED
#define joystickXPin 35 // moving left/right with joystick
#define joystickYPin 34 // moving up/down with joystick

// initialize joystick state variables
bool buttonState = HIGH;
int joystickXValue = 0;
int joystickYValue = 0;

void setup() {
  //pin mode for Joystick
  pinMode(buttonPin, INPUT_PULLUP);

  // pin mode for LEDS
  pinMode(centreLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(bottomLED, OUTPUT);
  pinMode(topLED, OUTPUT);

  // start ESP32
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  digitalWrite(centreLED, HIGH);
  delay(1000);
  digitalWrite(centreLED, LOW);
  delay(1000);

  digitalWrite(topLED, HIGH);
  delay(1000);
  digitalWrite(topLED, LOW);
  delay(1000);

  digitalWrite(bottomLED, HIGH);
  delay(1000);
  digitalWrite(bottomLED, LOW);
  delay(1000);

  digitalWrite(leftLED, HIGH);
  delay(1000);
  digitalWrite(leftLED, LOW);
  delay(1000);
}
