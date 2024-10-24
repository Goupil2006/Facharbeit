// Importieren der Librarys
#include <Arduino.h>
#include <Adafruit_BMP085.h>
#include <SoftwareWire.h>

// Importieren der Klassen
#include "MySwitch.cpp"
#include "MyServo.cpp"
#include "MyOled.cpp"
#include "MyAmpel.cpp"

// IC2 Adresse definieren
#define I2C_ADDRESS 0x3C

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

SoftwareWire myWire1(37, 35); // SDA = 37, SCL = 35
SoftwareWire myWire2(41, 39); // SDA = 41, SCL = 39
SoftwareWire myWire3(45, 43); // SDA = 45, SCL = 43
SoftwareWire myWire4(49, 47); // SDA = 49, SCL = 47
SoftwareWire myWire5(53, 51); // SDA = 53, SCL = 51

Adafruit_BMP085 bmp1(&myWire1);
Adafruit_BMP085 bmp2(&myWire2);
Adafruit_BMP085 bmp3(&myWire3);
Adafruit_BMP085 bmp4(&myWire4);
Adafruit_BMP085 bmp5(&myWire5);

double pressure1;
double pressure2;
double pressure3;
double pressure4;
double pressure5;

// Variablen definieren
int anzahlPusten = 0;
bool checking = false;
int Timeout = 0;
int stage = 0;
double druck = 0;

// Klassen für Komponenten definieren
// MyAmpel ampel = MyAmpel();
// MyServo servo1 = MyServo(5, 0, 5);
MyOled oled1 = MyOled();
MySwitch mySwitch = MySwitch(10);

String currentdisplay = "";

const int SERVO1 = 2;
const int SERVO2 = 3;
const int SERVO3 = 4;
const int SERVO4 = 5;
const int SERVO5 = 6;
const int BUTTON = 22;
const int Gyro = A13;

const int correctConnections[5] = {bmp1, bmp2, bmp3, bmp4, bmp5};

void start()
{
  s1.write(90);
  delay(200);

  s2.write(90);
  delay(200);

  s3.write(90);
  delay(200);

  s4.write(100);
  delay(200);

  s5.write(85);
  delay(200);

  s1.write(0);
  oled1.drawtexte(0, 30, "An");
  // Alle Komponenten und Variablen auf den Start der Überprüfung setzen
  // ampel.turnOnGreen();
  // servo1.reset();
  mySwitch.on();
  anzahlPusten = 0;
  stage = 0;
  checking = true;
}

void checkSuccess()
{
  // Erkannte luftströme erhöhen
  stage++;

  // move next servo
  switch (stage)
  {
  case 1:
    s1.write(90);
    delay(1000);
    s2.write(0);
    delay(500);
    break;
  case 2:
    s2.write(90);
    delay(1000);
    s3.write(0);
    delay(500);
  case 3:
    s3.write(100);
    delay(1000);
    s4.write(0);
    delay(500);
  case 4:
    s4.write(85);
    delay(1000);
    s5.write(0);
    delay(500);
  }

  anzahlPusten++;

  // Die Anzahl der Pusten auf dem Oled anzeigen
  switch (stage)
  {
  case 1:
    oled1.drawtexte(75, 40, "Anzahl: 1");
    break;
  case 2:
    oled1.drawtexte(75, 40, "Anzahl: 2");
    break;
  case 3:
    oled1.drawtexte(75, 40, "Anzahl: 3");
    break;
  case 4:
    oled1.drawtexte(75, 40, "Anzahl: 4");
    break;
  case 5:
    oled1.drawtexte(75, 40, "Anzahl: 5");
    break;
  default:
    break;
  }

  // Den Servo um einen Schritt weiter geben
  // servo1.addRotation(1);
  delay(1000);

  Timeout = 0;

  // Wenn 5 Luftströme erkannt wurden
  if (stage == 5)
  {
    s5.write(80);
    // Alles Ausschalten und zurücksetzen
    mySwitch.off();
    {
      // Nutzer über display mitteilen, das er es geschafft hat
      oled1.drawtexte(0, 30, "Geschafft");
      // servo1.reset();
    }
    delay(5000);
    Timeout = 0;
    anzahlPusten = 0;
    checking = false;
  }
}

void stopCheck()
{
  // Alles Ausschalten und zurücksetzen
  mySwitch.off();
  // Nutzer über display mitteilen, das er es nicht geschafft hat
  oled1.drawtexte(0, 30, "Nicht Geschafft");
  delay(1000);
  switch (stage)
  {
  case 1:
    oled1.drawtexte(75, 40, "Anzahl: 1");
    break;
  case 2:
    oled1.drawtexte(75, 40, "Anzahl: 2");
    break;
  case 3:
    oled1.drawtexte(75, 40, "Anzahl: 3");
    break;
  case 4:
    oled1.drawtexte(75, 40, "Anzahl: 4");
    break;
  case 5:
    oled1.drawtexte(75, 40, "Anzahl: 5");
    break;
  default:
    break;
  }
  // servo1.reset();
  delay(1000);
  Timeout = 0;
  anzahlPusten = 0;
  checking = false;
}

bool isStartCase()
{
  return analogRead(Gyro) > 500 && !checking;
}

bool isAirflowAndChecking()
{ // digitalRead(correctConnections[stage]) == HIGH
  if (checking)
  {
    if (correctConnections[stage].readPressure() + 500 > pressure1)
    {
      return true;
    }
    else
    {
      delay(500);
      if (correctConnections[stage].readPressure() + 500 > pressure1)
      {
        return true;
      }
      else
      {
        delay(500);
        if (correctConnections[stage].readPressure() + 500 > pressure1)
        {
          return true;
        }
        else
        {
          delay(500);
        }
      }
    }
  }
  return correctConnections[stage].readPressure() + 500 > pressure1 && checking;
}

bool isNoAirflow()
{
  return Timeout > 10;
}

void checkLoop()
{
  if (isStartCase())
  {
    s1.write(0);
    start();
    currentdisplay = "Click";
    if (currentdisplay != "Click")
    {
      oled1.drawtexte(0, 30, "Click");
    }
  }
  else
  {
    currentdisplay = "Ready";
    if (currentdisplay != "Ready")
    {
      oled1.drawtexte(0, 30, "Ready");
    }
  }

  // // Wenn die Überprüfung noch nicht gestartet ist
  if (!checking)
  {
    //   // Die Ampel auf Rot setzen
    //   // ampel.turnOnRed();
    Timeout = 0;
  }

  // // Wenn während der Überprüfung Airflow erkannt wird
  if (isAirflowAndChecking())
  {
    checkSuccess();
  }
  else
  {
    Timeout++;
    delay(50);
  }

  // // Falls für 0,5 Sekunden kein Luftstrom erkannt wird
  if (isNoAirflow())
  {
    stopCheck();
  }

  // // Wenn die Überprüfung gestartet wurde und kein Luftstrom erkannt wird
}

void setup()
{
  // Luftdurcksensoren Initialisieren
  // Den Oled initialisieren
  oled1.init();
  oled1.drawtexte(0, 30, "TEST");

  // Servos für Ventile
  s1.attach(SERVO1, 500, 1500);
  s2.attach(SERVO2, 475, 1500);
  s3.attach(SERVO3, 900, 1500);
  s4.attach(SERVO4, 900, 1800);
  s5.attach(SERVO5, 475, 1500);

  // Überprüfen der Servos
  s1.write(0);
  delay(1000);
  s1.write(90);
  delay(1000);

  s2.write(0);
  delay(1000);
  s2.write(90);
  delay(1000);

  s3.write(0);
  delay(1000);
  s3.write(90);
  delay(1000);

  s4.write(0);
  delay(1000);
  s4.write(100);
  delay(1000);

  s5.write(0);
  delay(1000);
  s5.write(85);
  delay(1000);

  // Airflow Sensor zu "input" setzen
  pinMode(AIRFLOW1, INPUT);
  pinMode(AIRFLOW2, INPUT);
  pinMode(AIRFLOW3, INPUT);
  pinMode(AIRFLOW4, INPUT);
  pinMode(AIRFLOW5, INPUT);

  // Den Knopf zu "input" setzen
  pinMode(BUTTON, INPUT);

  // BMPS Inizaliesieren
  myWire1.begin();
  myWire2.begin();
  myWire3.begin();
  myWire4.begin();
  myWire5.begin();

  pressure1 = bmp1.readPressure();
  pressure2 = bmp2.readPressure();
  pressure3 = bmp3.readPressure();
  pressure4 = bmp4.readPressure();
  pressure5 = bmp5.readPressure();

  // Die Ampel initialisieren auf die Pins 1, 2 und 3
  // ampel.init(1, 2, 3);

  // Den Servo initialisieren auf Pin 5
  // ervo1.init(5);

  // Den Switch initialisieren um die Steckdose zu schalten
  mySwitch.init(11);
}

void loop()
{
  checkLoop();
}
