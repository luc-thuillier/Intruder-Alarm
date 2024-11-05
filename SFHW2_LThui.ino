// Luc Thuillier ; thuillier.l@northeastern.edu ; SFHW2_LThui

#include <Servo.h>

Servo myservo; // Create servo object to be able to control a servo

// Constants for pin assignments
const int redLED = 8;
const int blueLED = 7;
const int pushButton = 3;
const int buzzer = 9;
const int photoresistor = A0;
const int servoPin = 12;

// Variables
bool alarmState = false;
int buttonState = HIGH; // Variable for reading the pushbutton status

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  myservo.attach(servoPin); // Attaches the servo on pin 12 to the servo object
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(photoresistor);
  buttonState = digitalRead(pushButton);

  // Detect light
  if (lightLevel > 400 && buttonState == HIGH) { // Check if the light is being detected and button is not being pressed
    if (!alarmState) {
      myservo.write(180); // Move servo by 180 degrees
      alarmState = true;
    }
    flashLightsAndSoundAlarm(); // Continue to flash the lights and sound the alarm
  } else if (buttonState == LOW) { // If the button is pressed, reset the alarm
    resetAlarm();
    alarmState = false;
  }
}

void flashLightsAndSoundAlarm() {
  digitalWrite(redLED, HIGH);
  delay(100);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, HIGH);
  delay(100);
  digitalWrite(blueLED, LOW);
  playSiren(); // Play the siren sound
}

void deactivateAlarm() {
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  noTone(buzzer); // Stop the siren sound
}

void resetAlarm() {
  deactivateAlarm();
  myservo.write(0); // Move servo back to 0 degrees
  delay(5000); // Wait for 5 seconds before the next detection phase
}

void playSiren() {
  tone(buzzer, 1000); // Play a siren sound
  delay(100);
  noTone(buzzer); // Stop the tone
}