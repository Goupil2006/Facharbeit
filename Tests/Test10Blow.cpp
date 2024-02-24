#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#define I2C_ADDRESS 0x3C

SSD1306AsciiWire oled;
Servo servoMotor;

int anzahlPusten = 0;

void setup()
{
    pinMode(31, INPUT); // Set port 32 as input
    pinMode(1, OUTPUT); // Set port 1 as output
    servoMotor.attach(2, 900, 1500);
    Wire.begin();
    Wire.setClock(400000L);
    oled.begin(&Adafruit128x64, I2C_ADDRESS);
    servoMotor.write(0);
}

void loop()
{
    int sensorValue = digitalRead(31); // Read the sensor value from port 0
    if (sensorValue == HIGH)
    {
        anzahlPusten++;
        servoMotor.write(anzahlPusten * 36);
        delay(500);
        oled.setFont(System5x7);  // Auswahl der Schriftart
        oled.clear();             // Löschen der aktuellen Displayanzeige
        oled.println("Anzahl:");  // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
        oled.print(anzahlPusten); // Text in der zweiten Zeile. Da es keine dritte Zeile gibt, wird hier kein Zeilenumsprung benötigt.
    }
    if (anzahlPusten >= 10)
    {
        oled.clear();                // Löschen der aktuellen Displayanzeige
        oled.println("Geschafft!!"); // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
        oled.print("Du hast " + anzahlPusten);
        digitalWrite(1, HIGH); // Turn on the LED connected to port 1
    }
}