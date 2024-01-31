#include <Arduino.h>
#include <Servo.h>

Servo servoMotor;

// put function declarations here:
void setup()
{
  pinMode(31, INPUT); // Set port 32 as input
  pinMode(1, OUTPUT); // Set port 1 as output
  servoMotor.attach(2, 900, 1500);
}

void loop()
{
  servoMotor.write(45);
  delay(500);

  servoMotor.write(135);
  delay(500);

  for (int i = 0; i < 180; i += 5)
  {
    servoMotor.write(i);
    delay(150);
  }

  delay(1000);

  for (int i = 180; i > 0; i -= 5)
  {
    servoMotor.write(i);
    delay(150);
  }
  // int sensorValue = digitalRead(31); // Read the sensor value from port 0

  // if (sensorValue == HIGH) // If the sensor value is high
  // {
  //   digitalWrite(1, HIGH); // Turn on the LED in port 1
  // }
  // else
  // {
  //   digitalWrite(1, LOW); // Turn off the LED in port 1
}