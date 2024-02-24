#include <RCSwitch.h>
#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#define I2C_ADDRESS 0x3C

RCSwitch mySwitch = RCSwitch();
SSD1306AsciiWire oled;
Servo servoMotor;

int anzahlPusten = 0;
bool start = false;
int Timeout = 0;

void setup()
{
  pinMode(32, INPUT); // Set port 32 as input
  pinMode(1, OUTPUT); // Set port 1 as output
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(52, INPUT);
  servoMotor.attach(5, 900, 1500);
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  servoMotor.write(180);
  mySwitch.enableTransmit(10);
  mySwitch.switchOff("11011", "10000");
}

void loop()
{
  if (start && digitalRead(32) != HIGH)
  {
    Timeout++;
    delay(50);
  }
  if (Timeout > 10)
  {
    mySwitch.switchOff("11011", "10000");
    oled.setFont(System5x7);         // Auswahl der Schriftart
    oled.clear();                    // Löschen der aktuellen Displayanzeige
    oled.println("Nicht Geschafft"); // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
    servoMotor.write(180);
    delay(2000);
    Timeout = 0;
    anzahlPusten = 0;
    start = false;
  }

  if (anzahlPusten == 10)
  {
    // Ausschalten
    mySwitch.switchOff("11011", "10000");
    oled.setFont(System5x7);   // Auswahl der Schriftart
    oled.clear();              // Löschen der aktuellen Displayanzeige
    oled.println("Geschafft"); // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
    servoMotor.write(180);
    delay(5000);
    Timeout = 0;
    anzahlPusten = 0;
    start = false;
  }
  if (digitalRead(32) == HIGH && start)
  {
    anzahlPusten++;
    servoMotor.write(180 - anzahlPusten * 18);
    delay(1000);
    oled.setFont(System5x7); // Auswahl der Schriftart
    oled.clear();            // Löschen der aktuellen Displayanzeige
    oled.println("Anzahl:"); // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
    oled.print(anzahlPusten);
  }
  if (digitalRead(52) == LOW)
  {
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    start = true;
    anzahlPusten = 0;
    servoMotor.write(180);
    mySwitch.switchOn("11011", "10000");
  }
  else if (!start)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }
}