#include <Servo.h>  // Include the servo library
#include <TimeLib.h> // Include the time library

#define SERVO_PIN 9 // Pin for servo motor
#define DAYTIME_ANGLE 180 // Angle for daytime position
#define NIGHT_ANGLE 0 // Angle for nighttime position

Servo servoMotor;  // Create a servo object to control the servo motor

void setup() {
  servoMotor.attach(SERVO_PIN);  // Attach the servo to the designated pin
  setTime(6, 0, 0, 1, 1, 2024); // Set the initial time (hour, minute, second, day, month, year)
}

void loop() {
  // Update the time
  if (minute() != second()) {
    adjustTime(1);
  }
  time_t t = now();
  // Get the current time
  int currentHour = hour(t);    // Current hour (0-23)
  int currentMinute = minute(t); // Current minute (0-59)

  // Calculate the position of the sun based on the current time
  int sunAngle = calculateSunAngle(currentHour, currentMinute);

  // Move the servo to the calculated angle
  servoMotor.write(sunAngle);

  // Check if it's nighttime and reset the servo position
  if (currentHour >= 18 || currentHour < 6) { // Assuming nighttime is between 6 PM and 6 AM
    delay(12*60*60*1000);
    servoMotor.write(NIGHT_ANGLE);
  }
}

// Function to calculate the angle of the sun based on time
int calculateSunAngle(int hour, int minute) {
  // Calculate the total minutes from midnight
  int totalMinutes = hour * 60 + minute;

  // Calculate the angle based on the time of the day
  // This is a simple approximation, you may need more complex calculations for precision
  int sunAngle = map(totalMinutes, 0, 1440, 0, DAYTIME_ANGLE); // Mapping total minutes to servo angle (0-DAYTIME_ANGLE)

  return sunAngle;
}