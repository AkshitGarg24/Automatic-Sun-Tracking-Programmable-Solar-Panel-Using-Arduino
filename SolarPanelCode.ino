#include <Servo.h>
#include<TimeLib.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // Calculate the position of the sun based on the time of the day
  // For simplicity, we assume the sun moves from east to west along the horizon
  unsigned long currentMillis = millis(); // Get the current time in milliseconds
  unsigned long totalSeconds = currentMillis / 1000; // Convert milliseconds to seconds
  // Calculate the angle for the servo based on the time of the day
  // We're assuming 240 seconds represent 24 hours, so it will work for only 120 seconds
  int angle = map(totalSeconds % 120, 0, 120, 0, 180); // Map the time to a servo angle
  if(totalSeconds%120==119){  // Rest 120 seconds it will tke rest and then return to its original position
    delay(120000);
  }
  // Move the servo to the calculated position
  myservo.write(angle);
  // Wait for a moment before updating the position again
  delay(1000);  // Update position every second
}
