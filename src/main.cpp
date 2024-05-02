// Importieren der Librarys
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Importieren der Klassen
#include "MySwitch.cpp"
#include "MyServo.cpp"
#include "MyOled.cpp"
#include "MyAmpel.cpp"

// IC2 Adresse definieren
#define I2C_ADDRESS 0x3C

// Variablen definieren
int anzahlPusten = 0;
bool start = false;
int Timeout = 0;

// Klassen für Komponenten definieren
// MyAmpel ampel = MyAmpel();
MyServo servo1 = MyServo(5, 0, 5);
MyOled oled1 = MyOled();
MySwitch mySwitch = MySwitch(10);

void setup()
{
  // Airflow Sensor zu "input" setzen
  pinMode(32, INPUT); // Aktueller

  // Den Knopf zu "input" setzen
  pinMode(52, INPUT);

  // Die Ampel initialisieren auf die Pins 1, 2 und 3
  // ampel.init(1, 2, 3);

  // Den Servo initialisieren auf Pin 5
  servo1.init(5);

  // Den Oled initialisieren
  oled1.init();

  // Den Switch initialisieren um die Steckdose zu schalten
  mySwitch.init(10);
}

void loop()
{
  // Wenn der Knopf gedrückt wird und die Überprüfung noch nicht gestartet ist
  if (digitalRead(52) == LOW && !start)
  {
    // Alle Komponenten und Variablen auf den Start der Überprüfung setzen
    // ampel.turnOnGreen();
    servo1.reset();
    mySwitch.on();
    anzahlPusten = 0;
    start = true;
  }

  // Wenn die Überprüfung noch nicht gestartet ist
  if (!start)
  {
    // Die Ampel auf Rot setzen
    // ampel.turnOnRed();
    Timeout = 0;
  }

  // Wenn während der Überprüfung Airflow erkannt wird
  if (digitalRead(32) == HIGH && start)
  {
    // Erkannte luftströme erhöhen
    anzahlPusten++;

    // Die Anzahl der Pusten auf dem Oled anzeigen
    oled1.clear();
    oled1.drawTip(0, 30, "Anzahl:");
    String anzahlPustenString = String(anzahlPusten);
    const char *charPointer = anzahlPustenString.c_str();
    oled1.drawtexte(75, 40, charPointer);

    // Den Servo um einen Schritt weiter geben
    servo1.addRotation(1);
    delay(1000);

    Timeout = 0;

    // Wenn 5 Luftströme erkannt wurden
    if (anzahlPusten == 5)
    {
      // Alles Ausschalten und zurücksetzen
      mySwitch.off();
      oled1.clear();
      {
        // Nutzer über display mitteilen, das er es geschafft hat
        oled1.drawTip(0, 30, "Geschafft");
        servo1.reset();
      }
      delay(5000);
      Timeout = 0;
      anzahlPusten = 0;
      start = false;
    }
  }

  // Falls für 0,5 Sekunden kein Luftstrom erkannt wird
  if (Timeout > 10)
  {
    // Alles Ausschalten und zurücksetzen
    mySwitch.off();
    oled1.clear();
    // Nutzer über display mitteilen, das er es nicht geschafft hat
    oled1.drawTip(0, 30, "Nicht Geschafft");
    servo1.reset();
    delay(2000);
    Timeout = 0;
    anzahlPusten = 0;
    start = false;
  }

  // Wenn die Überprüfung gestartet wurde und kein Luftstrom erkannt wird
  if (start && digitalRead(32) != HIGH)
  {
    // Timeout erhöhen
    Timeout++;
    delay(50);
  }
}
