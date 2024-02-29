#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
// #include <string>
// using namespace std;
#include "MySwitch.cpp"
#include "MyServo.cpp"
#include "MyOled.cpp"
#include "MyAmpel.cpp"
#define I2C_ADDRESS 0x3C

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

int anzahlPusten = 0;
bool start = false;
int Timeout = 0;

MyAmpel ampel = MyAmpel(1, 2, 3);
MyServo servo1 = MyServo(5, 0, 10);
MyOled oled1 = MyOled();
MySwitch mySwitch = MySwitch(10);

void setup()
{
  // Airflow Sensor zu "input" setzen
  pinMode(32, INPUT);
  pinMode(33, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);

  // Den Knopf zu "input" setzen
  pinMode(52, INPUT);

  // Die Ampel initialisieren auf die Pins 1, 2 und 3
  ampel = MyAmpel(1, 2, 3);

  // Die Ampel auf Rot setzen
  ampel.turnOnRed();

  // Den Servo initialisieren auf Pin 5, mit der anfangsposition 0 und zehn Schritte bis 180 Grad
  servo1 = MyServo(5, 0, 10);

  // Den Oled initialisieren
  oled1 = MyOled();
  oled1.drawTip(0, 30, "Pusten um zu starten");

  // Den Switch initialisieren um die Steckdose zu schalten
  mySwitch = MySwitch(10);
}

void loop()
{
  // Wenn der Knopf gedrückt wird und die Überprüfung noch nicht gestartet ist
  if (digitalRead(52) == LOW && !start)
  {
    // Die Ampel auf Grün setzen
    ampel.turnOnGreen();

    // Den Servo auf die Startposition setzen
    servo1.reset();

    // Die Steckdose einschalten
    mySwitch.on();

    // Die Anzahl der Pusten auf 0 setzen
    anzahlPusten = 0;

    // Den Start auf true setzen
    start = true;
  }
  else if (!start)
  {
    // Die Ampel auf Rot setzen
    ampel.turnOnRed();
    Timeout = 0;
  }
  else if (digitalRead(32) == HIGH && start)
  {
    anzahlPusten++;

    // Den Servo um einen Schritt weiter geben
    servo1.addRotation(1);
    delay(1000);

    // Die Anzahl der Pusten auf dem Oled anzeigen
    oled1.clear();
    oled1.drawTip(0, 30, "Anzahl:");
    String anzahlPustenString = String(anzahlPusten);
    const char *charPointer = anzahlPustenString.c_str();
    oled1.drawtexte(50, 40, charPointer);
  }
  else if (anzahlPusten == 10)
  {
    // Alles Ausschalten und zurücksetzen
    mySwitch.off();
    oled1.clear();
    // Nutzer über display mitteilen, das er es geschafft hat
    oled1.drawTip(0, 30, "Geschafft");
    servo1.reset();
    delay(5000);
    Timeout = 0;
    anzahlPusten = 0;
    start = false;
  }
  else if (Timeout > 10)
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
  else if (start && digitalRead(32) != HIGH)
  {
    Timeout++;
    delay(50);
  }
}

// void loop()
// {
//   if (start && digitalRead(32) != HIGH)
//   {
//     Timeout++;
//     delay(50);
//   }
//   if (Timeout > 10)
//   {
//     mySwitch.switchOff("11011", "10000");
//     oled.setFont(System5x7);         // Auswahl der Schriftart
//     oled.clear();                    // Löschen der aktuellen Displayanzeige
//     oled.println("Nicht Geschafft"); // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
//     servoMotor.write(180);
//     delay(2000);
//     Timeout = 0;
//     anzahlPusten = 0;
//     start = false;
//   }

//   if (anzahlPusten == 10)
//   {
//     // Ausschalten
//     mySwitch.switchOff("11011", "10000");
//     oled.setFont(System5x7);   // Auswahl der Schriftart
//     oled.clear();              // Löschen der aktuellen Displayanzeige
//     oled.println("Geschafft"); // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
//     servoMotor.write(180);
//     delay(5000);
//     Timeout = 0;
//     anzahlPusten = 0;
//     start = false;
//   }
//   if (digitalRead(32) == HIGH && start)
//   {
//     anzahlPusten++;
//     servoMotor.write(180 - anzahlPusten * 18);
//     delay(1000);
//     oled.setFont(System5x7); // Auswahl der Schriftart
//     oled.clear();            // Löschen der aktuellen Displayanzeige
//     oled.println("Anzahl:"); // Text in der ersten Zeile. "Println" sorgt dabei für einen Zeilensprung.
//     oled.print(anzahlPusten);
//   }
//   if (digitalRead(52) == LOW)
//   {
//     digitalWrite(1, LOW);
//     digitalWrite(2, LOW);
//     digitalWrite(3, HIGH);
//     start = true;
//     anzahlPusten = 0;
//     servoMotor.write(180);
//     mySwitch.switchOn("11011", "10000");
//   }
//   else if (!start)
//   {
//     digitalWrite(1, HIGH);
//     digitalWrite(2, LOW);
//     digitalWrite(3, LOW);
//   }
// }
